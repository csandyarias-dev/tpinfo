/**
	\file    m4funciones_servidor.h
	\brief   Contienen las funciones pertenecientes al menu 4 para el SERVIDOR
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#ifndef MENU4_SERVIDOR_H
#define MENU4_SERVIDOR_H

//--------------
//-- Includes --
//--------------

#include "encabezadogeneral.h"

//----------------
//-- Prototipos --
//----------------

int agregar_responsable(int client_fd, int *u_pac, int *ultimo_id, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
int anadirordenado_r(nodo_responsable_t **lista, responsable_t nuevo_resp);
int buscar_nodo_resp_id(nodo_responsable_t *lista, int id_buscado, nodo_responsable_t **encontrado);
int modificarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
int eliminarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
int eliminar_nodo_r(nodo_responsable_t **lista, nodo_responsable_t *actual);

#endif
