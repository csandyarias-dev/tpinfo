#include "encabezadogeneral.h"
#include "socket.h"

int realizar_peticion(int sock, mensaje_t msg) {
    char respuesta[BUFFER_SIZE];
    int exito;

    exito = 0;
    memset(respuesta, 0, BUFFER_SIZE);

    
    if (send(sock, &msg, sizeof(mensaje_t), 0) > 0) {//envia la estructura sin mezclar datos
        
        if (recv(sock, respuesta, BUFFER_SIZE, 0) > 0) {// espera la respuesta completa del servidor
            printf("\n%s\n", respuesta);
            exito = 1;
        }
    }

    return exito;
}

