/**
	\file    m4menu.c
	\brief   Programa principal para el Menú 4 (Responsables) - Arquitectura Cliente
	\author  Grupo las marmotas
	\date    2026.10.02
	\version 1.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/encabezadogeneral.h"

int m4menu(int client_socket_fd) {
    int opcion = 0, loop = OK, estado = 0;
    
    p_menu4_t acciones_m4[3] = {
        agregar_responsable, 
        modificarResponsable, 
        eliminarResponsable
    };
    
    char cadena[3][11] = {"agregado", "modificado", "eliminado"};

    while (loop) {
        printf("\n--- MENU 4: RESPONSABLES ---\n");
        printf("\t 1- Agregar responsable\n");
        printf("\t 2- Modificar responsable\n");
        printf("\t 3- Eliminar responsable\n");
        printf("\t 4- Volver\n");
        printf("Seleccione una opcion: ");
        
        if (leer_entero(&opcion) != OK) opcion = 0;

        if (opcion >= OPCION_AGREGAR && opcion <= OPCION_ELIMINAR) {
            estado = acciones_m4[opcion - 1](client_socket_fd);
            if (estado == OK || estado == EXITO) {
                printf("Responsable %s con exito!\n", cadena[opcion - 1]);
            }
        } 
        else if (opcion == OPCION_VOLVER) {
            loop = 0;
        } 
        else {
            printf("[ERROR] Opcion invalida. Intente nuevamente.\n");
        }
    }
    return OK;
}
