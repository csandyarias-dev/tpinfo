
/**
	\file    menu_configuracion.h
	\brief   contiene las funciones pertenecientes al menu de configuracion
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#ifndef MENU_CONFIGURACION_H
#define MENU_CONFIGURACION_H

//--------------
//-- includes --
//--------------

//#include "encabezadogeneral.h"

//--------------
//-- Defines --
//--------------

#define MOSTRAR_TIPOS 1 
#define BORRAR_TIPO 4
#define VOLVER_MENU5 5  

//--------------
//-- includes --
//--------------
typedef void (*p_menu5_t)(tipopac_t **, int *, int *);

//----------------
//-- prototipos de funciones --
//----------------

/**
	\fn     void ejecutar_menu_configuracion(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Ejecuta el menu principal de configuracion
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void ejecutar_menu_configuracion(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
	\fn     void mostrar_tipos_animales(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Muestra la lista de tipos de animales registrados
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void mostrar_tipos_animales(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
	\fn     void agregar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Agrega un nuevo tipo de animal a la lista
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void agregar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
	\fn     void modificar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Modifica un tipo de animal existente en la lista
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void modificar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
	\fn     void borrar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Elimina un tipo de animal de la lista
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void borrar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
	\fn     void volver_menu_principal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
	\brief  Regresa al menu principal del sistema
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  tipopac_t ** vector_tipos
	\param  int * cant_tipos
	\param  int * ultimo_tipoID
	\return void
*/
void volver_menu_principal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

#endif
