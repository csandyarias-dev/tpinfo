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

typedef int (*p_menu3_t)(nodo_paciente_t **, int *, tipopac_t ** tipos, int * cant_t, int * u_tipo);

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
	\fn     int agregarPaciente(nodo_paciente_t ** primero, int * ultimo_ID_utilizado);
	\brief  Se agrega un paciente a la lista
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_paciente_t ** primero, int * ultimo_ID_utilizado
	\return int estado
*/
int agregar_paciente(nodo_paciente_t ** primero, int * ultimo_ID_utilizado, tipopac_t ** tipos, int * cant_t, int * u_tipo);

/**
	\fn     int anadir_ordenado(nodo_paciente_t ** primero, paciente_t nuevo);
	\brief  Se añade a la lista el nuevo paciente 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_paciente_t ** primero, paciente_t nuevo
	\return int estado
*/
int anadir_ordenado_p(nodo_paciente_t ** primero, paciente_t nuevo);

/**
	\fn     int modificarPaciente(nodo_paciente_t ** primero);
	\brief  Se modifica un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_paciente_t ** primero
	\return int estado
*/
int modificar_paciente(nodo_paciente_t ** primero, int * ultimo_ID_utilizado, tipopac_t ** tipos, int * cant_t, int * u_tipo);

/**
	\fn     int modificarNodo(nodo_paciente_t ** elegido);
	\brief  Se modifica un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_paciente_t ** elegido 
	\return int estado
*/
int modificar_nodo(nodo_paciente_t * actual, nodo_paciente_t ** lista);

/**
	\fn     int eliminarPaciente(nodo_paciente_t ** primero);
	\brief  Se elimina un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_paciente_t ** primero
	\return int estado
*/
int eliminar_paciente(nodo_paciente_t ** primero, int * ultimo_ID_utilizado, tipopac_t ** tipos, int * cant_t, int * u_tipo);

/**
	\fn     int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual, nodo_paciente_t * anterior)
	\brief  Se elimina un nodo de la lista
	\author Grupo Las Marmotas
	\date   2026.09.30
	\param  nodo_paciente_t ** lista, nodo_paciente_t * actual, nodo_paciente_t * anterior
	\return int estado
*/
int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual); 


#endif
