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
	\fn     int agregar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se agrega un paciente a la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  client_fd Socket del cliente, u_pac Ultimo ID paciente, u_resp Ultimo ID responsable, pac Lista pacientes, resp Lista responsables, tur Lista turnos, tipos Vector tipos, cant_t Cantidad tipos, u_tipo Ultimo ID tipo
	\return int estado
*/
int agregar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int anadir_ordenado_p(nodo_paciente_t ** primero, paciente_t nuevo);
	\brief  Se añade a la lista el nuevo paciente 
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_paciente_t ** primero, paciente_t nuevo
	\return int estado
*/
int anadir_ordenado_p(nodo_paciente_t ** primero, paciente_t nuevo);


/**
	\fn     int modificar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se modifica un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  client_fd Socket del cliente, u_pac Ultimo ID paciente, u_resp Ultimo ID responsable, pac Lista pacientes, resp Lista responsables, tur Lista turnos, tipos Vector tipos, cant_t Cantidad tipos, u_tipo Ultimo ID tipo
	\return int estado
*/
int modificar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int eliminar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se elimina un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  client_fd Socket del cliente, u_pac Ultimo ID paciente, u_resp Ultimo ID responsable, pac Lista pacientes, resp Lista responsables, tur Lista turnos, tipos Vector tipos, cant_t Cantidad tipos, u_tipo Ultimo ID tipo
	\return int estado
*/
int eliminar_paciente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
	\fn     int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual);
	\brief  Se elimina un nodo de la lista
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_paciente_t ** lista, nodo_paciente_t * actual
	\return int estado
*/
int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual);


/**
	\fn     int buscar_nodo_pac_id(nodo_paciente_t * lista, int id_buscado, nodo_paciente_t ** encontrado);
	\brief  Busca un nodo de paciente por su ID en memoria
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nodo_paciente_t * lista, int id_buscado, nodo_paciente_t ** encontrado
	\return int cantidad de coincidencias (1 si lo encontro, 0 si no)
*/
int buscar_nodo_pac_id(nodo_paciente_t * lista, int id_buscado, nodo_paciente_t ** encontrado);

#endif
