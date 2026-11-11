/**
	\file    m4funciones.c
	\author  Grupo las marmotas
	\date    2026.11.11
	\version 1.0.0
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include "../inc/encabezadogeneral.h"

#ifndef RECORRIENDO
#define RECORRIENDO 1
#define FIN 0
#endif

int agregar_responsable(int socket_fd) {
    responsable_t nuevo_resp;
    int estado = ERROR, cmd = CMD_AGREGAR_RESP; 

    memset(&nuevo_resp, 0, sizeof(responsable_t));

    printf("Ingrese apellido del responsable: ");
    scanf(" %29[^\n]", nuevo_resp.apellido);
    limpiar_buffer();
    
    printf("Ingrese nombre del responsable: ");
    scanf(" %29[^\n]", nuevo_resp.nombre);
    limpiar_buffer();
    
    printf("Ingrese numero de telefono: ");
    if (leer_lu(&(nuevo_resp.telcont))) { 
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, &nuevo_resp, sizeof(responsable_t), 0);
        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        
        if (estado != OK) printf("[Error] No se pudo agregar responsable en el servidor.\n");
    } else {
        printf("Entrada de telefono invalida.\n");
    }
    
    return estado;
}

int buscar_responsable_cliente(int socket_fd, responsable_t *resp_out) {
    int opcion = 0, id_buscado = 0, coincidencias = 0, cmd = 0, encontrado = 0, estado = FIN, dato_valido = 0;
    char nombre[30] = {0}, apellido[30] = {0};
    responsable_t aux;

    do {
        printf("Ingrese 1 para buscar por nombre/apellido y 2 para buscar por ID: ");
        leer_entero(&opcion);
    } while ((opcion != 1) && (opcion != 2));

    if (opcion == 1) {
        printf("Ingrese nombre (o '-' para omitir): ");
        scanf(" %29[^\n]", nombre);
        limpiar_buffer();
        printf("Ingrese apellido (o '-' para omitir): ");
        scanf(" %29[^\n]", apellido);
        limpiar_buffer();

        cmd = CMD_CONSULTAR_RESP_NOM;
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, nombre, 30, 0);
        send(socket_fd, apellido, 30, 0);

        recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        while (estado == RECORRIENDO) {
            recv(socket_fd, &aux, sizeof(responsable_t), MSG_WAITALL);
            mostrar_responsable(&aux);
            *resp_out = aux;
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
        }
        recv(socket_fd, &coincidencias, sizeof(int), MSG_WAITALL);

        if (coincidencias == 1) encontrado = 1;
        else if (coincidencias > 1) {
            printf("Duplicado, debe seleccionar ingresando el ID\n");
            opcion = 2;
        } else printf("[Error] Responsable no encontrado\n");
    }
    if (opcion == 2) {
        printf("Ingrese ID exacto a buscar: ");
        dato_valido = leer_entero(&id_buscado);
        cmd = CMD_CONSULTAR_RESP_ID;
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, &dato_valido, sizeof(int), 0);
        if (dato_valido) {
            send(socket_fd, &id_buscado, sizeof(int), 0);
            recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            while (estado == RECORRIENDO) {
                recv(socket_fd, resp_out, sizeof(responsable_t), MSG_WAITALL);
                mostrar_responsable(resp_out);
                recv(socket_fd, &estado, sizeof(int), MSG_WAITALL);
            }
            recv(socket_fd, &coincidencias, sizeof(int), MSG_WAITALL);
            if (coincidencias == 1) encontrado = 1;
            else printf("[Error] Responsable no encontrado\n");
        } else printf("Error: el ID debe ser un numero.\n");
    }
    return encontrado;
}

int pedir_modificacion_resp(responsable_t * resp) {
    int campo = 0, estado = ERROR; 
	
    printf("Que dato desea modificar? 1-Nombre 2-Apellido 3-Telefono: ");
    leer_entero(&campo);
    if (campo == 1) {
        printf("Ingrese nuevo nombre: ");
        scanf(" %29[^\n]", resp->nombre);
        limpiar_buffer();
        estado = OK;
    } else if (campo == 2) {
        printf("Ingrese nuevo apellido: ");
        scanf(" %29[^\n]", resp->apellido);
        limpiar_buffer();
        estado = OK;
    } else if (campo == 3) {
        printf("Ingrese nuevo telefono: ");
        if (leer_lu(&(resp->telcont))) estado = OK;
    } else {
        printf("[Error] Campo invalido.\n");
    }
    return estado;
}

int modificarResponsable(int socket_fd) {
    int modificado = 0, cmd = CMD_MODIFICAR_RESP;
    responsable_t resp;

    if (buscar_responsable_cliente(socket_fd, &resp) == 1) {
        if (pedir_modificacion_resp(&resp) == OK) {
            send(socket_fd, &cmd, sizeof(int), 0);
            send(socket_fd, &resp, sizeof(responsable_t), 0);
            recv(socket_fd, &modificado, sizeof(int), MSG_WAITALL);
        }
    }
    return modificado;
}

int eliminarResponsable(int socket_fd) {
    int confirmar = 0, eliminado = 0, cmd = CMD_ELIMINAR_RESP;
    responsable_t resp;

    if (buscar_responsable_cliente(socket_fd, &resp) == 1) {
        printf("Confirma que desea eliminar al responsable? (1-Si / 0-No): ");
        leer_entero(&confirmar);
        if (confirmar == 1) {
            send(socket_fd, &cmd, sizeof(int), 0);
            send(socket_fd, &(resp.responID), sizeof(int), 0);
            recv(socket_fd, &eliminado, sizeof(int), MSG_WAITALL);
        }
    }
    return eliminado;
}

int leer_lu(unsigned long int * valor) { 
    int es_numero = 0;

    if (scanf("%lu", valor) == 1) { 
        es_numero = 1; 
    } else {
        *valor = 0;
    } 
    limpiar_buffer();

    return es_numero; 
}
