/**
	\file    m3funciones.c
	\brief   Contienen las funciones pertenecientes al menu 3
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

//--------------
//-- Includes --
//--------------

#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>

//---------------
//-- Funciones --
//---------------

int agregar_paciente(int client_fd, int *ultimo_id, int *u_resp, nodo_paciente_t **lista, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    paciente_t nuevo;
    int estado = ERROR_MEMORIA;

    if (recv(client_fd, &nuevo, sizeof(paciente_t), 0) > 0) {
        nuevo.pacID = (*ultimo_id) + 1;
        if (anadir_ordenado_p(lista, nuevo) == OK) {
            (*ultimo_id)++;
            estado = OK;
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int anadir_ordenado_p(nodo_paciente_t ** lista, paciente_t cliente) {
    nodo_paciente_t * nuevo = NULL, * auxp = NULL, * anterior = NULL, * actual = NULL;
    int estado = ERROR_MEMORIA; 
    
    auxp = (nodo_paciente_t *) malloc(sizeof(nodo_paciente_t)); 
    
    if (auxp != NULL) { 
        nuevo = auxp; 
        
        nuevo->paciente = cliente; 
        nuevo->sig = NULL; 
        
        actual = *lista;
        
        while ((actual != NULL) && (strcasecmp(actual->paciente.nombre, cliente.nombre) < 0)) {
            anterior = actual;
            actual = actual->sig;                                                              
        }
        
        if (anterior != NULL) { 
            anterior->sig = nuevo; 
            nuevo->sig = actual;
        } else {
            nuevo->sig = *lista; 
            *lista = nuevo;    
        }
        estado = OK;
    } else {
        estado = ERROR_MEMORIA;
    }
    
    return estado; 
}

int buscar_nodo_pac_id(nodo_paciente_t * lista, int id_buscado, nodo_paciente_t ** encontrado) {
    int coincidencias = 0;
    nodo_paciente_t * actual = lista;

    while (actual != NULL && coincidencias == 0) {
        if (actual->paciente.pacID == id_buscado) {
            *encontrado = actual;
            coincidencias = 1;
        }
        actual = actual->sig;
    }
    return coincidencias;
}

int modificar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    paciente_t mod;
    int estado = ERROR;
    nodo_paciente_t *actual = NULL;

    if (recv(client_fd, &mod, sizeof(paciente_t), 0) > 0) {
        if (buscar_nodo_pac_id(*lista, mod.pacID, &actual) == 1) {
            eliminar_nodo(lista, actual);
            estado = anadir_ordenado_p(lista, mod);
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int eliminar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int id_borrar = 0, estado = ERROR;
    nodo_paciente_t *actual = NULL;

    if (recv(client_fd, &id_borrar, sizeof(int), 0) > 0) {
        if (buscar_nodo_pac_id(*lista, id_borrar, &actual) == 1) {
            estado = eliminar_nodo(lista, actual);
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual) {
    int estado = ERROR; 
    nodo_paciente_t * anterior = *lista;
    
    if (actual != NULL && *lista != NULL) {
        if (*lista == actual) {
            *lista = actual->sig; // Si es el primero de la lista
        } else {
            while (anterior != NULL && anterior->sig != actual) {
                anterior = anterior->sig;
            }
            if (anterior != NULL) {
                anterior->sig = actual->sig;
            }
        }
        free(actual);
        estado = OK; 
    }
    return estado; 
}
  
