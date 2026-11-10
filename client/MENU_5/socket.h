
#ifndef ENCABEZADOGENERAL_H
#define ENCABEZADOGENERAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define BUFFER_SIZE 512


typedef enum {
    LISTAR = 1,
    AGREGAR,
    MODIFICAR,
    BORRAR,
    SALIR
} accion_t;



void mostrar_tipos_animales(tipopac_t **vector_tipos, int *cant_tipos, char *respuesta);
void agregar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID, char *nombre, char *respuesta);
void modificar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int id, char *nuevo_nombre, char *respuesta);
void borrar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int id, char *respuesta);

#endif