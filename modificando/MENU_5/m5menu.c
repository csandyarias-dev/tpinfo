#include "../inc/encabezadogeneral.h"
#include <stdio.h>

int m5menu(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID) {
    int opcion = 0; 
    int continuar = OK;

    p_menu5_t acciones_m5[4] = {
        mostrar_tipos_animales,
        agregar_tipo_animal,
        modificar_tipo_animal,
        borrar_tipo_animal
    };

    while (continuar == OK) {
        printf("\nMENU DE CONFIGURACION\n");
        printf("1- Mostrar tipos de animales\n"
               "2- Agregar tipo de animal\n"
               "3- Modificar tipo de animal\n"
               "4- Borrar tipo de animal\n"
               "5- Volver al menu principal\n"
               "Seleccione una opcion: ");
		if(leer_entero(&opcion)!=OK) opcion=0;

        if (opcion >= MOSTRAR_TIPOS && opcion <= BORRAR_TIPO) {
            acciones_m5[opcion - 1](vector_tipos, cant_tipos, ultimo_tipoID);
        } 
        else if (opcion == VOLVER_MENU5) {
            printf("Regresando al menu principal\n");
            continuar = 0;
        } 
        else {
            printf("Opcion invalida, ingresar una opcion de las dadas\n");
        }
    }
    return OK;
}
