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
	\fn     int agregar_responsable(int client_fd, nodo_responsable_t **lista, int *ultimo_id);
	\brief  Recibe los datos del cliente y agrega el responsable a la lista dinámica.
*/
int agregar_responsable(int client_fd, nodo_responsable_t **lista, int *ultimo_id);

/**
	\fn     int anadirordenado_r(nodo_responsable_t ** primero, responsable_t nuevo_resp);
	\brief  Añade el responsable a la lista enlazada manteniendo el orden alfabético.
*/
int anadirordenado_r(nodo_responsable_t ** primero, responsable_t nuevo_resp);

/**
	\fn     int modificarResponsable(int client_fd, nodo_responsable_t **lista);
	\brief  Recibe los datos a modificar, reubica el nodo en la lista y responde al cliente.
*/
int modificarResponsable(int client_fd, nodo_responsable_t **lista);

/**
	\fn     int eliminar_nodo_r(nodo_responsable_t ** lista, nodo_responsable_t * actual);
	\brief  Libera la memoria de un nodo específico y reconecta la lista.
*/
int eliminar_nodo_r(nodo_responsable_t ** lista, nodo_responsable_t * actual);

/**
	\fn     int eliminarResponsable(int client_fd, nodo_responsable_t **lista);
	\brief  Recibe el ID a eliminar, borra el nodo y responde al cliente.
*/
int eliminarResponsable(int client_fd, nodo_responsable_t **lista);

#endif
