#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int m3menu(int client_socket_fd) {
    int opcion = 0, loop = OK, estado = 0;
    p_menu3_t acciones_m3[3] = {
        agregar_paciente,
        modificar_paciente,
        eliminar_paciente
    };
    char cadena[3][11] = {"agregado", "modificado", "eliminado"};

    while (loop) {
        printf("\nIngrese:\n\t 1- Añadir paciente\n\t 2- Modificar paciente\n\t 3- Eliminar paciente\n\t 4- Volver\nOpcion: ");
        if (leer_entero(&opcion) != OK) opcion = 0;

        if (opcion >= OPCION_AGREGAR && opcion <= OPCION_ELIMINAR) {
            estado = acciones_m3[opcion - 1](client_socket_fd);
            if (estado == OK) printf("Paciente %s con exito!\n", cadena[opcion - 1]);
        } 
        else if (opcion == OPCION_VOLVER) {
            loop = 0;
        } 
        else {
            printf("[ERROR] Opcion invalida, intente nuevamente.\n");
        }
    }
    return OK;
}
