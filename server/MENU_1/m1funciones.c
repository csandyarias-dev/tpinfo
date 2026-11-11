/**
	\file    Menu1_funciones_servidor_socket.c
	\brief   Funciones internas del servidor (Menu 1) con socket. NINGUNA imprime por pantalla.
	\author  Las Marmotas
	\version 2.0.0
*/

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../inc/encabezadogeneral.h"

#define MAX_LETRAS_NOMBRE 30

#ifndef RECORRIENDO
#define RECORRIENDO 1
#define FIN 0
#endif 

//-------------------------------------------------------------

/**
	\fn     const char * obtener_nombre_responsable(nodo_responsable_t * lista_resp, int responID);
	\brief  Busca el nombre de un responsable a partir de su ID
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_resp: lista de responsables
	\param  responID: ID del responsable a buscar
	\return El nombre del responsable, o NULL si no existe
*/
const char * obtener_nombre_responsable(nodo_responsable_t * lista_resp, int responID) {
    const char * nombre = NULL;

    while (lista_resp != NULL && nombre == NULL) {
        if (lista_resp->responsable.responID == responID) {
            nombre = lista_resp->responsable.nombre;
        }
        lista_resp = lista_resp->sig;
    }

    return nombre;
}

//-------------------------------------------------------------

/**
	\fn     const char * obtener_nombre_paciente(nodo_paciente_t * lista_pac, int pacID);
	\brief  Busca el nombre de un paciente a partir de su ID
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pac: lista de pacientes
	\param  pacID: ID del paciente a buscar
	\return El nombre del paciente, o NULL si no existe
*/
const char * obtener_nombre_paciente(nodo_paciente_t * lista_pac, int pacID) {
    const char * nombre = NULL;

    while (lista_pac != NULL && nombre == NULL) {
        if (lista_pac->paciente.pacID == pacID) {
            nombre = lista_pac->paciente.nombre;
        }
        lista_pac = lista_pac->sig;
    }

    return nombre;
}

//------------------------------------------------------------- 

/**
	\fn     int coincide_responsable(responsable_t r, const char *nom, const char *ape)
	\brief  Chequea que la hora sea valida
	\author Las Marmotas
	\date   2026.10.29
	\param  responsable_t r, const char *nom, const char *ape
	\return int coincide
*/

int coincide_responsable(responsable_t r, const char *nom, const char *ape) {
    int coincide = 0, evaluar_nom = 0, evaluar_ape = 0;

    if (nom[0] != '\0' && strcmp(nom, "-") != 0) evaluar_nom = 1;
    if (ape[0] != '\0' && strcmp(ape, "-") != 0) evaluar_ape = 1;

    if (evaluar_nom && evaluar_ape) {
        if (strcasecmp(r.nombre, nom) == 0 && strcasecmp(r.apellido, ape) == 0) coincide = 1;
    } else if (evaluar_nom) {
        if (strcasecmp(r.nombre, nom) == 0) coincide = 1;
    } else if (evaluar_ape) {
        if (strcasecmp(r.apellido, ape) == 0) coincide = 1;
    }

    return coincide;
} 

//-------------------------------------------------------------

/**
	\fn     int es_hora_valida(int hora, int min, int am_pm)
	\brief  Chequea que la hora sea valida
	\author Las Marmotas
	\date   2026.10.29
	\param  int hora, int min, int am_pm
	\return 1 si la hora es valida, 0 si no
*/

int es_hora_valida(int hora, int min, int am_pm) {
    int valida = 0;

    if (hora >= 1 && hora <= 12 && min >= 0 && min <= 59 && (am_pm == 0 || am_pm == 1)) {
        valida = 1;
    }

    return valida;
}

//-------------------------------------------------------------

/**
	\fn     int es_fecha_valida(nfecha_t f);
	\brief  Chequea que la fecha exista (contempla años bisiestos)
	\author Las Marmotas
	\date   2026.10.29
	\param  f: fecha a chequear
	\return 1 si la fecha es valida, 0 si no
*/
int es_fecha_valida(nfecha_t f) {
    int dias_mes[12] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
    int valida = 0, dias_max = 0, bisiesto = 0;

    if (f.bits1.mes >= 1 && f.bits1.mes <= 12 && f.bits1.anio >= 1 && f.bits1.dia >= 1) {
        bisiesto = ((f.bits1.anio % 4 == 0 && f.bits1.anio % 100 != 0) || f.bits1.anio % 400 == 0);
        dias_max = dias_mes[f.bits1.mes - 1];

        if (f.bits1.mes == 2 && bisiesto) {
            dias_max = 29;
        }

        if (f.bits1.dia <= dias_max) {
            valida = 1;
        }
    }

    return valida;
} 

//------------------------------------------------------------- 

/**
	\fn      int comparar_fecha_hora(turnos_t a, turnos_t b)
	\brief   Compara dos turnos cronologicamente por fecha y hora (ascendente)
	\author  Grupo Las Marmotas
	\date    2026.10.29
	\param   turnos_t a, turnos_t b
	\return  >0 si a > b, <0 si a < b, 0 si son iguales
*/
int comparar_fecha_hora(turnos_t a, turnos_t b) {
    int res = 0, hora_a = 0, hora_b = 0;

    if (a.fecha.bits1.anio != b.fecha.bits1.anio) {
        res = (int)a.fecha.bits1.anio - (int)b.fecha.bits1.anio;
    } else if (a.fecha.bits1.mes != b.fecha.bits1.mes) {
        res = (int)a.fecha.bits1.mes - (int)b.fecha.bits1.mes;
    } else if (a.fecha.bits1.dia != b.fecha.bits1.dia) {
        res = (int)a.fecha.bits1.dia - (int)b.fecha.bits1.dia;
    } else if (a.hora.bits.am_pm != b.hora.bits.am_pm) {
        res = (int)a.hora.bits.am_pm - (int)b.hora.bits.am_pm;
    } else {
        hora_a = (a.hora.bits.hora == 12) ? 0 : (int)a.hora.bits.hora;
        hora_b = (b.hora.bits.hora == 12) ? 0 : (int)b.hora.bits.hora;
        if (hora_a != hora_b) {
            res = hora_a - hora_b;
        } else {
            res = (int)a.hora.bits.min - (int)b.hora.bits.min;
        }
    }
    return res;
} 

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_PacienteID(int socket_fd, nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Recibe un ID del cliente y le envia cada paciente que coincide
	\param  socket_fd: socket conectado con el cliente
	\param  lista_pacientes: lista de pacientes
	\param  id_ingresado: aca se guarda el ID recibido del cliente
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, dato_valido = 0, id_ingresado = 0, estado = FIN;
    nodo_paciente_t *aux_pacientes = *lista_pacientes;

    recv(socket_fd, &dato_valido, sizeof(int), MSG_WAITALL);

    if (dato_valido) {
        recv(socket_fd, &id_ingresado, sizeof(int), MSG_WAITALL);

        while (aux_pacientes != NULL) {
            if (aux_pacientes->paciente.pacID == id_ingresado) {
                estado = RECORRIENDO;
                send(socket_fd, &estado, sizeof(int), 0);
                send(socket_fd, &(aux_pacientes->paciente), sizeof(paciente_t), 0);
                contador++;
            }
            aux_pacientes = aux_pacientes->sig;
        }

        estado = FIN;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &contador, sizeof(int), 0);
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_PacienteNombre(int socket_fd, nodo_paciente_t *lista_pacientes, char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Recibe un nombre del cliente y le envia cada paciente que coincide
	\param  socket_fd: socket conectado con el cliente
	\param  lista_pacientes: lista de pacientes
	\param  nombre_ingresado: buffer de MAX_LETRAS_NOMBRE donde se guarda el nombre recibido
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    nodo_paciente_t *aux_pacientes = *lista_pacientes;

    recv(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
    nombre_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';

    while (aux_pacientes != NULL) {
        if (strcasecmp(aux_pacientes->paciente.nombre, nombre_ingresado) == 0) {
            estado = RECORRIENDO;
            send(socket_fd, &estado, sizeof(int), 0);
            send(socket_fd, &(aux_pacientes->paciente), sizeof(paciente_t), 0);
            contador++;
        }
        aux_pacientes = aux_pacientes->sig;
    }

    estado = FIN;
    send(socket_fd, &estado, sizeof(int), 0);
    send(socket_fd, &contador, sizeof(int), 0);

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableID(int socket_fd, nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Recibe un ID del cliente y le envia cada responsable que coincide
	\param  socket_fd: socket conectado con el cliente
	\param  lista_responsables: lista de responsables
	\param  id_ingresado: aca se guarda el ID recibido del cliente
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, dato_valido = 0, id_ingresado = 0, estado = FIN;
    nodo_responsable_t *aux_responsables = *lista_responsables;

    recv(socket_fd, &dato_valido, sizeof(int), MSG_WAITALL);

    if (dato_valido) {
        recv(socket_fd, &id_ingresado, sizeof(int), MSG_WAITALL);

        while (aux_responsables != NULL) {
            if (aux_responsables->responsable.responID == id_ingresado) {
                estado = RECORRIENDO;
                send(socket_fd, &estado, sizeof(int), 0);
                send(socket_fd, &(aux_responsables->responsable), sizeof(responsable_t), 0);
                contador++;
            }
            aux_responsables = aux_responsables->sig;
        }

        estado = FIN;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &contador, sizeof(int), 0);
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableNombre(int socket_fd, nodo_responsable_t *lista_responsables, char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Recibe un nombre del cliente y le envia cada responsable que coincide
	\param  socket_fd: socket conectado con el cliente
	\param  lista_responsables: lista de responsables
	\param  nombre_ingresado: buffer de MAX_LETRAS_NOMBRE donde se guarda el nombre recibido
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    char apellido_ingresado[MAX_LETRAS_NOMBRE] = {0};
    nodo_responsable_t *aux_responsables = *lista_responsables;

    recv(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
    recv(socket_fd, apellido_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
    nombre_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';
    apellido_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';

    while (aux_responsables != NULL) {
        if (coincide_responsable(aux_responsables->responsable, nombre_ingresado, apellido_ingresado)) {
            estado = RECORRIENDO;
            send(socket_fd, &estado, sizeof(int), 0);
            send(socket_fd, &(aux_responsables->responsable), sizeof(responsable_t), 0);
            contador++;
        }
        aux_responsables = aux_responsables->sig;
    }

    estado = FIN;
    send(socket_fd, &estado, sizeof(int), 0);
    send(socket_fd, &contador, sizeof(int), 0);

    return contador;
}
//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_PacienteNombre(int socket_fd, nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Recibe el nombre de un paciente y le envia sus turnos (usar antes ConsultarCoincidencias_PacienteNombre)
	\param  socket_fd: socket conectado con el cliente
	\param  lista_turnos: lista de turnos
	\param  lista_pacientes: lista de pacientes (el turno solo guarda el pacID)
	\param  nombre_ingresado: buffer de MAX_LETRAS_NOMBRE donde se guarda el nombre recibido
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, coincidencias = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    nodo_turnos_t *aux_turnos = *lista_turnos;
    const char *nombre_pac = NULL;

    // Paso 1: Reutilizamos ConsultarCoincidencias_PacienteNombre tal como disenaste en el cliente
    coincidencias = ConsultarCoincidencias_PacienteNombre(socket_fd, u_pac, u_resp, lista_pacientes, lista_responsables, lista_turnos, tipos, cant_t, u_tipo);

    // Paso 2: Si hubo 1 sola coincidencia, el cliente reenvia el nombre y le mandamos los turnos
    if (coincidencias == 1) {
        recv(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
        nombre_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';

        while (aux_turnos != NULL) {
            nombre_pac = obtener_nombre_paciente(*lista_pacientes, aux_turnos->turnos.pacID);
            if (nombre_pac != NULL && strcasecmp(nombre_pac, nombre_ingresado) == 0) {
                estado = RECORRIENDO;
                send(socket_fd, &estado, sizeof(int), 0);
                send(socket_fd, &(aux_turnos->turnos), sizeof(turnos_t), 0);
                contador++;
            }
            aux_turnos = aux_turnos->sig;
        }

        estado = FIN;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &contador, sizeof(int), 0);
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_Fecha(int socket_fd, nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados);
	\brief  Recibe una fecha del cliente y le envia los turnos de ese dia
	\param  socket_fd: socket conectado con el cliente
	\param  lista_turnos: lista de turnos
	\param  fecha_ingresada: aca se guarda la fecha recibida del cliente
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados

	Protocolo: recibe dato_valido; si es 1 recibe la fecha y envia fecha_valida (1/0);
	si la fecha es valida envia los turnos (estado + turno ...) y al final FIN + contador.
*/
int ConsultarTurnos_Fecha(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, estado = FIN, dato_valido = 0, fecha_valida = 0;
    nfecha_t fecha_ingresada;
    nodo_turnos_t *aux_turnos = *lista_turnos;

    fecha_ingresada.valor = 0;
    recv(socket_fd, &dato_valido, sizeof(int), MSG_WAITALL);

    if (dato_valido) {
        recv(socket_fd, &fecha_ingresada, sizeof(nfecha_t), MSG_WAITALL);

        fecha_valida = es_fecha_valida(fecha_ingresada);
        send(socket_fd, &fecha_valida, sizeof(int), 0);

        if (fecha_valida) {
            while (aux_turnos != NULL) {
                if (aux_turnos->turnos.fecha.bits1.dia  == fecha_ingresada.bits1.dia &&
                    aux_turnos->turnos.fecha.bits1.mes  == fecha_ingresada.bits1.mes &&
                    aux_turnos->turnos.fecha.bits1.anio == fecha_ingresada.bits1.anio) {

                    estado = RECORRIENDO;
                    send(socket_fd, &estado, sizeof(int), 0);
                    send(socket_fd, &(aux_turnos->turnos), sizeof(turnos_t), 0);
                    contador++;
                }
                aux_turnos = aux_turnos->sig;
            }

            estado = FIN;
            send(socket_fd, &estado, sizeof(int), 0);
            send(socket_fd, &contador, sizeof(int), 0);
        }
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_ResponsableNombre(int socket_fd, nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Recibe el nombre de un responsable y le envia sus turnos
	\param  socket_fd: socket conectado con el cliente
	\param  lista_turnos: lista de turnos
	\param  lista_responsables: lista de responsables (el turno solo guarda el responID)
	\param  nombre_ingresado: buffer de MAX_LETRAS_NOMBRE donde se guarda el nombre recibido
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, coincidencias = 0, estado = FIN, id_resp_unico = -1;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    char apellido_ingresado[MAX_LETRAS_NOMBRE] = {0};
    nodo_turnos_t *aux_turnos = *lista_turnos;
    nodo_responsable_t *aux_resp = *lista_responsables;

    coincidencias = ConsultarCoincidencias_ResponsableNombre(socket_fd, u_pac, u_resp, lista_pacientes, lista_responsables, lista_turnos, tipos, cant_t, u_tipo);

    if (coincidencias == 1) {
        recv(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
        recv(socket_fd, apellido_ingresado, MAX_LETRAS_NOMBRE, MSG_WAITALL);
        nombre_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';
        apellido_ingresado[MAX_LETRAS_NOMBRE - 1] = '\0';

        while (aux_resp != NULL && id_resp_unico == -1) {
            if (coincide_responsable(aux_resp->responsable, nombre_ingresado, apellido_ingresado)) {
                id_resp_unico = aux_resp->responsable.responID;
            }
            aux_resp = aux_resp->sig;
        }

        while (aux_turnos != NULL) {
            if (aux_turnos->turnos.responID == id_resp_unico) {
                estado = RECORRIENDO;
                send(socket_fd, &estado, sizeof(int), 0);
                send(socket_fd, &(aux_turnos->turnos), sizeof(turnos_t), 0);
                contador++;
            }
            aux_turnos = aux_turnos->sig;
        }

        estado = FIN;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &contador, sizeof(int), 0);
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int MostrarListadoCompletoPacientes(int socket_fd, nodo_paciente_t *lista_pac);
	\brief  Envia al cliente todos los pacientes
	\param  socket_fd: socket conectado con el cliente
	\param  lista_pac: lista de pacientes
	\return Cantidad de pacientes enviados
*/
int MostrarListadoCompletoPacientes(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pac, nodo_responsable_t **lista_resp, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, estado = FIN;
    nodo_paciente_t *aux = *lista_pac;

    while (aux != NULL) {
        estado = RECORRIENDO;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &(aux->paciente), sizeof(paciente_t), 0);
        contador++;
        aux = aux->sig;
    }

    estado = FIN;
    send(socket_fd, &estado, sizeof(int), 0);

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int MostrarListadoCompletoResponsables(int socket_fd, nodo_responsable_t *lista_resp);
	\brief  Envia al cliente todos los responsables
	\param  socket_fd: socket conectado con el cliente
	\param  lista_resp: lista de responsables
	\return Cantidad de responsables enviados
*/
int MostrarListadoCompletoResponsables(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pac, nodo_responsable_t **lista_resp, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int contador = 0, estado = FIN;
    nodo_responsable_t *aux = *lista_resp;

    while (aux != NULL) {
        estado = RECORRIENDO;
        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &(aux->responsable), sizeof(responsable_t), 0);
        contador++;
        aux = aux->sig;
    }

    estado = FIN;
    send(socket_fd, &estado, sizeof(int), 0);

    return contador;
}

