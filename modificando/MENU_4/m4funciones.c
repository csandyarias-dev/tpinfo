/**
	\file    m4funciones.c
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../inc/encabezadogeneral.h"

#define EXITO 0
#define ERROR_MEM 1
#define MAX_STR 30

int anadirordenado_r(nodo_responsable_t ** primero, responsable_t nuevo_resp) {
    nodo_responsable_t * nuevo = NULL;
    nodo_responsable_t * actual = NULL;
    nodo_responsable_t * anterior = NULL;
    int estado = ERROR_MEM;

    nuevo = (nodo_responsable_t *) malloc(sizeof(nodo_responsable_t));

    if (nuevo != NULL && primero != NULL) {
        nuevo->responsable = nuevo_resp;
        nuevo->sig = NULL;
        actual = *primero;

        while (actual != NULL && strcmp(nuevo_resp.apellido, actual->responsable.apellido) >= 0) {
            anterior = actual;
            actual = actual->sig;
        }

        if (anterior == NULL) {
            nuevo->sig = *primero;
            *primero = nuevo;
        } else {
            anterior->sig = nuevo;
            nuevo->sig = actual;
        }
        estado = EXITO;
    }
    return estado;
}

int agregar_responsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado) {
    responsable_t nuevo_resp;
    int estado = ERROR_MEM;

    if (primero != NULL && ultimo_ID_utilizado != NULL) {
        printf("Ingrese apellido del responsable: ");
        scanf(" %[^\n]", nuevo_resp.apellido);
        
        printf("Ingrese nombre del responsable: ");
        scanf(" %[^\n]", nuevo_resp.nombre);
        
        printf("Ingrese numero de telefono: ");
        scanf(" %lu", &nuevo_resp.telcont);

        nuevo_resp.responID = (*ultimo_ID_utilizado) + 1;

        estado = anadirordenado_r(primero, nuevo_resp);

        if (estado == EXITO) {
            printf("[Exito] Responsable cargado correctamente.\n");
            (*ultimo_ID_utilizado)++;
        } else {
            printf("[Error] No se pudo asignar memoria.\n");
        }
    }
    return estado;
}

int modificarResponsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado) {
    nodo_responsable_t * actual = NULL;
    int opcion = 0, id_buscado = 0, coincidencias = 0, estado = ERROR_MEM;
    char nombre_buscado[MAX_STR] = {0};

    if (primero != NULL && *primero != NULL) {
        printf("Modificar por: 1-Nombre 2-ID : ");
        leer_entero(&opcion); 

        if (opcion == 1) {
            printf("Ingrese nombre: ");
            scanf("%[^\n]", nombre_buscado);
            limpiar_buffer();
            actual = *primero;
            coincidencias= ConsultarCoincidencias_ResponsableNombre(*primero, nombre_buscado, &actual);
            
            if (coincidencias==1) modificar_nodo_r(actual, primero); 
            else if (coincidencias>1) opcion=2;
            else printf("[Error] Nombre no encontrado.\n"); 
        }

        if (opcion == 2) {
            printf("Ingrese ID exacto a modificar: ");
            leer_entero(&id_buscado);
            
            coincidencias= ConsultarCoincidencias_ResponsableID(*primero, id_buscado, &actual);
            
            if (coincidencias==1) modificar_nodo_r(actual, primero); 
            else if (coincidencias>1) opcion=2;
			else printf("[Error] No se pudo modificar (ID no encontrado).\n");
        }
    }
    return estado;
}

int modificar_nodo_r(nodo_responsable_t * actual, nodo_responsable_t ** lista){
	int campo, estado=ERROR; 
	
	printf("Que dato desea modificar? 1-Nombre 2-Apellido 3-Telefono: ");
                    leer_entero(&campo);
                    if (campo == 1) {
                        printf("Ingrese nuevo nombre: ");
                        scanf(" %[^\n]", actual->responsable.nombre);
                        estado = EXITO;
                    } 
                    else if (campo == 2) {
                        printf("Ingrese nuevo apellido: ");
                        scanf(" %[^\n]", actual->responsable.apellido);
                        limpiar_buffer();
                        estado = EXITO;
                    } 
                    else if (campo == 3) {
                        printf("Ingrese nuevo telefono: ");
                        scanf("%lu", &actual->responsable.telcont);
                        limpiar_buffer();
                        estado = EXITO;
                    } 
                    else {
                        printf("[Error] Campo invalido.\n");
                    }
     return estado;
	}

int eliminarResponsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado) {
    nodo_responsable_t * actual = NULL;
    nodo_responsable_t * anterior = NULL;
    int id_buscado = 0, estado = ERROR_MEM;

    if (primero != NULL && *primero != NULL) {
        printf("Ingrese el ID del responsable a eliminar: ");
        scanf("%d", &id_buscado);

        actual = *primero;
        while (actual != NULL && estado == ERROR_MEM) {
            if (actual->responsable.responID == id_buscado) {
                if (anterior == NULL) {
                    *primero = actual->sig;
                } else {
                    anterior->sig = actual->sig;
                }
                free(actual);
                estado = EXITO;
                printf("[Exito] Responsable eliminado del sistema.\n");
            } else {
                anterior = actual;
                actual = actual->sig;
            }
        }
        if (estado == ERROR_MEM) {
            printf("[Error] No existe responsable con ese ID.\n");
        }
    }
    return estado;
}
