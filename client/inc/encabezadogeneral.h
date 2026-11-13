/**
	\file    encabezadogeneral.h
	\brief   Contiene las estructuras comunes a todo el programa
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

#ifndef ENCABEZADOGENERAL_H
#define ENCABEZADOGENERAL_H


//--------------
//-- Defines --
//--------------

#define ARCH_CLIENTE "cfg/cliente.cfg"

//-------------
//-- Structs --
//-------------

typedef struct {
    unsigned short int min : 6;
    unsigned short int vacio1 : 2;
    unsigned short int hora : 4;   
    unsigned short int vacio2 : 3; 
    unsigned short int am_pm : 1;  
} bits_hora_t;

typedef union {
    unsigned short int valor; 
    bits_hora_t bits;     
} nhora_t;

typedef struct {
    unsigned int anio : 12;  
    unsigned int vacio1 : 1; 
    unsigned int mes : 4;   
    unsigned int vacio2 : 1;  
    unsigned int dia : 5;    
    unsigned int vacio3 : 1;  
} bits_fecha_t;

typedef union {
    unsigned int valor;   
    bits_fecha_t bits1; 
} nfecha_t;

typedef struct tipoPac {
	unsigned char tipoID;
	char * nombre;
	} tipopac_t; 
	
	// PACIENTE
	
typedef struct Paciente{
	unsigned char tipoID;
	int pacID;
	char nombre [30];
	nfecha_t nacimiento; 
	int responID;
	}paciente_t;
	
typedef struct nodo_paciente{
	paciente_t paciente;
	struct nodo_paciente * sig;
	}nodo_paciente_t; 
	
	// RESPONSABLE
	
typedef struct Responsable{
	int responID;
	char nombre[30];
	char apellido[30];
	unsigned long int telcont;
	}responsable_t;
	
typedef struct nodo_responsable{
	responsable_t responsable;
	struct nodo_responsable * sig;
	}nodo_responsable_t; 
	
	// TURNOS
	
typedef struct Turnos{
	int responID; 
	int pacID; 
	nfecha_t fecha; 
	nhora_t hora;
	}turnos_t;
	
typedef struct nodo_turnos{
	turnos_t turnos;
	struct nodo_turnos * sig;
	}nodo_turnos_t; 
	

//-------------
//-- Enums --
//-------------

enum ERRORES_GENERALES{ERROR=-3, ERROR_MEMORIA, ERROR_ARCHIVO, OK=1};

enum COMANDOS_SOCKET {
    CMD_CONSULTAR_PAC_ID = 1,
    CMD_CONSULTAR_PAC_NOM,
    CMD_CONSULTAR_RESP_ID,
    CMD_CONSULTAR_RESP_NOM,
    CMD_TURNO_PAC_NOM,
    CMD_TURNO_RESP_NOM,
    CMD_TURNO_FECHA,
    CMD_LISTADO_PAC,
    CMD_LISTADO_RESP,
    CMD_AGREGAR_TURNO,
    CMD_AGREGAR_PAC,
    CMD_MODIFICAR_PAC,
    CMD_ELIMINAR_PAC,
    CMD_AGREGAR_RESP,
    CMD_MODIFICAR_RESP,
    CMD_ELIMINAR_RESP,
    CMD_MOSTRAR_TIPOS,
    CMD_AGREGAR_TIPO,
    CMD_MODIFICAR_TIPO,
    CMD_BORRAR_TIPO,
    CMD_SALIR
};

//-------------
//-- Defines --
//-------------

#define CONSULTAR_INFORMACION 1
#define MENU_CONFIGURACION 5
#define SALIR 6
#define EXITO 1

//-----------------------------------------
//-- typedef puntero a funcion principal --
//-----------------------------------------

typedef int (*puntero_menu_principal_t)(int client_socket_fd);

//-------------------------------
//-- prototipos de los 5 menus --
//-------------------------------

/**
	\fn      void menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);
	\brief   Muestra el menu 1 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param   int client_socket_fd
	\return  OK al finalizar la ejecucion del menu y volver al menu principal
*/
int m1menu(int client_socket_fd);


/**
	\fn      int agregar_turno(int client_socket_fd)
	\brief   Agrega un turno
	\author  Grupo Las Marmotas
	\date    2026.11.13
	\param   int client_socket_fd
	\return  int estado
*/
int agregar_turno(int client_socket_fd);


/**
	\fn      int m3menu(int client_socket_fd);
	\brief   Muestra el menu 3 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param   int client_socket_fd
	\return  OK al finalizar la ejecucion del menu y volver al menu principal
*/
int m3menu(int client_socket_fd);


/**
	\fn      int m4menu(int client_socket_fd);
	\brief   Muestra el menu 4 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param   int client_socket_fd
	\return  OK al finalizar la ejecucion del menu y volver al menu principal
*/
int m4menu(int client_socket_fd);


/**
	\fn      int m5menu(int client_socket_fd);
	\brief   Muestra el menu 5 y ejecuta la opcion elegida mediante un vector de punteros a funcion
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param   int client_socket_fd
	\return  OK al finalizar la ejecucion del menu y volver al menu principal
*/
int m5menu(int client_socket_fd);

//--------------
//-- Includes --
//--------------

#include "m1funciones.h"
#include "m3funciones.h"
#include "m4funciones.h"
#include "m5funciones.h"


//----------------
//-- Prototipos --
//----------------

/**
	\fn     int obtener_ip_puerto(int cant, char *argv[], char *ip, int *puerto);
	\brief  Obtiene la direccion IP y el puerto por medio del archivo de configuracion (cfg/cliente.cfg) o de los argumentos de la terminal
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int cant, char *argv[], char *ip, int *puerto
	\return int error = (0 si se leyó y guardó exitosamente la direccion IP y el puerto, de lo contrario 1)
*/
int obtener_ip_puerto(int cant, char *argv[], char *ip, int *puerto);


/**
	\fn     int conectar_servidor(char *ip, int server_port);
	\brief  Se conecta al servidor, devolviendo un numero positivo en caso de éxito, o de lo contrario uno negativo
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  char *ip, int server_port
	\return int client_socket_fd = (un numero positivo ej. 3, 4, 5... si la conexion fue exitosa, -1 si fue imposible establecer la conexion)
*/
int conectar_servidor(char *ip, int server_port);


/**
	\fn     int agregar_turno(int client_socket_fd);
	\brief  
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int client_socket_fd
	\return int estado
*/
int agregar_turno(int client_socket_fd);
      
#endif	
