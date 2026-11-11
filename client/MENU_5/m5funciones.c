#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "../inc/encabezadogeneral.h"

#define MAX_NOMBRE_TIPO 50

#ifndef RECORRIENDO
#define RECORRIENDO 1
#define FIN 0
#endif

void mostrar_tipos_animales_cliente(int socket_fd) {
    int estado = FIN;
    unsigned char tipoID = 0;
    char nombre[MAX_NOMBRE_TIPO];

    recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);

    if (estado == FIN) {
        printf("No hay tipos de animales registrados\n");
    } else {
        printf("Lista de tipos de animales:\n");
        while (estado == RECORRIENDO) {
            recv(socket_fd, &tipoID, sizeof(unsigned char), MSG_WAITALL);
            recv(socket_fd, nombre, MAX_NOMBRE_TIPO, MSG_WAITALL);
            printf("ID: %d, Nombre: %s\n", tipoID, nombre);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
    }
}

void agregar_tipo_animal_cliente(int socket_fd) {
    int resultado = ERROR;
    char nombre[MAX_NOMBRE_TIPO] = {0};

    printf("Ingrese el nombre del tipo de animal:\n");
    scanf(" %49[^\n]", nombre);
    limpiar_buffer();

    send(socket_fd, nombre, MAX_NOMBRE_TIPO, 0);
    recv(socket_fd, &resultado, sizeof(int), MSG_WAITALL);

    if (resultado == OK) {
        printf("El tipo de animal se agrego correctamente\n");
    } else {
        printf("No hay suficiente memoria para agregar al animal\n");
    }
}

void modificar_tipo_animal_cliente(int socket_fd) {
    int cant_tipos = 0, id = 0, dato_valido = 0, resultado = ERROR;
    char nuevo_nombre[MAX_NOMBRE_TIPO] = {0};

    recv(socket_fd, &cant_tipos, sizeof(int), MSG_WAITALL);

    if (cant_tipos == 0) {
        printf("No hay tipos de animales registrados\n");
    } else {
        printf("Ingrese el ID del tipo de animal a modificar:\n");
        dato_valido = leer_entero(&id);
        send(socket_fd, &dato_valido, sizeof(int), 0);

        if (dato_valido) {
            printf("Ingrese el nuevo nombre del tipo de animal:\n");
            scanf(" %49[^\n]", nuevo_nombre);
            limpiar_buffer();

            send(socket_fd, &id, sizeof(int), 0);
            send(socket_fd, nuevo_nombre, MAX_NOMBRE_TIPO, 0);
            recv(socket_fd, &resultado, sizeof(int), MSG_WAITALL);

            if (resultado == OK) {
                printf("El animal con ID %d se modifico\n", id);
            } else {
                printf("No se encontro el animal con ID %d\n", id);
            }
        } else {
            printf("Error: el ID debe ser un numero.\n");
        }
    }
}

void borrar_tipo_animal_cliente(int socket_fd) {
    int cant_tipos = 0, id = 0, dato_valido = 0, resultado = ERROR;

    recv(socket_fd, &cant_tipos, sizeof(int), MSG_WAITALL);

    if (cant_tipos == 0) {
        printf("No hay tipos de animales registrados\n");
    } else {
        printf("Ingrese el ID del tipo de animal a borrar:\n");
        dato_valido = leer_entero(&id);
        send(socket_fd, &dato_valido, sizeof(int), 0);

        if (dato_valido) {
            send(socket_fd, &id, sizeof(int), 0);
            recv(socket_fd, &resultado, sizeof(int), MSG_WAITALL);

            if (resultado == OK) {
                printf("El animal con ID %d se borro\n", id);
            } else {
                printf("No se encontro el animal con ID %d\n", id);
            }
        } else {
            printf("Error: el ID debe ser un numero.\n");
        }
    }
}


