
#include "encabezadogeneral.h"
#include "socket.h"


int main() {
    int sock;
    int opcion;
    int cliente_activo;
    struct sockaddr_in serv_addr;
    mensaje_t msg;

    sock = 0;
    opcion = 0;
    cliente_activo = 1;

    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock >= 0) {
        serv_addr.sin_family = AF_INET;
        serv_addr.sin_port = htons(PORT);

        if (inet_pton(AF_INET, SERVER_IP, &serv_addr.sin_addr) > 0) {
            if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) >= 0) {
                printf("Conectado exitosamente al servidor.\n");

                do {
                    memset(&msg, 0, sizeof(mensaje_t));

                    printf("\n--- MENU DE GESTION ---\n");
                    printf("1. Listar animales\n");
                    printf("2. Agregar animal\n");
                    printf("3. Modificar animal\n");
                    printf("4. Borrar animal\n");
                    printf("5. Salir\n");
                    printf("Seleccione una opcion: ");
                    scanf("%d", &opcion);
                    getchar();

                    if (opcion == 1) {
                        msg.accion = CMD_LISTAR;
                        realizar_peticion(sock, msg);
                    } else if (opcion == 2) {
                        msg.accion = CMD_AGREGAR;
                        printf("Ingrese el nombre del tipo de animal:\n");
                        scanf(" %49[^\n]", msg.nombre);
                        getchar();
                        realizar_peticion(sock, msg);
                    } else if (opcion == 3) {
                        msg.accion = CMD_MODIFICAR;
                        printf("Ingrese el ID del tipo de animal a modificar:\n");
                        scanf("%d", &msg.id);
                        getchar();
                        printf("Ingrese el nuevo nombre del tipo de animal:\n");
                        scanf(" %49[^\n]", msg.nombre);
                        getchar();
                        realizar_peticion(sock, msg);
                    } else if (opcion == 4) {
                        msg.accion = CMD_BORRAR;
                        printf("Ingrese el ID del tipo de animal a borrar:\n");
                        scanf("%d", &msg.id);
                        getchar();
                        realizar_peticion(sock, msg);
                    } else if (opcion == 5) {
                        msg.accion = CMD_SALIR;
                        realizar_peticion(sock, msg);
                        cliente_activo = 0;
                    } else {
                        printf("Opcion invalida.\n");
                    }

                } while (cliente_activo == 1);

            } else {
                printf("Error: No se pudo conectar al servidor.\n");
            }
        }
        close(sock);
    }

    return 0;
}