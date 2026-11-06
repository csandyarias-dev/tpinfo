#include "inc/encabezadogeneral.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int cant, char *argv[]) {
    int continuar = OK, entrada = 0, server_port = 0, cmd_salir=CMD_SALIR;
    int client_socket_fd = -1;
    char ip_servidor[30] = {0};
    puntero_menu_principal_t menu_principal[5] = {m1menu, agregar_turno, m3menu, m4menu, m5menu};

    if (!obtener_ip_puerto(cant, argv, ip_servidor, &server_port)) {
        client_socket_fd = conectar_servidor(ip_servidor, server_port);
    }

    if (client_socket_fd != -1) {
        printf("Cliente conectado al servidor.\n");
        while (continuar) {
            printf("\n--- MENU PRINCIPAL ---\n");
            printf("1- Consultar informacion.\n2- Agregar turno.\n3- Menu pacientes.\n"
                   "4- Menu responsables.\n5- Menu configuracion.\n6- Salir\nOpcion: ");
            if (leer_entero(&entrada) != OK) entrada = 0;

            if (entrada >= CONSULTAR_INFORMACION && entrada <= MENU_CONFIGURACION) {
                menu_principal[entrada - 1](client_socket_fd);
            } else if (entrada == SALIR) {
                send(client_socket_fd, &cmd_salir, sizeof(int), 0);
                continuar = 0;
            } else {
                printf("Entrada invalida, intente nuevamente.\n");
            }
        }
        close(client_socket_fd);
        printf("Conexion con servidor finalizada.\n");
    }
    return 0;
}
