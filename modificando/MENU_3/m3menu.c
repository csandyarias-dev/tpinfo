/**
	\file    <Nombre del archivo>
	\brief   <Que contiene el archivo>
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día> 
	\version <Versión (ejemplo: 1.0.0)>

	Compilación: 	gcc -c main.c -o main_ejemplo.o -Wall
					gcc -c funciones.c -o funciones.o -Wall
	Linkeo: 		gcc main_ejemplo.o funciones.o -o ejecutable -Wall
	Ejecución: 		./ejecutable
*/


//--------------
//-- Includes --
//--------------

#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//-------------
//-- Defines --
//-------------

/**
	\fn      <Prototipo de la función>
	\brief   <Función de la función>
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   <Parámetro A (si no tiene no se pone)>
	\param   <Parámetro B (si no tiene no se pone)>
	\return  <Lo que retorna>
*/

int m3menu(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** tipos, int * cant_t, int * u_tipo) {
    int opcion = 0, loop = OK, estado=0;

    p_menu3_t acciones_m3[3] = {
        agregar_paciente,
        modificar_paciente,
        eliminar_paciente
    };
    char cadena[3][11]={"agregado", "modificado", "eliminado"};
	
    while (loop) {
        printf("\nIngrese:\n\t 1- Añadir paciente\n\t 2- Modificar paciente\n\t 3- Eliminar paciente\n\t 4- Volver\nOpcion: ");
        if(leer_entero(&opcion)!=OK) opcion=0;
		
        if (opcion >= OPCION_AGREGAR && opcion <= OPCION_ELIMINAR) {
            estado=acciones_m3[opcion - 1](pac, u_pac,tipos,cant_t,u_tipo);
            if (estado>0) printf("Paciente %s con exito!", cadena[opcion-1]);
        } else if (opcion == OPCION_VOLVER) {
            loop = 0;
        } else {
            printf("[ERROR] Opcion invalida, intente nuevamente.\n");
        }
    }
    return OK;
}
