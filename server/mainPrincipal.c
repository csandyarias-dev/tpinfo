#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "inc/encabezadogeneral.h"

#define BACKLOG 10

int flag_alarma = 0;


int main(int argc, char *argv[]) {
    int port = 0, listen_fd = -1, client_fd = -1, client_len = 0, error = 0;
    int u_pac = 0, u_resp = 0, cant_tipos = 0, u_tipo = 0;
    struct sockaddr_in client_data;
    nodo_paciente_t *pac = NULL;
    nodo_responsable_t *resp = NULL;
    nodo_turnos_t *tur = NULL;
    tipopac_t *tipos = NULL;

    if (argc < 2 || (port = atoi(argv[1])) == 0) {
        printf("Uso: %s <PUERTO>\n", argv[0]);
        error = 1;
    }
    if (!error) {
        listen_fd = iniciar_socket_servidor(port);
        if (listen_fd == -1) error = 1;
    }
    if (!error) {
        importar_desde_archivo(&u_pac, &u_resp, &pac, &resp, &tur, &tipos, &cant_tipos, &u_tipo);
        signal(SIGALRM, alarma_handler);
        alarm(120);
        printf("Servidor corriendo en el puerto: %d.\n", port);

        while (!error) {
            if (flag_alarma) {
                act_archivos(&pac, u_pac, &resp, u_resp, &tur, tipos, cant_tipos, u_tipo);
                flag_alarma = 0;
            }
            client_len = sizeof(struct sockaddr_in);
            client_fd = accept(listen_fd, (struct sockaddr *)&client_data, (socklen_t *)&client_len);
            if (client_fd != -1) {
                printf("Conexion desde IP: %s.\n", inet_ntoa((struct in_addr)client_data.sin_addr));
                atender_cliente(client_fd, &u_pac, &u_resp, &pac, &resp, &tur, &tipos, &cant_tipos, &u_tipo);
                close(client_fd);
                printf("Conexion con cliente finalizada.\n");
            }
        }
        close(listen_fd);
    }
    return 0;
}
