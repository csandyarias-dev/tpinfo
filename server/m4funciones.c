/**
	\file    m4funciones.c
	\brief   Contiene las funciones del servidor pertenecientes al menu 4 (Responsables)
	\author  Grupo Las Marmotas
	\date    2026.10.29
	\version 1.0.0
*/

#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>

int agregar_responsable(int client_fd, int *u_pac, int *ultimo_id, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    responsable_t nuevo;
    int estado = ERROR_MEMORIA;

    if (recv(client_fd, &nuevo, sizeof(responsable_t), 0) > 0) {
        nuevo.responID = (*ultimo_id) + 1;
        if (anadirordenado_r(lista, nuevo) == OK) {
            (*ultimo_id)++;
            estado = OK;
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int anadirordenado_r(nodo_responsable_t **lista, responsable_t nuevo_resp) {
    nodo_responsable_t *nuevo = NULL, *auxr = NULL, *anterior = NULL, *actual = NULL;
    int estado = ERROR_MEMORIA;

    auxr = (nodo_responsable_t *)malloc(sizeof(nodo_responsable_t));
    if (auxr != NULL) {
        nuevo = auxr;
        nuevo->responsable = nuevo_resp;
        nuevo->sig = NULL;
        actual = *lista;

        while ((actual != NULL) && (strcasecmp(actual->responsable.apellido, nuevo_resp.apellido) < 0)) {
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
    }
    return estado;
}

int buscar_nodo_resp_id(nodo_responsable_t *lista, int id_buscado, nodo_responsable_t **encontrado) {
    int coincidencias = 0;
    nodo_responsable_t *actual = lista;

    while (actual != NULL && coincidencias == 0) {
        if (actual->responsable.responID == id_buscado) {
            *encontrado = actual;
            coincidencias = 1;
        }
        actual = actual->sig;
    }
    return coincidencias;
}

int modificarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    responsable_t mod;
    int estado = ERROR;
    nodo_responsable_t *actual = NULL;

    if (recv(client_fd, &mod, sizeof(responsable_t), 0) > 0) {
        if (buscar_nodo_resp_id(*lista, mod.responID, &actual) == 1) {
            eliminar_nodo_r(lista, actual);
            estado = anadirordenado_r(lista, mod);
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int eliminarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int id_borrar = 0, estado = ERROR;
    nodo_responsable_t *actual = NULL;

    if (recv(client_fd, &id_borrar, sizeof(int), 0) > 0) {
        if (buscar_nodo_resp_id(*lista, id_borrar, &actual) == 1) {
            estado = eliminar_nodo_r(lista, actual);
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}

int eliminar_nodo_r(nodo_responsable_t **lista, nodo_responsable_t *actual) {
    int estado = ERROR;
    nodo_responsable_t *anterior = *lista;

    if (actual != NULL && *lista != NULL) {
        if (*lista == actual) {
            *lista = actual->sig;
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
