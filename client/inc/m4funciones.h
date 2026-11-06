/**
	\file    m4funciones_cliente.h
	\brief   Contienen las funciones pertenecientes al menu 4 para el CLIENTE
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#ifndef MENU4_CLIENTE_H
#define MENU4_CLIENTE_H

//--------------
//-- Includes --
//--------------

#include "encabezadogeneral.h"

//--------------
//-- typedef --
//--------------

typedef int (*p_menu4_t)(int);


//----------------
//-- Prototipos --
//----------------

/**
	\fn     int agregar_responsable(int socket_fd);
	\brief  Envía los datos de un nuevo responsable al servidor.
*/
int agregar_responsable(int socket_fd);

/**
	\fn     int buscar_responsable_cliente(int socket_fd, responsable_t *resp_out);
	\brief  Solicita al servidor la busqueda de un responsable por nombre o ID.
*/
int buscar_responsable_cliente(int socket_fd, responsable_t *resp_out);

/**
	\fn     int pedir_modificacion_resp(responsable_t * resp);
	\brief  Pide por consola los nuevos datos del responsable a modificar.
*/
int pedir_modificacion_resp(responsable_t * resp);

/**
	\fn     int modificarResponsable(int socket_fd);
	\brief  Envía la solicitud de modificación al servidor.
*/
int modificarResponsable(int socket_fd);

/**
	\fn     int eliminarResponsable(int socket_fd);
	\brief  Envía la solicitud de eliminación al servidor.
*/
int eliminarResponsable(int socket_fd);

/**
	\fn     int m4menu(int client_socket_fd);
	\brief  Ejecuta el menu 4 del lado del cliente.
*/
int m4menu(int client_socket_fd);

#endif
