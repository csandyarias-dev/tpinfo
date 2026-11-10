#include "../inc/encabezadogeneral.h"
#include "socket.h"

void mostrar_tipos_animales(tipopac_t **vector_tipos, int *cant_tipos, char *respuesta) {
    int i;
    char linea[100];

    i = 0;
    memset(respuesta, 0, BUFFER_SIZE);

    if (*cant_tipos == 0) {
        strcpy(respuesta, "No hay tipos de animales registrados\n");
    } else {
        strcpy(respuesta, "Lista de tipos de animales:\n");
        for (i = 0; i < *cant_tipos; i++) {
            snprintf(linea, sizeof(linea), "ID: %d, Nombre: %s\n", (*vector_tipos)[i].tipoID, (*vector_tipos)[i].nombre);
            strcat(respuesta, linea);
        }
    }
}

void agregar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID, char *nombre, char *respuesta) {
    tipopac_t *vector_aux;

    vector_aux = NULL;
    memset(respuesta, 0, BUFFER_SIZE);

    vector_aux = (tipopac_t *)realloc(*vector_tipos, (*cant_tipos + 1) * sizeof(tipopac_t));
    if (vector_aux == NULL) {
        strcpy(respuesta, "No hay suficiente memoria para agregar al animal\n");
    } else {
        *vector_tipos = vector_aux;
        (*vector_tipos)[*cant_tipos].nombre = (char *)malloc((strlen(nombre) + 1) * sizeof(char));

        if ((*vector_tipos)[*cant_tipos].nombre == NULL) {
            strcpy(respuesta, "No hay suficiente memoria para el nombre del animal\n");
        } else {
            strcpy((*vector_tipos)[*cant_tipos].nombre, nombre);
            (*ultimo_tipoID)++;
            (*vector_tipos)[*cant_tipos].tipoID = *ultimo_tipoID;
            (*cant_tipos)++;
            strcpy(respuesta, "El tipo de animal se agrego correctamente\n");
        }
    }
}

void modificar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int id, char *nuevo_nombre, char *respuesta) {
    int i;
    int p_encontrada;
    char *nombre_aux;

    i = 0;
    p_encontrada = -1;
    nombre_aux = NULL;
    memset(respuesta, 0, BUFFER_SIZE);

    if (*cant_tipos == 0) {
        strcpy(respuesta, "No hay tipos de animales registrados\n");
    } else {
        for (i = 0; (i < *cant_tipos) && (p_encontrada == -1); i++) {
            if ((*vector_tipos)[i].tipoID == id) {
                p_encontrada = i;
            }
        }

        if (p_encontrada == -1) {
            snprintf(respuesta, BUFFER_SIZE, "No se encontro el animal con ID %d\n", id);
        } else {
            nombre_aux = (char *)realloc((*vector_tipos)[p_encontrada].nombre, (strlen(nuevo_nombre) + 1) * sizeof(char));
            if (nombre_aux != NULL) {
                (*vector_tipos)[p_encontrada].nombre = nombre_aux;
                strcpy((*vector_tipos)[p_encontrada].nombre, nuevo_nombre);
                snprintf(respuesta, BUFFER_SIZE, "El animal con ID %d se modifico\n", id);
            } else {
                strcpy(respuesta, "No hay suficiente memoria para modificar el nombre\n");
            }
        }
    }
}

void borrar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int id, char *respuesta) {
    int i;
    int p_encontrada;
    int nuevo_tamano;
    tipopac_t *vector_aux;

    i = 0;
    p_encontrada = -1;
    nuevo_tamano = 0;
    vector_aux = NULL;
    memset(respuesta, 0, BUFFER_SIZE);

    if (*cant_tipos == 0) {
        strcpy(respuesta, "No hay tipos de animales registrados\n");
    } else {
        for (i = 0; (i < *cant_tipos) && (p_encontrada == -1); i++) {
            if ((*vector_tipos)[i].tipoID == id) {
                p_encontrada = i;
            }
        }

        if (p_encontrada == -1) {
            snprintf(respuesta, BUFFER_SIZE, "No se encontro el animal con ID %d\n", id);
        } else {
            free((*vector_tipos)[p_encontrada].nombre);
            for (i = p_encontrada; i < *cant_tipos - 1; i++) {
                (*vector_tipos)[i] = (*vector_tipos)[i + 1];
            }

            nuevo_tamano = *cant_tipos - 1;

            if (nuevo_tamano == 0) {
                free(*vector_tipos);
                *vector_tipos = NULL;
                (*cant_tipos)--;
                snprintf(respuesta, BUFFER_SIZE, "El animal con ID %d se borro\n", id);
            } else {
                vector_aux = (tipopac_t *)realloc(*vector_tipos, nuevo_tamano * sizeof(tipopac_t));
                if (vector_aux == NULL) {
                    strcpy(respuesta, "No se pudo reducir la memoria\n");
                } else {
                    *vector_tipos = vector_aux;
                    (*cant_tipos)--;
                    snprintf(respuesta, BUFFER_SIZE, "El animal con ID %d se borro\n", id);
                }
            }
        }
    }
}
