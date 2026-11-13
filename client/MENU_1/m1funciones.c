/**
	\file    Menu1_funciones_cliente_socket.c
	\brief   Funciones del cliente (Menu 1) con socket. Aca va TODO printf/scanf.
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
#define MAX_CARACTERES_FECHA 11

#ifndef RECORRIENDO
#define RECORRIENDO 1
#define FIN 0
#endif

int es_hora_valida(int hora, int min, int am_pm) {
    int valida = 0;

    if (hora >= 1 && hora <= 12 && min >= 0 && min <= 59 && (am_pm == 0 || am_pm == 1)) {
        valida = 1;
    }

    return valida;
}

//-------------------------------------------------------------

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

void mostrar_paciente(paciente_t * actual) {
    if (actual != NULL) {
        printf("ID: %d | Nombre: %s | Nacimiento: %02d-%02d-%04d | Resp ID: %d\n",
            actual->pacID,
            actual->nombre,
            actual->nacimiento.bits1.dia,
            actual->nacimiento.bits1.mes,
            actual->nacimiento.bits1.anio,
            actual->responID);
    }
}

//-------------------------------------------------------------

void mostrar_responsable(responsable_t * actual) {
    if (actual != NULL) {
        printf("Resp ID: %d | Nombre: %s %s | Tel: %lu\n",
            actual->responID,
            actual->nombre,
            actual->apellido,
            actual->telcont);
    }
}

//-------------------------------------------------------------

void imprimir_fecha(nfecha_t f) {
    printf("%02d-%02d-%04d", f.bits1.dia, f.bits1.mes, f.bits1.anio);
} 

//-------------------------------------------------------------

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

void imprimir_fecha_hora(nfecha_t f, nhora_t h) {
    imprimir_fecha(f);
    printf(" ");
    imprimir_hora(h);
} 

//-------------------------------------------------------------

void mostrar_turno(turnos_t * actual) {
    if (actual != NULL) {
        printf("Pac ID: %d | Resp ID: %d | Turno: ",
            actual->pacID,
            actual->responID);
        imprimir_fecha_hora(actual->fecha, actual->hora);
        printf("\n");
    }
}

//-------------------------------------------------------------

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

void limpiar_buffer(void) {
    int c = getchar();

    while (c != '\n' && c != EOF) {
        c = getchar();
    }
}

//-------------------------------------------------------------

int leer_entero(int * valor) {
    int es_numero = 0;

    if (scanf("%d", valor) == 1) {
        es_numero = 1;
    }
    limpiar_buffer();

    return es_numero;
}

//-------------------------------------------------------------

int leer_uchar(unsigned char * valor) {
    int es_numero = 0;

    if (scanf("%hhu", valor) == 1) {
        es_numero = 1;
    }
    limpiar_buffer();

    return es_numero;
}

//-------------------------------------------------------------

void ConsultarPacientePorID_Menu1(int socket_fd){
    int id_ingresado = 0, resultado_funcion = 0, dato_valido = 0, estado = FIN;
    paciente_t aux;

    printf("\nIngrese el ID del paciente: ");
    dato_valido = leer_entero(&id_ingresado);
    send(socket_fd, &dato_valido, sizeof(int), 0);

    if (dato_valido) {
        send(socket_fd, &id_ingresado, sizeof(int), 0);

        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux, sizeof(paciente_t), MSG_WAITALL);
            mostrar_paciente(&aux);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

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

void ConsultarPacientePorNombre_Menu1(int socket_fd){
    int resultado_funcion = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];
    paciente_t aux;

    printf("\nIngrese el nombre del paciente: ");
    scanf(" %29[^\n]", nombre_ingresado);
    limpiar_buffer();

    send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    while (estado == RECORRIENDO) {
        recv(socket_fd, &aux, sizeof(paciente_t), MSG_WAITALL);
        mostrar_paciente(&aux);
        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    }
    recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

    if (resultado_funcion == 0) {
        printf("\nNo existe ese nombre en la lista de pacientes. Vuelva a intentarlo.\n");
    } else {
        printf("\n%d resultados de busqueda\n", resultado_funcion);
    }
}

//-------------------------------------------------------------

void ConsultarResponsablePorID_Menu1(int socket_fd){
    int id_ingresado = 0, resultado_funcion = 0, dato_valido = 0, estado = FIN;
    responsable_t aux;

    printf("\nIngrese el ID del responsable: ");
    dato_valido = leer_entero(&id_ingresado);
    send(socket_fd, &dato_valido, sizeof(int), 0);

    if (dato_valido) {
        send(socket_fd, &id_ingresado, sizeof(int), 0);

        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux, sizeof(responsable_t), MSG_WAITALL);
            mostrar_responsable(&aux);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

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

void ConsultarResponsablePorNombre_Menu1(int socket_fd){
    int resultado_funcion = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    char apellido_ingresado[MAX_LETRAS_NOMBRE] = {0};
    responsable_t aux;

    printf("\nIngrese el nombre del responsable (o '-' para omitir): ");
    scanf(" %29[^\n]", nombre_ingresado);
    limpiar_buffer();

    printf("Ingrese el apellido del responsable (o '-' para omitir): ");
    scanf(" %29[^\n]", apellido_ingresado);
    limpiar_buffer();

    send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);
    send(socket_fd, apellido_ingresado, MAX_LETRAS_NOMBRE, 0);

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    while (estado == RECORRIENDO) {
        recv(socket_fd, &aux, sizeof(responsable_t), MSG_WAITALL);
        mostrar_responsable(&aux);
        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    }
    recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

    if (resultado_funcion == 0) {
        printf("\nNo existen responsables con esos datos. Vuelva a intentarlo.\n");
    } else {
        printf("\n%d resultados de busqueda\n", resultado_funcion);
    }
}

//-------------------------------------------------------------

void ConsultarTurnosPorPacientes_Menu1(int socket_fd){
    int resultado_funcion = 0, coincidencias = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE];
    paciente_t aux_paciente;
    turnos_t aux_turno;

    printf("\nIngrese el nombre del paciente del cual quiere saber los turnos: ");
    scanf(" %29[^\n]", nombre_ingresado);
    limpiar_buffer();

    send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    while (estado == RECORRIENDO) {
        recv(socket_fd, &aux_paciente, sizeof(paciente_t), MSG_WAITALL);
        mostrar_paciente(&aux_paciente);
        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    }
    recv(socket_fd, &coincidencias, sizeof(int), MSG_WAITALL);

    if (coincidencias == 0) {
        printf("\nNo existe ese nombre en la lista de pacientes. Vuelva a intentarlo.\n");
    } else {
        if (coincidencias > 1) {
            printf("\nHay %d pacientes con ese nombre. Consulte por ID para distinguirlos.\n", coincidencias);
        } else {
            send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);

            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            while (estado == RECORRIENDO) {
                recv(socket_fd, &aux_turno, sizeof(turnos_t), MSG_WAITALL);
                mostrar_turno(&aux_turno);
                recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            }
            recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

            if (resultado_funcion == 0) {
                printf("\nEl paciente no tiene turnos registrados.\n");
            } else {
                printf("\n%d resultados de busqueda\n", resultado_funcion);
            }
        }
    }
}

//-------------------------------------------------------------

void ConsultarTurnosPorResponsable_Menu1(int socket_fd){
    int resultado_funcion = 0, coincidencias = 0, estado = FIN;
    char nombre_ingresado[MAX_LETRAS_NOMBRE] = {0};
    char apellido_ingresado[MAX_LETRAS_NOMBRE] = {0};
    responsable_t aux_responsable;
    turnos_t aux_turno;

    printf("\nIngrese el nombre del responsable (o '-' para omitir): ");
    scanf(" %29[^\n]", nombre_ingresado);
    limpiar_buffer();

    printf("Ingrese el apellido del responsable (o '-' para omitir): ");
    scanf(" %29[^\n]", apellido_ingresado);
    limpiar_buffer();

    send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);
    send(socket_fd, apellido_ingresado, MAX_LETRAS_NOMBRE, 0);

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    while (estado == RECORRIENDO) {
        recv(socket_fd, &aux_responsable, sizeof(responsable_t), MSG_WAITALL);
        mostrar_responsable(&aux_responsable);
        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
    }
    recv(socket_fd, &coincidencias, sizeof(int), MSG_WAITALL);

    if (coincidencias == 0) {
        printf("\nNo existe ese responsable en la lista. Vuelva a intentarlo.\n");
    } else if (coincidencias > 1) {
        printf("\nHay %d responsables que coinciden. Especifique nombre y apellido completo.\n", coincidencias);
    } else {
        send(socket_fd, nombre_ingresado, MAX_LETRAS_NOMBRE, 0);
        send(socket_fd, apellido_ingresado, MAX_LETRAS_NOMBRE, 0);

        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux_turno, sizeof(turnos_t), MSG_WAITALL);
            mostrar_turno(&aux_turno);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

        if (resultado_funcion == 0) {
            printf("\nEl responsable no tiene turnos registrados.\n");
        } else {
            printf("\n%d resultados de busqueda\n", resultado_funcion);
        }
    }
}

//-------------------------------------------------------------

void ConsultarTurnosPorFecha_Menu1(int socket_fd){
    nfecha_t fecha_ingresada;
    turnos_t aux_turno;
    char fecha_texto[MAX_CARACTERES_FECHA];
    int dia = 0, mes = 0, anio = 0, resultado_funcion = 0, estado = FIN, dato_valido = 0, fecha_valida = 0;

    fecha_texto[0] = '\0';
    fecha_ingresada.valor = 0;

    printf("\nIngrese la fecha con el formato DD.MM.AAAA: ");
    scanf("%10s", fecha_texto);
    limpiar_buffer();

    // Se chequea el rango de cada dato antes de guardarlo en los campos de bits (dia: 5 bits, mes: 4 bits, año: 12 bits)
    if (sscanf(fecha_texto, "%d%*c%d%*c%d", &dia, &mes, &anio) == 3 &&
        dia >= 1 && dia <= 31 && mes >= 1 && mes <= 12 && anio >= 1 && anio <= 4095) {
        dato_valido = 1;
    }

    send(socket_fd, &dato_valido, sizeof(int), 0);

    if (dato_valido) {
        // Asignacion a los miembros de la estructura nfecha_t
        fecha_ingresada.bits1.dia = dia;
        fecha_ingresada.bits1.mes = mes;
        fecha_ingresada.bits1.anio = anio;

        printf("Dia: %02d | Mes: %02d | Anio: %04d\n", fecha_ingresada.bits1.dia, fecha_ingresada.bits1.mes, fecha_ingresada.bits1.anio);
        send(socket_fd, &fecha_ingresada, sizeof(nfecha_t), 0);

        recv(socket_fd, &fecha_valida, sizeof(int), MSG_WAITALL);

        if (fecha_valida) {
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            while (estado == RECORRIENDO) {
                recv(socket_fd, &aux_turno, sizeof(turnos_t), MSG_WAITALL);
                mostrar_turno(&aux_turno);
                recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            }
            recv(socket_fd, &resultado_funcion, sizeof(int), MSG_WAITALL);

            if (resultado_funcion == 0) {
                printf("\nNo hay turnos registrados en esa fecha.\n");
            } else {
                printf("\n%d resultados de busqueda\n", resultado_funcion);
            }
        } else {
            printf("Error: La fecha ingresada (%02d/%02d/%04d) no existe o es invalida.\n",
                   fecha_ingresada.bits1.dia, fecha_ingresada.bits1.mes, fecha_ingresada.bits1.anio);
        }
    } else {
        printf("Error: El formato ingresado no es valido.\n");
    }
}

//-------------------------------------------------------------

void MostrarListadoCompletoPacientes(int socket_fd){
    int estado = FIN;
    paciente_t aux;

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);

    if (estado == FIN) {
        printf("No hay pacientes registrados en el sistema.\n");
    } else {
        printf("\n=================== LISTADO DE PACIENTES ===================\n");
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux, sizeof(paciente_t), MSG_WAITALL);
            mostrar_paciente(&aux);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        printf("============================================================\n");
    }
}

//-------------------------------------------------------------

void MostrarListadoCompletoResponsable(int socket_fd){
    int estado = FIN;
    responsable_t aux;

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);

    if (estado == FIN) {
        printf("No hay responsables registrados en el sistema.\n");
    } else {
        printf("\n================== LISTADO DE RESPONSABLES =================\n");
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux, sizeof(responsable_t), MSG_WAITALL);
            mostrar_responsable(&aux);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        printf("============================================================\n");
    }
}
