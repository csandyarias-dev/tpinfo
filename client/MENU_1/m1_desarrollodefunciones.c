/**
	\file    m1_desarrollodefunciones.c
	\brief   Funciones del main 1 correspondientes al TP final
	\author  Las Marmotas
	\date    2026.11.21 
	\version 1.0.0
*/


//--------------
//-- Includes --
//--------------

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../inc/encabezadogeneral.h"

//-------------
//-- Defines --
//-------------

#define MAX_LETRAS_NOMBRE 30
#define MAX_CARACTERES_FECHA 11

//---------------
//-- Funciones --
//---------------

/**
	\fn     void mostrar_paciente(nodo_paciente_t * actual);
	\brief  Imprime los datos de un paciente
	\author Las Marmotas
	\date   2026.10.29
	\param  actual: nodo del paciente a imprimir
	\return No retorna
*/
void mostrar_paciente(nodo_paciente_t * actual) {
    if (actual != NULL) {
        printf("ID: %d | Nombre: %s | Nacimiento: %02d-%02d-%04d | Resp ID: %d\n",
            actual->paciente.pacID,
            actual->paciente.nombre,
            actual->paciente.nacimiento.bits1.dia,
            actual->paciente.nacimiento.bits1.mes,
            actual->paciente.nacimiento.bits1.anio,
            actual->paciente.responID);
    }
}

//-------------------------------------------------------------

/**
	\fn     void mostrar_responsable(nodo_responsable_t * actual);
	\brief  Imprime los datos de un responsable
	\author Las Marmotas
	\date   2026.10.29
	\param  actual: nodo del responsable a imprimir
	\return No retorna
*/
void mostrar_responsable(nodo_responsable_t * actual) {
    if (actual != NULL) {
        printf("Resp ID: %d | Nombre: %s %s | Tel: %lu\n",
            actual->responsable.responID,
            actual->responsable.nombre,
            actual->responsable.apellido,
            actual->responsable.telcont);
    }
}

//-------------------------------------------------------------

/**
	\fn     void imprimir_fecha(nfecha_t f);
	\brief  Imprime una fecha con formato DD-MM-AAAA
	\author Las Marmotas
	\date   2026.10.29
	\param  f: fecha a imprimir
	\return No retorna
*/
void imprimir_fecha(nfecha_t f) {
    printf("%02d-%02d-%04d", f.bits1.dia, f.bits1.mes, f.bits1.anio);
}

//-------------------------------------------------------------

/**
	\fn     void imprimir_hora(nhora_t h);
	\brief  Imprime una hora con formato HH:MM AM/PM
	\author Las Marmotas
	\date   2026.10.29
	\param  h: hora a imprimir
	\return No retorna
*/
void imprimir_hora(nhora_t h) {
    const char *periodo;

    // Campo am_pm de 1 bit: 0 = AM, 1 = PM
    if (h.bits.am_pm == 0) {
        periodo = "AM";
    } else {
        periodo = "PM";
    }

    printf("%02d:%02d %s", h.bits.hora, h.bits.min, periodo);
}

//-------------------------------------------------------------

/**
	\fn     void imprimir_fecha_hora(nfecha_t f, nhora_t h);
	\brief  Imprime una fecha y una hora juntas
	\author Las Marmotas
	\date   2026.10.29
	\param  f: fecha a imprimir
	\param  h: hora a imprimir
	\return No retorna
*/
void imprimir_fecha_hora(nfecha_t f, nhora_t h) {
    imprimir_fecha(f);
    printf(" ");
    imprimir_hora(h);
}

//-------------------------------------------------------------

/**
	\fn     void mostrar_turno(nodo_turnos_t * actual);
	\brief  Imprime los datos de un turno (IDs, fecha y hora)
	\author Las Marmotas
	\date   2026.10.29
	\param  actual: nodo del turno a imprimir
	\return No retorna
*/
void mostrar_turno(nodo_turnos_t * actual) {
    if (actual != NULL) {
        printf("Pac ID: %d | Resp ID: %d | Turno: ",
            actual->turnos.pacID,
            actual->turnos.responID);
        imprimir_fecha_hora(actual->turnos.fecha, actual->turnos.hora);
        printf("\n");
    }
}

//-------------------------------------------------------------

/**
	\fn     void limpiar_buffer(void);
	\brief  Descarta lo que quedo en el buffer de entrada hasta el salto de linea
	\author Las Marmotas
	\date   2026.10.29
	\param  No recibe parametros
	\return No retorna
*/
void limpiar_buffer(void) {
    int c = getchar();

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

//-------------------------------------------------------------

/**
	\fn     int leer_entero(int * valor);
	\brief  Lee un numero entero por teclado y chequea que sea un numero
	\author Las Marmotas
	\date   2026.10.29
	\param  valor: puntero donde se guarda el numero leido
	\return 1 si se leyo un numero, 0 si no
*/
int leer_entero(int * valor) {
    int es_numero = 0;

    if (scanf("%d", valor) == 1) {
        es_numero = 1;
    }
    limpiar_buffer();

    return es_numero;
}

//-------------------------------------------------------------

/**
	\fn     int leer_uchar(int * valor);
	\brief  Lee un unsigned char por teclado y chequea que sea un unsigned char
	\author Las Marmotas
	\date   2026.10.29
	\param  valor: puntero donde se guarda el uchar leido
	\return 1 si se leyo un numero, 0 si no
*/
int leer_uchar(unsigned char * valor) {
    int es_numero = 0;

    if (scanf("%hhu", valor) == 1) {
        es_numero = 1;
    }
    limpiar_buffer();

    return es_numero;
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
	\fn     int ConsultarCoincidencias_PacienteID(nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Busca pacientes por ID e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pacientes: lista de pacientes
	\param  id_ingresado: ID a buscar
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteID(nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado){
    int contador = 0;
    nodo_paciente_t *aux_pacientes = lista_pacientes;

    while (aux_pacientes != NULL) {
        if (aux_pacientes->paciente.pacID == id_ingresado) {
            // Imprime los datos del paciente encontrado
            mostrar_paciente(aux_pacientes);
            send(socket_fd, &(aux_pacientes->paciente), sizeof(paciente_t), 0);

            // Guarda la primera coincidencia (si el llamador quiere recibirla)
            if (Paciente_encontrado != NULL && contador == 0) {
                *Paciente_encontrado = aux_pacientes;
            }
            contador++;
        }
        aux_pacientes = aux_pacientes->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_PacienteNombre(nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Busca pacientes por nombre e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pacientes: lista de pacientes
	\param  nombre_ingresado: nombre a buscar
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteNombre(nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado){
    int contador = 0;
    nodo_paciente_t *aux_pacientes = lista_pacientes;

    while (aux_pacientes != NULL) {
        if (strcmp(aux_pacientes->paciente.nombre, nombre_ingresado) == 0) {
            // Imprime los datos del paciente encontrado
            mostrar_paciente(aux_pacientes);

            if (Paciente_encontrado != NULL && contador == 0) {
                *Paciente_encontrado = aux_pacientes;
            }
            contador++;
        }
        aux_pacientes = aux_pacientes->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableID(nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Busca responsables por ID e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_responsables: lista de responsables
	\param  id_ingresado: ID a buscar
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableID(nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado){
    int contador = 0;
    nodo_responsable_t *aux_responsables = lista_responsables;

    while (aux_responsables != NULL) {
        if (aux_responsables->responsable.responID == id_ingresado) {
            // Imprime los datos del responsable encontrado
            mostrar_responsable(aux_responsables);

            if (Responsable_encontrado != NULL && contador == 0) {
                *Responsable_encontrado = aux_responsables;
            }
            contador++;
        }
        aux_responsables = aux_responsables->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableNombre(nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Busca responsables por nombre e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_responsables: lista de responsables
	\param  nombre_ingresado: nombre a buscar
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableNombre(nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado){
    int contador = 0;
    nodo_responsable_t *aux_responsables = lista_responsables;

    while (aux_responsables != NULL) {
        if (strcmp(aux_responsables->responsable.nombre, nombre_ingresado) == 0) {
            // Imprime los datos del responsable encontrado
            mostrar_responsable(aux_responsables);

            if (Responsable_encontrado != NULL && contador == 0) {
                *Responsable_encontrado = aux_responsables;
            }
            contador++;
        }
        aux_responsables = aux_responsables->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_PacienteNombre(nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de un paciente por nombre (usar antes ConsultarCoincidencias_PacienteNombre)
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  lista_pacientes: lista de pacientes (el turno solo guarda el pacID)
	\param  nombre_ingresado: nombre del paciente
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_PacienteNombre(nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;
    const char *nombre_pac = NULL;

    // Primer recorrido: contamos cuantos turnos hay registrados con ese nombre
    while (aux_turnos != NULL) {
        nombre_pac = obtener_nombre_paciente(lista_pacientes, aux_turnos->turnos.pacID);
        if (nombre_pac != NULL && strcmp(nombre_pac, nombre_ingresado) == 0) {
            contador++;
        }
        aux_turnos = aux_turnos->sig;
    }

    // Si se encontraron turnos, reservar memoria y hacer el segundo recorrido
    if (contador > 0) {
        if (turnos_encontrados != NULL) {
            // Se le da memoria al vector segun la cantidad de turnos encontrados
            vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
        }

        if (turnos_encontrados == NULL || vector_turnos != NULL) {
            aux_turnos = lista_turnos;

            while (aux_turnos != NULL) {
                nombre_pac = obtener_nombre_paciente(lista_pacientes, aux_turnos->turnos.pacID);
                if (nombre_pac != NULL && strcmp(nombre_pac, nombre_ingresado) == 0) {
                    mostrar_turno(aux_turnos);          // Imprime fecha y hora mediante la funcion atomica

                    if (vector_turnos != NULL) {        // Almacena el puntero en el vector dinamico
                        vector_turnos[i] = aux_turnos;
                        i++;
                    }
                }
                aux_turnos = aux_turnos->sig;
            }
        } else {
            contador = 0;   // Si fallo el malloc, la cantidad devuelta se resetea a 0
        }
    }

    // Asignacion final del vector reservado (o NULL si no hubo coincidencias/fallo malloc)
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_Fecha(nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de una fecha
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  fecha_ingresada: fecha a buscar
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_Fecha(nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;

    if (es_fecha_valida(fecha_ingresada)) {
        // Primer recorrido: contar coincidencias en dia, mes y año
        while (aux_turnos != NULL) {
            if (aux_turnos->turnos.fecha.bits1.dia  == fecha_ingresada.bits1.dia &&
                aux_turnos->turnos.fecha.bits1.mes  == fecha_ingresada.bits1.mes &&
                aux_turnos->turnos.fecha.bits1.anio == fecha_ingresada.bits1.anio) {
                contador++;
            }
            aux_turnos = aux_turnos->sig;
        }

        // Si hay coincidencias, reservar memoria dinamica con malloc
        if (contador > 0) {
            if (turnos_encontrados != NULL) {
                vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
            }

            // Si la memoria se asigno correctamente o no se requirio guardar el arreglo
            if (turnos_encontrados == NULL || vector_turnos != NULL) {
                aux_turnos = lista_turnos;

                // Segundo recorrido: imprimir y guardar los turnos
                while (aux_turnos != NULL) {
                    if (aux_turnos->turnos.fecha.bits1.dia  == fecha_ingresada.bits1.dia &&
                        aux_turnos->turnos.fecha.bits1.mes  == fecha_ingresada.bits1.mes &&
                        aux_turnos->turnos.fecha.bits1.anio == fecha_ingresada.bits1.anio) {

                        mostrar_turno(aux_turnos);      // Imprime los datos del turno (fecha y hora)

                        if (vector_turnos != NULL) {    // Almacena la direccion del nodo en el vector dinamico
                            vector_turnos[i] = aux_turnos;
                            i++;
                        }
                    }
                    aux_turnos = aux_turnos->sig;
                }
            } else {
                contador = 0;   // Si malloc falla, resetea el contador a 0
            }
        }

    } else {
        printf("Error: La fecha ingresada (%02d/%02d/%04d) no existe o es invalida.\n",
               fecha_ingresada.bits1.dia, fecha_ingresada.bits1.mes, fecha_ingresada.bits1.anio);
    }

    // Guardar el puntero al vector reservado en la variable dada por referencia
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_ResponsableNombre(nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de un responsable por nombre
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  lista_responsables: lista de responsables (el turno solo guarda el responID)
	\param  nombre_ingresado: nombre del responsable
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_ResponsableNombre(nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;
    const char *nombre_resp = NULL;

    // 1. Primer recorrido: contamos cuantos turnos hay registrados con el nombre del responsable
    while (aux_turnos != NULL) {
        nombre_resp = obtener_nombre_responsable(lista_responsables, aux_turnos->turnos.responID);
        if (nombre_resp != NULL && strcmp(nombre_resp, nombre_ingresado) == 0) {
            contador++;
        }
        aux_turnos = aux_turnos->sig;
    }

    // 2. Si se encontraron turnos, reservamos memoria dinamica y realizamos el segundo recorrido
    if (contador > 0) {
        if (turnos_encontrados != NULL) {
            vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
        }

        if (turnos_encontrados == NULL || vector_turnos != NULL) {
            aux_turnos = lista_turnos;

            while (aux_turnos != NULL) {
                nombre_resp = obtener_nombre_responsable(lista_responsables, aux_turnos->turnos.responID);
                if (nombre_resp != NULL && strcmp(nombre_resp, nombre_ingresado) == 0) {
                    mostrar_turno(aux_turnos);          // Imprime fecha y hora mediante la funcion atomica

                    if (vector_turnos != NULL) {        // Almacena el puntero en el vector dinamico
                        vector_turnos[i] = aux_turnos;
                        i++;
                    }
                }
                aux_turnos = aux_turnos->sig;
            }
        } else {
            contador = 0;   // Si fallo el malloc, la cantidad devuelta se resetea a 0
        }
    }

    // Asignacion final del vector reservado (o NULL si no hubo coincidencias/fallo malloc)
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarPacientePorID_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado);
	\brief  Pide un ID por teclado y muestra el paciente correspondiente
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pac: lista de pacientes
	\param  lista_resp: lista de responsables
	\param  Paciente_encontrado: guarda el paciente encontrado
	\return No retorna
*/
void ConsultarPacientePorID_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado){
    int id_ingresado = 0, resultado_funcion = 0;
    paciente_t aux;

    printf("\nIngrese el ID del paciente: ");

    if (leer_entero(&id_ingresado)) {
		send(socket_fd, &id, sizeof(int), 0);
		recv(socket_fd, &aux, sizeof(paciente_t), 0);
		recv(socket_fd, &coincidencias, sizeof(int), 0);
		
		mostrar_paciente(aux);
        resultado_funcion = ConsultarCoincidencias_PacienteID(lista_pac, id_ingresado, Paciente_encontrado);

        if (resultado_funcion == 0) {
            printf("No existe ese ID. Vuelva a intentarlo.\n");
        } else {
            printf("\n%d resultados de busqueda\n", resultado_funcion);
        }
    } else {
        printf("Error: el ID debe ser un numero.\n");
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarPacientePorNombre_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado);
	\brief  Pide un nombre por teclado y muestra los pacientes que coinciden
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pac: lista de pacientes
	\param  lista_resp: lista de responsables
	\param  Paciente_encontrado: guarda el primer paciente encontrado
	\return No retorna
*/
void ConsultarPacientePorNombre_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado){
    int resultado_funcion = 0;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];

    printf("\nIngrese el nombre del paciente: ");
    scanf("%29s", nombre_ingresado);
    limpiar_buffer();

    resultado_funcion = ConsultarCoincidencias_PacienteNombre(lista_pac, nombre_ingresado, Paciente_encontrado);

    if (resultado_funcion == 0) {
        printf("\nNo existe ese nombre en la lista de pacientes. Vuelva a intentarlo.\n");
    } else {
        printf("\n%d resultados de busqueda\n", resultado_funcion);
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarResponsablePorID_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado);
	\brief  Pide un ID por teclado y muestra el responsable correspondiente
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_resp: lista de responsables
	\param  Responsable_encontrado: guarda el responsable encontrado
	\return No retorna
*/
void ConsultarResponsablePorID_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado){
    int id_ingresado = 0, resultado_funcion = 0;

    printf("\nIngrese el ID del responsable: ");

    if (leer_entero(&id_ingresado)) {
        resultado_funcion = ConsultarCoincidencias_ResponsableID(lista_resp, id_ingresado, Responsable_encontrado);

        if (resultado_funcion == 0) {
            printf("\nNo existe ese ID en la lista de responsables. Vuelva a intentarlo.\n");
        } else {
            printf("\n%d resultados de busqueda\n", resultado_funcion);
        }
    } else {
        printf("Error: el ID debe ser un numero.\n");
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarResponsablePorNombre_Menu(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado);
	\brief  Pide un nombre por teclado y muestra los responsables que coinciden
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_resp: lista de responsables
	\param  Responsable_encontrado: guarda el primer responsable encontrado
	\return No retorna
*/
void ConsultarResponsablePorNombre_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado){
    int resultado_funcion = 0;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];

    printf("\nIngrese el nombre del responsable: ");
    scanf("%29s", nombre_ingresado);
    limpiar_buffer();

    resultado_funcion = ConsultarCoincidencias_ResponsableNombre(lista_resp, nombre_ingresado, Responsable_encontrado);

    if (resultado_funcion == 0) {
        printf("\nNo existe ese nombre en la lista de responsables. Vuelva a intentarlo.\n");
    } else {
        printf("\n%d resultados de busqueda\n", resultado_funcion);
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarTurnosPorPacientes_Menu1(nodo_paciente_t *lista_pac, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
	\brief  Pide el nombre de un paciente y muestra sus turnos (si el nombre es unico)
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pac: lista de pacientes
	\param  lista_turnos: lista de turnos
	\param  turnos_encontrados: vector dinamico con los turnos encontrados
	\return No retorna
*/
void ConsultarTurnosPorPacientes_Menu1(nodo_paciente_t *lista_pac, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados){
    int resultado_funcion = 0, coincidencias = 0;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];

    printf("\nIngrese el nombre del paciente del cual quiere saber los turnos: ");
    scanf("%29s", nombre_ingresado);
    limpiar_buffer();

    coincidencias = ConsultarCoincidencias_PacienteNombre(lista_pac, nombre_ingresado, NULL);

    if (coincidencias == 0) {
        printf("\nNo existe ese nombre en la lista de pacientes. Vuelva a intentarlo.\n");
    } else {
        if (coincidencias > 1) {
            printf("\nHay %d pacientes con ese nombre. Consulte por ID para distinguirlos.\n", coincidencias);
        } else {
            resultado_funcion = ConsultarTurnos_PacienteNombre(lista_turnos, lista_pac, nombre_ingresado, turnos_encontrados);

            if (resultado_funcion == 0) {
                printf("\nEl paciente no tiene turnos registrados.\n");
            } else {
                printf("\n%d resultados de busqueda\n", resultado_funcion);
            }
        }
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarTurnosPorResponsable_Menu1(nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
	\brief  Pide el nombre de un responsable y muestra sus turnos (si el nombre es unico)
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_resp: lista de responsables
	\param  lista_turnos: lista de turnos
	\param  turnos_encontrados: vector dinamico con los turnos encontrados
	\return No retorna
*/
void ConsultarTurnosPorResponsable_Menu1(nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados){
    int resultado_funcion = 0, coincidencias = 0;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];

    printf("\nIngrese el nombre del responsable del cual quiere saber los turnos: ");
    scanf("%29s", nombre_ingresado);
    limpiar_buffer();

    coincidencias = ConsultarCoincidencias_ResponsableNombre(lista_resp, nombre_ingresado, NULL);

    if (coincidencias == 0) {
        printf("\nNo existe ese nombre en la lista de responsables. Vuelva a intentarlo.\n");
    } else {
        if (coincidencias > 1) {
            printf("\nHay %d responsables con ese nombre. Consulte por ID para distinguirlos.\n", coincidencias);
        } else {
            resultado_funcion = ConsultarTurnos_ResponsableNombre(lista_turnos, lista_resp, nombre_ingresado, turnos_encontrados);

            if (resultado_funcion == 0) {
                printf("\nEl responsable no tiene turnos registrados.\n");
            } else {
                printf("\n%d resultados de busqueda\n", resultado_funcion);
            }
        }
    }
}

//-------------------------------------------------------------

/**
	\fn     void ConsultarTurnosPorFecha_Menu(nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
	\brief  Pide una fecha (DD.MM.AAAA) y muestra los turnos de ese dia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  turnos_encontrados: vector dinamico con los turnos encontrados
	\return No retorna
*/
void ConsultarTurnosPorFecha_Menu1(nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados){
    nfecha_t fecha_ingresada;
    char fecha_texto[MAX_CARACTERES_FECHA];
    int dia = 0, mes = 0, anio = 0, resultado_funcion = 0;

    fecha_texto[0] = '\0';

    printf("\nIngrese la fecha con el formato DD.MM.AAAA: ");
    scanf("%10s", fecha_texto);
    limpiar_buffer();

    // Se chequea el rango de cada dato antes de guardarlo en los campos de bits (dia: 5 bits, mes: 4 bits, año: 12 bits)
    if (sscanf(fecha_texto, "%d%*c%d%*c%d", &dia, &mes, &anio) == 3 &&
        dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && anio >= 1 && anio <= 4095) {

        // Asignacion a los miembros de la estructura nfecha_t
        fecha_ingresada.valor = 0;
        fecha_ingresada.bits1.dia = dia;
        fecha_ingresada.bits1.mes = mes;
        fecha_ingresada.bits1.anio = anio;

        printf("Dia: %02d | Mes: %02d | Anio: %04d\n", fecha_ingresada.bits1.dia, fecha_ingresada.bits1.mes, fecha_ingresada.bits1.anio);
        resultado_funcion = ConsultarTurnos_Fecha(lista_turnos, fecha_ingresada, turnos_encontrados);

        if (resultado_funcion == 0) {
            printf("\nNo hay turnos registrados en esa fecha.\n");
        } else {
            printf("\n%d resultados de busqueda\n", resultado_funcion);
        }

    } else {
        printf("Error: El formato ingresado no es valido.\n");
    }
}

//-------------------------------------------------------------

/**
	\fn     void MostrarListadoCompletoPacientes(nodo_paciente_t *lista_pac);
	\brief  Muestra el listado completo de pacientes
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pac: lista de pacientes
	\return No retorna
*/
void MostrarListadoCompletoPacientes(nodo_paciente_t *lista_pac){
    nodo_paciente_t *aux = lista_pac;

    if (aux == NULL) {
        printf("No hay pacientes registrados en el sistema.\n");
    } else {
        printf("\n=================== LISTADO DE PACIENTES ===================\n");
        while (aux != NULL) {
            mostrar_paciente(aux); // Reutiliza la funcion atomica de impresion
            aux = aux->sig;
        }
        printf("============================================================\n");
    }
}

//-------------------------------------------------------------

/**
	\fn     void MostrarListadoCompletoResponsables(nodo_responsable_t *lista_resp);
	\brief  Muestra el listado completo de responsables
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_resp: lista de responsables
	\return No retorna
*/
void MostrarListadoCompletoResponsables(nodo_responsable_t *lista_resp){
    nodo_responsable_t *aux = lista_resp;

    if (aux == NULL) {
        printf("No hay responsables registrados en el sistema.\n");
    } else {
        printf("\n================== LISTADO DE RESPONSABLES =================\n");
        while (aux != NULL) {
            mostrar_responsable(aux); // Reutiliza la funcion atomica de impresion
            aux = aux->sig;
        }
        printf("============================================================\n");
    }
}

//-------------------------------------------------------------
