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

extern int flag_alarma;
extern int flag_ctrlc;

#define ARCH_PACIENTES "dat/pacientes.dat"
#define ARCH_RESPONSABLES "dat/responsables.dat"
#define ARCH_TURNOS "dat/turnos.dat"
#define ARCH_TIPOS "dat/tipospac.lst"

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
	
typedef int (*puntero_cmd_servidor_t)(int, int *, int *, nodo_paciente_t **, nodo_responsable_t **, nodo_turnos_t **, tipopac_t **, int *, int *);

//-------------
//-- Enums --
//-------------

enum ERRORES_GENERALES{ERROR_CONEXION=-4, ERROR, ERROR_MEMORIA, ERROR_ARCHIVO, OK=1};

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
#define BACKLOG 10

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
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/

int iniciar_socket_servidor(int port);

/**
	\fn     void atender_cliente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
void atender_cliente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);


int ejecutar_comando_servidor(int client_fd, int comando, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo);
/**
	\fn     int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);
	\brief  Se carga un paciente al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID);


/**
	\fn    int cargar_responsables_archivo(nodo_responsable_t ** lista, int *ultimoResponID);
	\brief  Se carga un responsable al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int cargar_responsables_archivo(nodo_responsable_t ** lista, int *ultimoResponID);


/**
	\fn     int cargar_turnos_archivo(nodo_turnos_t ** lista);
	\brief  Se carga un turno al archivo
	\author Grupo Las Marmotas
	\date   2026.09.02
	\param  int ultimo_id, nodo_paciente_t ** primero_pac, nodo_responsable_t **  primero_resp, nodo_turnos_t ** primero_turnos
	\return int estado
*/
int cargar_turnos_archivo(nodo_turnos_t ** lista);

/**
	\fn      cargar_tipos_archivo(tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID)
	\brief   actualiza el vector dinamico de tipos desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID
	\return  int tipos_cargados
*/

int cargar_tipos_archivo(tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID);

/**
	\fn      importar_desde_archivo(int * ultimo_id_pac, int * ultimo_id_resp, nodo_paciente_t ** primero_pac, nodo_responsable_t ** primero_resp, nodo_turnos_t ** primero_turnos)
	\brief   importa todos los datos de los distintos archivos
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID
	\return  int tipos_cargados
*/


int importar_desde_archivo(int * ultimo_id_pac, int * ultimo_id_resp, nodo_paciente_t ** primero_pac, nodo_responsable_t ** primero_resp, nodo_turnos_t ** primero_turnos, tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_id_tipo);
 

/**
	\fn      int agregar_turno(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo)
	\brief   agrega un turno
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo
	\return  int estado
*/

int agregar_turno(int, int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo);

/**
	\fn      int comparar_fecha_hora(turnos_t a, turnos_t b)
	\brief   comparar fecha y hora (desendentemente)
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   turnos_t a, turnos_t b
	\return  int resultado
*/

int comparar_fecha_hora(turnos_t a, turnos_t b);

/**
	\fn      int aniadir_ordenado_t(nodo_turnos_t **lista, turnos_t nuevo)
	\brief   añade un turno de forma ordenada
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_turnos_t **lista, turnos_t nuevo
	\return  int estado
*/	

int aniadir_ordenado_t(nodo_turnos_t **lista, turnos_t nuevo);

	/**
	\fn    	 void alarma_handler(int nsig)
	\brief   setea la flag de actualizacion de archivos en 1
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   int nsig
	\return  void
*/

void alarma_handler(int nsig);



/**
	\fn    	 int act_archivos(nodo_paciente_t ** pac_primero, nodo_responsable_t ** resp_primero, nodo_turnos_t ** turnos_primero, tipopac_t * vector_tipos, int cant_tipos, int ultimo_id_tipo) 
	\brief   actualiza los archivos con los datos actuales
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_turnos_t **lista, turnos_t nuevo
	\return  int estado
*/
	
int act_archivos(nodo_paciente_t ** pac_primero, int ultimo_id_pac, nodo_responsable_t ** resp_primero, int ultimo_id_resp, nodo_turnos_t ** turnos_primero, tipopac_t * vector_tipos, int cant_tipos, int ultimo_id_tipo);
/**
	\fn    	 int act_pacientes_archivos(nodo_paciente_t ** primero) 
	\brief   actualiza el archivo pacientes.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** primero
	\return  int estado
*/

int act_pacientes_archivos(nodo_paciente_t ** primero, int ultimo_id);

/**
	\fn    	 int act_resp_archivos(nodo_responsable_t ** primero)
	\brief   actualiza el archivo responsables.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_responsable_t ** primero
	\return  int estado
*/

int act_resp_archivos(nodo_responsable_t ** primero, int ultimo_id);

/**
	\fn    	 int act_turnos_archivos(nodo_turnos_t ** primero)
	\brief   actualiza el archivo turnos.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_responsable_t ** primero
	\return  int estado
*/
    
int act_turnos_archivos(nodo_turnos_t ** primero);

/**
	\fn    	 int act_tipos_archivos(tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID)
	\brief   actualiza el archivo tipospac.lst
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID
	\return  int estado
*/

int act_tipos_archivos(tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID);

/**
	\fn    	 void liberar_memoria(nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** tipos, int cant_tipos)
	\brief   libera la memoria usada por el programa
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** tipos, int cant_tipos
	\return  void
*/
void liberar_memoria(nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** tipos, int cant_tipos);
	
#endif	
