/**
	\file    m3funciones.h
	\brief   Contienen las funciones pertenecientes al menu 3
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/



#ifndef MENU3_H
#define MENU3_H

//--------------
//-- Includes --
//--------------

//#include "encabezadogeneral.h"

//--------------
//-- typedef --
//--------------

typedef int (*p_menu3_t)(int);

//--------------
//-- Defines --
//--------------

#define OPCION_AGREGAR 1
#define OPCION_ELIMINAR 3
#define OPCION_VOLVER 4

//-------------
//-- Structs --
//-------------

enum OPCIONESM3{NOMBRE=1, FECHA_NACIMIENTO, ID_RESPONSABLE};

//----------------
//-- Prototipos --
//----------------


/**
	\fn     int agregar_paciente(int socket_fd);
	\brief  Se agrega un paciente al servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return int estado
*/
int agregar_paciente(int socket_fd);


/**
	\fn     int buscar_paciente_cliente(int socket_fd, paciente_t *pac_out);
	\brief  Se busca un paciente en el servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd, paciente_t *pac_out
	\return int encontrado
*/
int buscar_paciente_cliente(int socket_fd, paciente_t *pac_out);


/**
	\fn     int pedir_modificacion_pac(paciente_t *pac);
	\brief  Se pide la modificacion de un paciente
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  paciente_t *pac
	\return int estado
*/
int pedir_modificacion_pac(paciente_t *pac);


/**
	\fn     int modificar_paciente(int socket_fd);
	\brief  Se modifica al paciente
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return int modificado
*/
int modificar_paciente(int socket_fd);


/**
	\fn     int eliminar_paciente(int socket_fd);
	\brief  Se elimina un paciente del servidor
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return int eliminado
*/
int eliminar_paciente(int socket_fd);

#endif
