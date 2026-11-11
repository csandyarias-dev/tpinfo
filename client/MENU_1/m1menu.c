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
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../inc/encabezadogeneral.h"

//-------------
//-- Defines --
//-------------

// Tipo de puntero a funcion: todas las opciones del menu comparten esta firma
typedef void (*funcion_menu1_t)(int);

/**
	\fn      void menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Muestra el menu 1 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author  Las Marmotas
	\date    2026.10.29
	\param   int socket_fd
	\return  No retorna
*/

int m1menu(int socket_fd) {
    int opcion = 0, loop = OK;

    funcion_menu1_t acciones_m1[9] = {
        ConsultarPacientePorID_Menu1,
        ConsultarPacientePorNombre_Menu1,
        ConsultarResponsablePorID_Menu1,
        ConsultarResponsablePorNombre_Menu1,
        ConsultarTurnosPorPacientes_Menu1,
        ConsultarTurnosPorResponsable_Menu1,
        ConsultarTurnosPorFecha_Menu1,
        MostrarListadoCompletoPacientes,
        MostrarListadoCompletoResponsable
    };

    while (loop) {
        printf("\nIngrese:\n\t1- Consultar paciente por ID\n\t2- Consultar paciente por nombre\n\t3- Consultar responsable por ID\n\t4- Consultar responsable por nombre y apellido\n\t5- Consultar turnos por paciente\n\t6- Consultar turnos por responsable\n\t7- Consultar turnos por fecha\n\t8- Mostrar listado completo de pacientes\n\t9- Mostrar listado completo de responsables\n\t10- Volver\nOpcion: ");
        if (leer_entero(&opcion) != OK) {
            opcion = 0;
        }

        if (opcion >= 1 && opcion <= 9) {
            // Enviamos el comando (1 al 9) al servidor y ejecutamos la funcion del cliente
            send(socket_fd, &opcion, sizeof(int), 0);
            acciones_m1[opcion - 1](socket_fd);
        } else if (opcion == 10) {
            loop = 0;
        } else {
            printf("Opcion invalida, intente nuevamente.\n");
        }
    }

    return OK;
}
