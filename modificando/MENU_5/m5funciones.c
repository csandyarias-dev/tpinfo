#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include "../inc/encabezadogeneral.h"

void mostrar_tipos_animales(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID){
    int i;
    i = 0;
    if(*cant_tipos == 0) printf("No hay tipos de animales registrados\n");

    else {
        printf("Lista de tipos de animales:\n");
        for(i = 0; i < *cant_tipos; i++){
            printf("ID: %d, Nombre: %s\n", (*vector_tipos)[i].tipoID, (*vector_tipos)[i].nombre);
        }
    }
}
 
 void agregar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    tipopac_t *vector_aux = NULL;
    char buffer[50] = {0};

    vector_aux = (tipopac_t *)realloc(*vector_tipos, (*cant_tipos + 1) * sizeof(tipopac_t));
    if (vector_aux == NULL) {
        printf("No hay suficiente memoria para agregar al animal\n");
    } 
    else { 
        *vector_tipos = vector_aux;

        printf("Ingrese el nombre del tipo de animal:\n");
        scanf(" %49[^\n]", buffer); // SOPORTA ESPACIOS
        limpiar_buffer();

        (*vector_tipos)[*cant_tipos].nombre = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
        if ((*vector_tipos)[*cant_tipos].nombre == NULL) {
            printf("No hay suficiente memoria para el nombre del animal\n");
        } 
        else { 
            strcpy((*vector_tipos)[*cant_tipos].nombre, buffer);
            (*ultimo_tipoID)++;
            (*vector_tipos)[*cant_tipos].tipoID = *ultimo_tipoID;
            (*cant_tipos)++;
            printf("El tipo de animal se agrego correctamente\n");
        }
    }
    return; 
}

void modificar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID){
    int i = 0;
    int id_buscado = 0;
    int p_encontrada = -1;
    char buffer[50] = {0}; 
    char *nombre_aux = NULL; 

    if(*cant_tipos == 0){
        printf("No hay tipos de animales registrados\n");
    }
    else{
        printf("Modificar tipo de animal\n");
        printf("Ingrese el ID del tipo de animal a modificar:\n");
        leer_entero(&id_buscado);

        for(i = 0; i < *cant_tipos; i++){
            if((*vector_tipos)[i].tipoID == id_buscado){
                p_encontrada = i;
            }
        }
        if(p_encontrada == -1){
            printf("No se encontro el animal con ID %d\n", id_buscado);
        }
        else{
            printf("Ingrese el nuevo nombre del tipo de animal:\n");
            scanf(" %49[^\n]", buffer); // [^\n] ES PARA QUE SOPORTE ESPACIOS
            limpiar_buffer();
            
            nombre_aux = (char *)realloc((*vector_tipos)[p_encontrada].nombre, (strlen(buffer) + 1) * sizeof(char));
            if (nombre_aux != NULL) {
                (*vector_tipos)[p_encontrada].nombre = nombre_aux;
                strcpy((*vector_tipos)[p_encontrada].nombre, buffer);
                printf("El animal con ID %d se modifico \n", id_buscado);
            } else {
                printf("No hay suficiente memoria para modificar el nombre\n");
            }
        }
    }
    return; 
}

void borrar_tipo_animal(tipopac_t **vector_tipos, int *cant_tipos, int *ultimo_tipoID) {
    int i, id_buscado = 0, p_encontrada = ERROR, nuevo_tamano, flag=0;
    tipopac_t *vector_aux = NULL;

    if (*cant_tipos == 0) printf("No hay tipos de animales registrados\n");
    else {	
		mostrar_tipos_animales(vector_tipos, cant_tipos, ultimo_tipoID);
		printf("\n Ingrese el ID del tipo de animal a borrar:\n");
		scanf("%d", &id_buscado);

		for (i = 0; (i < *cant_tipos)&&(flag==0); i++) {
			if ((*vector_tipos)[i].tipoID == id_buscado) {
				p_encontrada = i;
				flag=1;
			}
		}
		if (p_encontrada == ERROR) {
			printf("No se encontro el animal con ID %d\n", id_buscado);
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
				printf("El animal con ID %d se borro\n", id_buscado);
			} else {
				vector_aux = (tipopac_t *)realloc(*vector_tipos, nuevo_tamano * sizeof(tipopac_t));
				if (vector_aux == NULL) printf("No se pudo reducir la memoria\n");
				else {
					*vector_tipos = vector_aux;
					(*cant_tipos)--;
					printf("El animal con ID %d se borro\n", id_buscado);
				}
			}
		}
	}
}
