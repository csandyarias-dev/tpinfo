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

// 17: CMD_MOSTRAR_TIPOS
int mostrar_tipos_animales(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    int i = 0, estado = FIN;
    char nombre_fijo[MAX_NOMBRE_TIPO];

    for (i = 0; i < *cant_tipos; i++) {
        estado = RECORRIENDO;
        memset(nombre_fijo, 0, MAX_NOMBRE_TIPO);
        strncpy(nombre_fijo, (*vector_tipos)[i].nombre, MAX_NOMBRE_TIPO - 1);

        send(socket_fd, &estado, sizeof(int), 0);
        send(socket_fd, &((*vector_tipos)[i].tipoID), sizeof(unsigned char), 0);
        send(socket_fd, nombre_fijo, MAX_NOMBRE_TIPO, 0);
    }

    estado = FIN;
    send(socket_fd, &estado, sizeof(int), 0);

    return *cant_tipos;
}

// 18: CMD_AGREGAR_TIPO
int agregar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    tipopac_t *vector_aux = NULL;
    char nombre[MAX_NOMBRE_TIPO] = {0};
    int resultado = ERROR;

    recv(socket_fd, nombre, MAX_NOMBRE_TIPO, MSG_WAITALL);
    nombre[MAX_NOMBRE_TIPO - 1] = '\0';

    vector_aux = (tipopac_t *)realloc(*vector_tipos, (*cant_tipos + 1) * sizeof(tipopac_t));
    if (vector_aux != NULL) {
        *vector_tipos = vector_aux;
        (*vector_tipos)[*cant_tipos].nombre = (char *)malloc((strlen(nombre) + 1) * sizeof(char));

        if ((*vector_tipos)[*cant_tipos].nombre != NULL) {
            strcpy((*vector_tipos)[*cant_tipos].nombre, nombre);
            (*ultimo_tipoID)++;
            (*vector_tipos)[*cant_tipos].tipoID = (unsigned char)(*ultimo_tipoID);
            (*cant_tipos)++;
            resultado = OK;
        }
    }

    send(socket_fd, &resultado, sizeof(int), 0);
    return resultado;
}

// 19: CMD_MODIFICAR_TIPO
int modificar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    int i = 0, id = 0, p_encontrada = -1, dato_valido = 0, resultado = ERROR;
    char nuevo_nombre[MAX_NOMBRE_TIPO] = {0};
    char *nombre_aux = NULL;

    send(socket_fd, cant_tipos, sizeof(int), 0);

    if (*cant_tipos > 0) {
        recv(socket_fd, &dato_valido, sizeof(int), MSG_WAITALL);
        if (dato_valido) {
            recv(socket_fd, &id, sizeof(int), MSG_WAITALL);
            recv(socket_fd, nuevo_nombre, MAX_NOMBRE_TIPO, MSG_WAITALL);
            nuevo_nombre[MAX_NOMBRE_TIPO - 1] = '\0';

            for (i = 0; (i < *cant_tipos) && (p_encontrada == -1); i++) {
                if ((*vector_tipos)[i].tipoID == id) {
                    p_encontrada = i;
                }
            }

            if (p_encontrada != -1) {
                nombre_aux = (char *)realloc((*vector_tipos)[p_encontrada].nombre, (strlen(nuevo_nombre) + 1) * sizeof(char));
                if (nombre_aux != NULL) {
                    (*vector_tipos)[p_encontrada].nombre = nombre_aux;
                    strcpy((*vector_tipos)[p_encontrada].nombre, nuevo_nombre);
                    resultado = OK;
                }
            }
            send(socket_fd, &resultado, sizeof(int), 0);
        }
    }

    return resultado;
}

// 20: CMD_BORRAR_TIPO
int borrar_tipo_animal(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    int i = 0, id = 0, p_encontrada = -1, nuevo_tamano = 0, dato_valido = 0, resultado = ERROR;
    tipopac_t *vector_aux = NULL;

    send(socket_fd, cant_tipos, sizeof(int), 0);

    if (*cant_tipos > 0) {
        recv(socket_fd, &dato_valido, sizeof(int), MSG_WAITALL);
        if (dato_valido) {
            recv(socket_fd, &id, sizeof(int), MSG_WAITALL);

            for (i = 0; (i < *cant_tipos) && (p_encontrada == -1); i++) {
                if ((*vector_tipos)[i].tipoID == id) {
                    p_encontrada = i;
                }
            }

            if (p_encontrada != -1) {
                free((*vector_tipos)[p_encontrada].nombre);
                for (i = p_encontrada; i < *cant_tipos - 1; i++) {
                    (*vector_tipos)[i] = (*vector_tipos)[i + 1];
                }

                nuevo_tamano = *cant_tipos - 1;
                if (nuevo_tamano == 0) {
                    free(*vector_tipos);
                    *vector_tipos = NULL;
                    (*cant_tipos)--;
                    resultado = OK;
                } else {
                    vector_aux = (tipopac_t *)realloc(*vector_tipos, nuevo_tamano * sizeof(tipopac_t));
                    if (vector_aux != NULL) {
                        *vector_tipos = vector_aux;
                        (*cant_tipos)--;
                        resultado = OK;
                    }
                }
            }
            send(socket_fd, &resultado, sizeof(int), 0);
        }
    }

    return resultado;
}
