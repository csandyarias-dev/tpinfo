/**
    \file    m5funciones_cliente.h
    \brief   Contiene las funciones del cliente pertenecientes al menu 5 (Tipos de animales)
    \author  Las Marmotas
    \version 2.0.0
*/

#ifndef M5FUNCIONES_CLIENTE_H
#define M5FUNCIONES_CLIENTE_H

//--------------
//-- Includes --
//--------------

#include "../inc/encabezadogeneral.h"

typedef void (*ptr_m5_cliente_t)(int);

//----------------
//-- Prototipos --
//----------------

/**
    \fn      int m5menu(int socket_fd);
    \brief   Muestra el menu de configuracion y gestiona el envio de comandos al servidor
    \author  Las Marmotas
    \param   socket_fd Descriptor del socket conectado al servidor
    \return  int estado (OK)
*/
int m5menu(int socket_fd);

/**
    \fn      void mostrar_tipos_animales_cliente(int socket_fd);
    \brief   Solicita al servidor la lista de tipos de animales y la imprime en pantalla
    \author  Las Marmotas
    \param   socket_fd Descriptor del socket conectado al servidor
    \return  void
*/
void mostrar_tipos_animales_cliente(int socket_fd);

/**
    \fn      void agregar_tipo_animal_cliente(int socket_fd);
    \brief   Pide un nombre por teclado y le solicita al servidor agregarlo al sistema
    \author  Las Marmotas
    \param   socket_fd Descriptor del socket conectado al servidor
    \return  void
*/
void agregar_tipo_animal_cliente(int socket_fd);

/**
    \fn      void modificar_tipo_animal_cliente(int socket_fd);
    \brief   Pide ID y nuevo nombre por teclado y le solicita al servidor la modificacion
    \author  Las Marmotas
    \param   socket_fd Descriptor del socket conectado al servidor
    \return  void
*/
void modificar_tipo_animal_cliente(int socket_fd);

/**
    \fn      void borrar_tipo_animal_cliente(int socket_fd);
    \brief   Pide el ID de un animal por teclado y le solicita al servidor su eliminacion
    \author  Las Marmotas
    \param   socket_fd Descriptor del socket conectado al servidor
    \return  void
*/
void borrar_tipo_animal_cliente(int socket_fd);

#endif // M5FUNCIONES_CLIENTE_H
