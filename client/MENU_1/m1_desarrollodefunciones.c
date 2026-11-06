
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

    printf("\nIngrese el ID del paciente: ");

    if (leer_entero(&id_ingresado)) {
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
	\fn     void ConsultarResponsablePorNombre_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado);
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
	\fn     void ConsultarTurnosPorFecha_Menu1(nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
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