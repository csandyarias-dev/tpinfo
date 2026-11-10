#include "encabezadogeneral.h"
#include "socket.h"

int main() {
    int server_fd;
    int client_socket;
    int addrlen;
    int servidor_activo;
    int cliente_conectado;
    struct sockaddr_in address;
    
    
    tipopac_t *vector_tipos;
    int cant_tipos;
    int ultimo_tipoID;

    mensaje_t msg_recibido;
    char respuesta[BUFFER_SIZE];

    server_fd = 0;
    client_socket = 0;
    addrlen = sizeof(address);
    servidor_activo = 1;
    cliente_conectado = 0;
    vector_tipos = NULL;
    cant_tipos = 0;
    ultimo_tipoID = 0;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd >= 0) {
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = INADDR_ANY;
        address.sin_port = htons(PORT);

        if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) >= 0) {
            if (listen(server_fd, 1) >= 0) {
                printf("Servidor a la escucha en puerto %d...\n", PORT);

                while (servidor_activo == 1) {
                    client_socket = accept(server_fd, (struct sockaddr *)&address, (socklen_t *)&addrlen);
                    if (client_socket >= 0) {
                        printf("Cliente conectado.\n");
                        cliente_conectado = 1;

                        
                        while (cliente_conectado == 1) { //mantiene la conexion abierta mientras el cliente este enviando ordenes
                            memset(&msg_recibido, 0, sizeof(mensaje_t));
                            
                          
                            if (recv(client_socket, &msg_recibido, sizeof(mensaje_t), 0) > 0) { //bloqueante, espera leer el msj del cliente
                                
                                if (msg_recibido.accion == CMD_LISTAR) {
                                    mostrar_tipos_animales(&vector_tipos, &cant_tipos, respuesta);
                                } else if (msg_recibido.accion == CMD_AGREGAR) {
                                    agregar_tipo_animal(&vector_tipos, &cant_tipos, &ultimo_tipoID, msg_recibido.nombre, respuesta);
                                } else if (msg_recibido.accion == CMD_MODIFICAR) {
                                    modificar_tipo_animal(&vector_tipos, &cant_tipos, msg_recibido.id, msg_recibido.nombre, respuesta);
                                } else if (msg_recibido.accion == CMD_BORRAR) {
                                    borrar_tipo_animal(&vector_tipos, &cant_tipos, msg_recibido.id, respuesta);
                                } else if (msg_recibido.accion == CMD_SALIR) {
                                    strcpy(respuesta, "Conexion finalizada por el cliente.\n");
                                    cliente_conectado = 0;
                                }

                                send(client_socket, respuesta, strlen(respuesta) + 1, 0); //no sobreescribe, responde antes de aceptar otro pedido
                            } else {
                                cliente_conectado = 0;
                            }
                        }
                        close(client_socket);
                        printf("Cliente desconectado.\n");
                    }
                }
            }
        }
    }

    return 0;
}