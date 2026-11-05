/**
	\file    mainPrincipal.c
	\brief   <Que contiene el archivo>
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día> 
	\version <Versión (ejemplo: 1.0.0)>

	Compilación: 	gcc -c mainPrincipal.c -o mainPrincipal.o -Wall
					gcc -c funciones.c -o funciones.o -Wall
	Linkeo: 		gcc main_ejemplo.o funciones.o -o ejecutable -Wall
	Ejecución: 		./ejecutable
*/

//--------------
//-- Includes --
//--------------
#include "inc/encabezadogeneral.h"
#include <stdio.h>
#include <unistd.h>  
#include <signal.h>  

//--------------
//-- Defines --
//--------------

int flag_alarma=0;
int flag_modificacion=0;

/**
	\fn      <Prototipo de la función>
	\brief   <Función de la función>
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   <Parámetro A (si no tiene no se pone)>
	\param   <Parámetro B (si no tiene no se pone)>
	\return  <Lo que retorna>
*/

int main(int cant, char * arg[]) {
    int continuar = OK, entrada = 0, ultimo_id_pac = 0, ultimo_id_resp = 0;
    int cant_tipos = 0, ultimo_id_tipo = 0;
    nodo_paciente_t * primero_pac = NULL;
    nodo_responsable_t * primero_resp = NULL; 
    nodo_turnos_t * primero_turnos = NULL;
    tipopac_t * vector_tipos = NULL;

    puntero_menu_principal_t menu_principal[5] = {
        m1menu,
        agregar_turno,
        m3menu,
        m4menu,
        m5menu
    };

    signal(SIGALRM, alarma_handler); 
    alarm(120);
	
    if(importar_desde_archivo(&ultimo_id_pac, &ultimo_id_resp, &primero_pac, &primero_resp, &primero_turnos, &vector_tipos, &cant_tipos, &ultimo_id_tipo)==OK) printf("Archivos cargados con exito");
	else (printf("Error"));
	
    while (continuar) {
        if (flag_alarma) {
            act_archivos(&primero_pac, ultimo_id_pac, &primero_resp, ultimo_id_resp, &primero_turnos, vector_tipos, cant_tipos, ultimo_id_tipo);
            flag_alarma = 0;
        }
		
		printf("\n--- MENU PRINCIPAL ---\n");
        printf("\nIngrese:\n\t1- Consultar informacion. \
						   \n\t2- Agregar turno.\
						    \n\t3- Acceder al menu pacientes.\
						     \n\t4- Acceder al menu responsables.\
						      \n\t5- Acceder al menu configuracion.\
						       \n\t6- Salir \
						        \nOpcion: ");
        if(leer_entero(&entrada)!=OK) entrada=0;
       

        if (entrada >= CONSULTAR_INFORMACION && entrada <= MENU_CONFIGURACION) {
            menu_principal[entrada - 1](&ultimo_id_pac, &ultimo_id_resp, &primero_pac, &primero_resp, &primero_turnos, &vector_tipos, &cant_tipos, &ultimo_id_tipo);
        } 
        else if (entrada == SALIR) {
            continuar = 0;
            act_archivos(&primero_pac, ultimo_id_pac, &primero_resp, ultimo_id_resp, &primero_turnos, vector_tipos, cant_tipos, ultimo_id_tipo);
            liberar_memoria(&primero_pac, &primero_resp, &primero_turnos, &vector_tipos, cant_tipos);
            printf("Sesion finalizada\n");
            
        } 
        else {
            printf("Entrada invalida, intente nuevamente.\n");
            entrada=0;
        }
    }
    return 0;
}
