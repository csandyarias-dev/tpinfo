/**
	\file    m1_menu.c
	\brief   Menu 1 (consultar informacion) del TP final, implementado con punteros a funcion
	\author  Las Marmotas
	\date    2026.10.29
	\version 1.0.0

	Compilación: 	gcc -c m1_menu.c -o m1_menu.o -Wall
					gcc -c m1_desarrollodefunciones.c -o m1_desarrollodefunciones.o -Wall
	Linkeo: 		gcc main.o m1_menu.o m1_desarrollodefunciones.o -o ejecutable -Wall
	Ejecución: 		./ejecutable
*/


//--------------
//-- Includes --
//--------------
#include <stdio.h>
#include <stdlib.h>
#include "../inc/encabezadogeneral.h"

enum m1{pac_id=1, pac_nombre, responsable_id, responsable_nombre, turnos_pacientes, turnos_responsables, turnos_fecha, listado_pacientes, listado_responsables, volver};

//-------------
//-- Defines --
//-------------

// Tipo de puntero a funcion: todas las opciones del menu comparten esta firma
typedef void (*funcion_menu1_t)(nodo_paciente_t *, nodo_responsable_t *, nodo_turnos_t *);


/**
	\fn      static void opcion_pac_id(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 1: consulta un paciente por ID
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_pac_id(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_paciente_t *paciente_encontrado = NULL;

	ConsultarPacientePorID_Menu1(lista_pac, lista_resp, &paciente_encontrado);
}


/**
	\fn      static void opcion_pac_nombre(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 2: consulta un paciente por nombre
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_pac_nombre(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_paciente_t *paciente_encontrado = NULL;

	ConsultarPacientePorNombre_Menu1(lista_pac, lista_resp, &paciente_encontrado);
}


/**
	\fn      static void opcion_responsable_id(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 3: consulta un responsable por ID
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_responsable_id(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_responsable_t *responsable_encontrado = NULL;

	ConsultarResponsablePorID_Menu1(lista_resp, &responsable_encontrado);
}


/**
	\fn      static void opcion_responsable_nombre(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 4: consulta un responsable por nombre
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_responsable_nombre(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_responsable_t *responsable_encontrado = NULL;

	ConsultarResponsablePorNombre_Menu1(lista_resp, &responsable_encontrado);
}


/**
	\fn      static void opcion_turnos_pacientes(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 5: consulta los turnos de un paciente
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_turnos_pacientes(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_turnos_t **turnos_encontrados = NULL;

	ConsultarTurnosPorPacientes_Menu1(lista_pac, lista_turnos, &turnos_encontrados);

	// El vector dinamico no se usa despues de mostrar los turnos, se libera
	if (turnos_encontrados != NULL) {
		free(turnos_encontrados);
	}
}


/**
	\fn      static void opcion_turnos_responsables(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 6: consulta los turnos de un responsable
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_turnos_responsables(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_turnos_t **turnos_encontrados = NULL;

	ConsultarTurnosPorResponsable_Menu1(lista_resp, lista_turnos, &turnos_encontrados);

	// El vector dinamico no se usa despues de mostrar los turnos, se libera
	if (turnos_encontrados != NULL) {
		free(turnos_encontrados);
	}
}


/**
	\fn      static void opcion_turnos_fecha(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 7: consulta los turnos de una fecha
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_turnos_fecha(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	nodo_turnos_t **turnos_encontrados = NULL;

	ConsultarTurnosPorFecha_Menu1(lista_turnos, &turnos_encontrados);

	// El vector dinamico no se usa despues de mostrar los turnos, se libera
	if (turnos_encontrados != NULL) {
		free(turnos_encontrados);
	}
}


/**
	\fn      static void opcion_listado_pacientes(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 8: muestra el listado completo de pacientes
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_listado_pacientes(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	MostrarListadoCompletoPacientes(lista_pac);
}


/**
	\fn      static void opcion_listado_responsables(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Opcion 9: muestra el listado completo de responsables
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/
static void opcion_listado_responsables(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos){
	MostrarListadoCompletoResponsables(lista_resp);
}


/**
	\fn      void menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Muestra el menu 1 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author  Las Marmotas
	\date    2026.10.29
	\param   lista_pac: lista de pacientes
	\param   lista_resp: lista de responsables
	\param   lista_turnos: lista de turnos
	\return  No retorna
*/

int m1menu(int * u_pac, int * u_resp, nodo_paciente_t ** lista_pac, nodo_responsable_t ** lista_resp, nodo_turnos_t ** lista_turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo){
	int opcion=0;
	int loop=OK;

	// El indice de cada funcion es (opcion - pac_id), en el mismo orden que el enum m1
	funcion_menu1_t acciones[volver - pac_id] = {
		opcion_pac_id,
		opcion_pac_nombre,
		opcion_responsable_id,
		opcion_responsable_nombre,
		opcion_turnos_pacientes,
		opcion_turnos_responsables,
		opcion_turnos_fecha,
		opcion_listado_pacientes,
		opcion_listado_responsables
	};

	while (loop) {
		printf("\nIngrese \n \t 1- Consultar paciente por ID \n \t 2- Consultar paciente por nombre \n \t 3- Consultar responsable por ID \n \t 4- Consultar responsable por nombre \n \t 5- Consultar turnos por paciente \n \t 6- Consultar turnos por responsable \n \t 7- Consultar turnos por fecha \n \t 8- Mostrar listado completo de pacientes \n \t 9- Mostrar listado completo de responsables \n \t 10- Volver \n Opcion: ");

		// Si no se ingreso un numero, la opcion queda invalida
		if (!leer_entero(&opcion)) {
			opcion = 0;
		}

		if (opcion >= pac_id && opcion < volver) {
			acciones[opcion - pac_id](*lista_pac, *lista_resp, *lista_turnos);
		} else {
			if (opcion == volver) {
				loop = 0;
			} else {
				printf("Opcion invalida, intente nuevamente\n");
			}
		}
	}
	return OK;
}
