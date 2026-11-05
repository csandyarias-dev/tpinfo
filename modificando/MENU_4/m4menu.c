/**
	\file    main_menu4.c
	\brief   Programa principal para ejecutar y probar localmente el Menú 4 (Responsables).
	\author  Grupo las marmotas
	\date    2026.10.02
	\version 1.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include "../inc/encabezadogeneral.h"

int m4menu(int * u_pac, int * ultimo_id, nodo_paciente_t ** pac, nodo_responsable_t ** lista, nodo_turnos_t ** tur, tipopac_t ** tipos, int * cant_t, int * u_tipo) {
    int continuar = 1;
    int opcion = 0;
    
    p_menu4_t acciones[3] = {
        agregar_responsable, 
        modificarResponsable, 
        eliminarResponsable
    };

    while (continuar == 1) {
        printf("\n--- MENU 4: RESPONSABLES ---\n");
        printf("\t 1- Agregar responsable\n");
        printf("\t 2- Modificar responsable\n");
        printf("\t 3- Eliminar responsable\n");
        printf("\t 4- Volver\n");
        printf("Seleccione una opcion: ");
        if(leer_entero(&opcion)!=OK) opcion=0;

        if (opcion >= OPCION_AGREGAR && opcion < OPCION_VOLVER) acciones[opcion - 1](lista, ultimo_id);
        else if (opcion == OPCION_VOLVER) continuar = 0;
        else {
            printf("[ERROR] Opcion invalida. Intente nuevamente.\n");
        }
    }
    return OK;
}
