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
	\brief  Se agrega un responsable al servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param int socket_fd
	\return int estado
*/
int agregar_responsable(int socket_fd);


/**
	\fn    int buscar_responsable_cliente(int socket_fd, responsable_t *resp_out);
	\brief  Se busca al responsable en el servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd, responsable_t *resp_out
	\return int encontrado
*/
int buscar_responsable_cliente(int socket_fd, responsable_t *resp_out);


/**
	\fn     int pedir_modificacion_resp(responsable_t * resp);
	\brief  Se pide modificar al responsable al servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  responsable_t * resp
	\return int estado
*/
int pedir_modificacion_resp(responsable_t * resp);


/**
	\fn     int modificarResponsable(int socket_fd);
	\brief  Se modifica al responsable
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return int modificado
*/
int modificarResponsable(int socket_fd);


/**
	\fn     int eliminarResponsable(int socket_fd);
	\brief  Se elimina al responsable
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return int eliminado
*/
int eliminarResponsable(int socket_fd);


/**
	\fn     int leer_lu(unsigned long int * valor);
	\brief  Lee un numero entero largo (ej: numero de telefono) y protege al sistema de entradas invalidas
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  unsigned long int * valor
	\return int es_numero
*/
int leer_lu(unsigned long int * valor);

#endif
