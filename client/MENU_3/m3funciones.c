#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

int agregar_paciente(int socket_fd) {
    paciente_t cliente;
    int estado = ERROR, cmd = CMD_AGREGAR_PAC, dia = 0, mes = 0, anio = 0;

    memset(&cliente, 0, sizeof(paciente_t));
    mostrar_tipos_animales(socket_fd);
    printf("Ingrese el ID del tipo de paciente: ");
    if (leer_uchar(&(cliente.tipoID))) {
        printf("Ingrese nombre del paciente: ");
        scanf(" %29[^\n]", cliente.nombre);
        printf("Ingrese la fecha de nacimiento SIGUIENDO el siguiente formato DD-MM-AAAA: ");
        scanf("%d-%d-%d", &dia, &mes, &anio);
        limpiar_buffer();
        cliente.nacimiento.bits1.dia = dia;
        cliente.nacimiento.bits1.mes = mes;
        cliente.nacimiento.bits1.anio = anio;

        printf("Ingrese el ID del responsable: ");
        if (leer_entero(&(cliente.responID))) {
            send(socket_fd, &cmd, sizeof(int), 0);
            send(socket_fd, &cliente, sizeof(paciente_t), 0);
            recv(socket_fd, &estado, sizeof(int), 0);
            if (estado != OK) printf("ERROR AL AÑADIR\n");
            else printf("Añadido con exito");
        } else printf("ID invalido\n");
    } else printf("Entrada invalida, intentelo nuevamente.\n");

    return estado;
}

int buscar_paciente_cliente(int socket_fd, paciente_t *pac_out) {
    int opcion = 0, id_buscado = 0, coincidencias = 0, i = 0, cmd = 0, encontrado = 0;
    char nombre[30] = {0};
    paciente_t aux;

    do {
        printf("Ingrese 1 para buscar por nombre y 2 para buscar por ID: ");
        leer_entero(&opcion);
    } while ((opcion != 1) && (opcion != 2));

    if (opcion == 1) {
        printf("Ingrese nombre: ");
        scanf(" %29[^\n]", nombre);
        limpiar_buffer();
        cmd = CMD_CONSULTAR_PAC_NOM;
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, nombre, 30, 0);
        recv(socket_fd, &coincidencias, sizeof(int), 0);
        while (i < coincidencias) {
            recv(socket_fd, &aux, sizeof(paciente_t), 0);
            printf("ID: %d | Nombre: %s | RespID: %d\n", aux.pacID, aux.nombre, aux.responID);
            *pac_out = aux;
            i++;
        }
        if (coincidencias == 1) encontrado = 1;
        else if (coincidencias > 1) {
            printf("Duplicado, debe seleccionar ingresando el ID\n");
            opcion = 2;
        } else printf("Paciente no encontrado\n");
    }
    if (opcion == 2) {
        printf("Ingrese ID: ");
        leer_entero(&id_buscado);
        cmd = CMD_CONSULTAR_PAC_ID;
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, &id_buscado, sizeof(int), 0);
        recv(socket_fd, &coincidencias, sizeof(int), 0);
        if (coincidencias == 1) {
            recv(socket_fd, pac_out, sizeof(paciente_t), 0);
            printf("ID: %d | Nombre: %s | RespID: %d\n", pac_out->pacID, pac_out->nombre, pac_out->responID);
            encontrado = 1;
        } else printf("Paciente no encontrado\n");
    }
    return encontrado;
}

int pedir_modificacion_pac(paciente_t *pac) {
    int opcion = 0, estado = ERROR, dia = 0, mes = 0, anio = 0;

    printf("Ingrese el numero del item a modificar:\n\t1- Nombre\n\t2- Fecha de nacimiento\n\t3- ID del responsable\nOpcion: ");
    leer_entero(&opcion);

    if (opcion == NOMBRE) {
        printf("Ingrese el nombre nuevo: ");
        scanf(" %29[^\n]", pac->nombre);
        limpiar_buffer();
        estado = OK;
    } else if (opcion == FECHA_NACIMIENTO) {
        printf("Ingrese la fecha de nacimiento SIGUIENDO el siguiente formato DD-MM-AAAA: ");
        scanf("%d-%d-%d", &dia, &mes, &anio);
        limpiar_buffer();
        pac->nacimiento.bits1.dia = dia;
        pac->nacimiento.bits1.mes = mes;
        pac->nacimiento.bits1.anio = anio;
        estado = OK;
    } else if (opcion == ID_RESPONSABLE) {
        printf("Ingrese el nuevo ID del responsable: ");
        if (leer_entero(&(pac->responID))) estado = OK;
    } else {
        printf("Opcion invalida.\n");
    }
    return estado;
}

int modificar_paciente(int socket_fd) {
    int modificado = 0, cmd = CMD_MODIFICAR_PAC;
    paciente_t pac;

    if (buscar_paciente_cliente(socket_fd, &pac) == 1) {
        if (pedir_modificacion_pac(&pac) == OK) {
            send(socket_fd, &cmd, sizeof(int), 0);
            send(socket_fd, &pac, sizeof(paciente_t), 0);
            recv(socket_fd, &modificado, sizeof(int), 0);
        }
    }
    return modificado;
}

int eliminar_paciente(int socket_fd) {
    int confirmar = 0, eliminado = 0, cmd = CMD_ELIMINAR_PAC;
    paciente_t pac;

    if (buscar_paciente_cliente(socket_fd, &pac) == 1) {
        printf("Confirma que desea eliminar al paciente? (1-Si / 0-No): ");
        leer_entero(&confirmar);
        if (confirmar == 1) {
            send(socket_fd, &cmd, sizeof(int), 0);
            send(socket_fd, &(pac.pacID), sizeof(int), 0);
            recv(socket_fd, &eliminado, sizeof(int), 0);
        }
    }
    return eliminado;
}
