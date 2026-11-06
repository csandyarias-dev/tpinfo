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
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int agregar_paciente(int socket_fd);


/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int buscar_paciente_cliente(int socket_fd, paciente_t *pac_out);


/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int pedir_modificacion_pac(paciente_t *pac);


/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int modificar_paciente(int socket_fd);


/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int eliminar_paciente(int socket_fd);


/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int m3menu(int client_socket_fd);

#endif
