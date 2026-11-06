/**
	\file    m4funciones.c
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
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

int agregar_responsable(int client_fd, nodo_responsable_t **lista, int *ultimo_id) {
    responsable_t nuevo_resp;
    int estado = ERROR_MEM;

    if (recv(client_fd, &nuevo_resp, sizeof(responsable_t), 0) > 0) {
        nuevo_resp.responID = (*ultimo_id) + 1;
        if (anadirordenado_r(lista, nuevo_resp) == EXITO) {
            (*ultimo_id)++;
            estado = EXITO;
        }
        send(client_fd, &estado, sizeof(int), 0);
    }
    return estado;
}
