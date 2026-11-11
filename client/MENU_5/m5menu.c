#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../inc/encabezadogeneral.h"

int m5menu(int socket_fd) {
    int opcion = 0, cliente_activo = 1, cmd = 0;

    ptr_m5_cliente_t acciones_m5[4] = {
        mostrar_tipos_animales_cliente,
        agregar_tipo_animal_cliente,
        modificar_tipo_animal_cliente,
        borrar_tipo_animal_cliente
    };

    while (cliente_activo == 1) {
        printf("\n--- MENU DE GESTION ---\n");
        printf("1. Listar animales\n");
        printf("2. Agregar animal\n");
        printf("3. Modificar animal\n");
        printf("4. Borrar animal\n");
        printf("5. Salir\n");
        printf("Seleccione una opcion: ");
        if (leer_entero(&opcion) != 1) {
            opcion = 0;
        }

        if (opcion >= 1 && opcion <= 4) {
            // CMD_MOSTRAR_TIPOS (17) a CMD_BORRAR_TIPO (20) = opcion + 16
            cmd = CMD_MOSTRAR_TIPOS + (opcion - 1);
            send(socket_fd, &cmd, sizeof(int), 0);
            acciones_m5[opcion - 1](socket_fd);
        } else if (opcion == 5) {
            cliente_activo = 0;
        } else {
            printf("Opcion invalida.\n");
        }
    }

    return OK;
}
