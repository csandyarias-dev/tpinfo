#include "inc/encabezadogeneral.h"
#include <arpa/inet.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>


int obtener_ip_puerto(int cant, char *argv[], char *ip, int *puerto) {
    FILE *fp = NULL;
    int error = 0;

    if (cant == 1) {
        fp = fopen(ARCH_CLIENTE, "r");
        if (fp != NULL) {
            if (fscanf(fp, "%s:%d", ip, puerto) != 2 || *puerto == 0) {
                printf("Error de formato en cfg/cliente.cfg\n");
                error = 1;
            }
            fclose(fp);
        } 
        else {
            printf("No se pudo abrir cfg/cliente.cfg\n");
            error = 1;
        }
    } 
    else if (cant == 3) {
        strcpy(ip, argv[1]);
        *puerto = atoi(argv[2]);
        if (*puerto == 0) {
            printf("Puerto invalido.\n");
            error = 1;
        }
    } else {
        printf("Uso normal: %s | Uso provisorio: %s <IP> <PUERTO>\n", argv[0], argv[0]);
        error = 1;
    }
    return error;
}

int conectar_servidor(char *ip, int server_port) {
    int client_socket_fd = -1, status = 0, error = 0;
    struct sockaddr_in server_data;
    struct hostent *host_data = NULL;

    host_data = gethostbyname(ip);
    if (host_data == NULL) {
        printf("IP invalida.\n");
        error = 1;
    }
    if (!error) {
        client_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
        if (client_socket_fd == -1) {
            printf("Error en socket().\n");
            error = 1;
        }
    }
    if (!error) {
        server_data.sin_family = AF_INET;
        memcpy(&(server_data.sin_addr), host_data->h_addr_list[0], host_data->h_length);
        server_data.sin_port = htons(server_port);
        memset(&(server_data.sin_zero), 0, 8);

        status = connect(client_socket_fd, (struct sockaddr *)&server_data, sizeof(server_data));
        if (status == -1) {
            printf("Error en connect().\n");
            close(client_socket_fd);
            client_socket_fd = -1;
        }
    }
    return client_socket_fd;
}

/**
	\fn      int agregar_turno(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo)
	\brief   agrega un turno
	\author  TP Las Marmotas
	\date    2026.11.13
	\param   int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo
	\return  int estado
*/

int agregar_turno(int socket_fd){
	int id = 0, estado = ERROR, cmd = 0, coincidencias = 0, estado=0;
	turnos_t nuevo; 
	paciente_t * paciente = NULL; 
	int dia = 0, mes = 0, anio = 0, hora = 0, min = 0, am_pm = 0;
	
	printf("Ingrese el ID del paciente: ");
	if(leer_entero(&id)){ 

		printf("Paciente seleccionado:\n");
		
		cmd = CMD_CONSULTAR_PAC_ID;
        send(socket_fd, &cmd, sizeof(int), 0);
        send(socket_fd, &id, sizeof(int), 0);
        recv(socket_fd, &coincidencias, sizeof(int), 0);
               
        if (coincidencias == 1) {
			recv(socket_fd, paciente, sizeof(paciente_t), 0);
			printf("ID: %d | Nombre: %s | RespID: %d\n", paciente->pacID, paciente->nombre, paciente->responID);
         
			nuevo.pacID = id;
			nuevo.responID = paciente->responID;
		
			printf("Ingrese la fecha siguiendo el siguiente formato: DIA-MES-ANIO: ");
			scanf("%d-%d-%d", &dia, &mes, &anio);
			nuevo.fecha.bits1.dia = dia;
			nuevo.fecha.bits1.mes = mes;
			nuevo.fecha.bits1.anio = anio;    
		
			printf("Ingrese la hora formato 12hs (01 a 12) de la siguiente forma HH:MM: ");
			scanf("%d:%d", &hora, &min);
			limpiar_buffer();
			printf("Ingrese 0 para AM o 1 para PM: ");
			leer_entero(&am_pm);

			nuevo.hora.bits.hora = hora;
			nuevo.hora.bits.min = min;
			nuevo.hora.bits.am_pm = am_pm;
		
			if (es_fecha_valida(nuevo.fecha) && es_hora_valida(hora, min, am_pm)){
				cmd = CMD_AGREGAR_TURNO;
				send(socket_fd, &cmd, sizeof(int), 0);
				send(socket_fd, &nuevo, sizeof(turnos_t), 0);
				
				if(recv(socket_fd, &estado, sizeof(int), 0)==OK)
				{
					 printf("Turno agregado con exito");
					 estado = OK;
				}
				else estado = ERROR;
			} 
			else printf("\n Fecha u hora invalida\n");
		}
		else printf("\n Paciente no encontrado\n");
	} 
	else printf("ID invalido");	
 return estado;
}
