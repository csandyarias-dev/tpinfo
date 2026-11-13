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

/**
	\fn     int agregar_responsable(int client_fd, int *u_pac, int *ultimo_id, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se agrega un responsable nuevo a la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int client_fd, int *u_pac, int *ultimo_id, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo
	\return int estado
*/
int agregar_responsable(int client_fd, int *u_pac, int *ultimo_id, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int anadirordenado_r(nodo_responsable_t **lista, responsable_t nuevo_resp);
	\brief  Se añade el nuevo responsable a la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_responsable_t **lista, responsable_t nuevo_resp
	\return int estado
*/
int anadirordenado_r(nodo_responsable_t **lista, responsable_t nuevo_resp);


/**
	\fn     int buscar_nodo_resp_id(nodo_responsable_t *lista, int id_buscado, nodo_responsable_t **encontrado);
	\brief  Busca un responsable por su ID y devuelve su posición de memoria
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_responsable_t *lista, int id_buscado, nodo_responsable_t **encontrado
	\return int coincidencias (1 si lo encontro, 0 si no)
*/
int buscar_nodo_resp_id(nodo_responsable_t *lista, int id_buscado, nodo_responsable_t **encontrado);


/**
	\fn     int modificarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se modifica un responsable de la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo
	\return int estado
*/
int modificarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int eliminarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se elimina un responsable de la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo
	\return int estado
*/
int eliminarResponsable(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **lista, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int eliminar_nodo_r(nodo_responsable_t **lista, nodo_responsable_t *actual);
	\brief  Se elimina un nodo de la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_responsable_t **lista, nodo_responsable_t *actual
	\return int estado
*/
int eliminar_nodo_r(nodo_responsable_t **lista, nodo_responsable_t *actual);

#endif
