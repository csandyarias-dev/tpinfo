/**
    \file    m5funciones_servidor.h
    \brief   Contiene las funciones del servidor pertenecientes al menu 5 (Tipos de animales)
    \author  Las Marmotas
    \version 2.0.0
*/

#ifndef M5FUNCIONES_SERVIDOR_H
#define M5FUNCIONES_SERVIDOR_H

//--------------
//-- Includes --
//--------------

#include "../inc/encabezadogeneral.h"

//----------------
//-- Prototipos --
//----------------

/**
    \fn      int mostrar_tipos_animales(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
    \brief   Recorre el vector de tipos de animales y los envia al cliente por socket
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   pac Puntero a la cabeza de la lista de pacientes
    \param   resp Puntero a la cabeza de la lista de responsables
    \param   tur Puntero a la cabeza de la lista de turnos
    \param   vector_tipos Puntero al vector dinamico de tipos de animales
    \param   cant_tipos Puntero a la cantidad actual de tipos registrados
    \param   ultimo_tipoID Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de elementos enviados
*/
int mostrar_tipos_animales(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
    \fn      int agregar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
    \brief   Recibe un nombre, actualiza el vector dinamico asignando un nuevo ID y responde el estado
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   pac Puntero a la cabeza de la lista de pacientes
    \param   resp Puntero a la cabeza de la lista de responsables
    \param   tur Puntero a la cabeza de la lista de turnos
    \param   vector_tipos Puntero al vector dinamico de tipos de animales
    \param   cant_tipos Puntero a la cantidad actual de tipos registrados
    \param   ultimo_tipoID Puntero al ultimo ID historico generado para tipos
    \return  int estado (OK o ERROR)
*/
int agregar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
    \fn      int modificar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
    \brief   Recibe ID y nombre, busca en el vector, actualiza el dato y responde el estado
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   pac Puntero a la cabeza de la lista de pacientes
    \param   resp Puntero a la cabeza de la lista de responsables
    \param   tur Puntero a la cabeza de la lista de turnos
    \param   vector_tipos Puntero al vector dinamico de tipos de animales
    \param   cant_tipos Puntero a la cantidad actual de tipos registrados
    \param   ultimo_tipoID Puntero al ultimo ID historico generado para tipos
    \return  int estado (OK o ERROR)
*/
int modificar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

/**
    \fn      int borrar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);
    \brief   Recibe un ID, elimina el tipo del vector, reasigna memoria y responde el estado
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   pac Puntero a la cabeza de la lista de pacientes
    \param   resp Puntero a la cabeza de la lista de responsables
    \param   tur Puntero a la cabeza de la lista de turnos
    \param   vector_tipos Puntero al vector dinamico de tipos de animales
    \param   cant_tipos Puntero a la cantidad actual de tipos registrados
    \param   ultimo_tipoID Puntero al ultimo ID historico generado para tipos
    \return  int estado (OK o ERROR)
*/
int borrar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID);

#endif // M5FUNCIONES_SERVIDOR_H
