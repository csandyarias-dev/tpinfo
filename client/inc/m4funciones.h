/**
	\file    m4funciones.h
	\brief   Contienen las funciones pertenecientes al menu 4
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#ifndef MENU4_H
#define MENU4_H

//--------------
//-- Includes --
//--------------

//#include "encabezadogeneral.h"


//--------------
//-- typedef --
//--------------
typedef int (*p_menu4_t)(nodo_responsable_t **, int *);

//----------------
//-- Prototipos --
//----------------

/**
	\fn     int agregar_responsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado);
	\brief  Se agrega un responsable a la lista
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  void 
	\return int estado
*/
int agregar_responsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado);

/**
	\fn     int anadirordenado_r(nodo_responsable_t ** primero, responsable_t nuevo);
	\brief  Se añade a la lista el nuevo responsable 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  void 
	\return int estado
*/
int anadirordenado_r(nodo_responsable_t ** primero, responsable_t nuevo);

/**
	\fn     int modificarResponsable(nodo_responsable_t ** primero);
	\brief  Se modifica un responsable de la lista 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  void 
	\return int estado
*/
int modificarResponsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado);

/**
	\fn     int modificar_nodo_r(nodo_responsable_t * actual, nodo_responsable_t ** lista);
	\brief  Se modifica un responsable del nodo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  nodo_responsable_t * actual, nodo_responsable_t ** lista
	\return int estado
*/
int modificar_nodo_r(nodo_responsable_t * actual, nodo_responsable_t ** lista);

/**
	\fn     int eliminarResponsable(nodo_responsable_t ** primero);
	\brief  Se elimina un paciente de la lista 
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  void 
	\return int estado
*/
int eliminarResponsable(nodo_responsable_t ** primero, int * ultimo_ID_utilizado);

#endif
