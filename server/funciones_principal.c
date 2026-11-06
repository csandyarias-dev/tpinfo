#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>
#include "inc/encabezadogeneral.h"


/**
	\fn      int iniciar_socket_servidor(int port)
	\brief   inicia el socket del servidor
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   int port
	\return  int listen_socket_fd
*/

int iniciar_socket_servidor(int port) {
    int listen_socket_fd = -1, status = 0, enable = 1, error = 0;
    struct sockaddr_in server_data;

    listen_socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_socket_fd == -1) {
        printf("Error en socket().\n");
        error = 1;
    }
    if (!error) {
        server_data.sin_family = AF_INET;
        server_data.sin_addr.s_addr = INADDR_ANY;
        server_data.sin_port = htons(port);
        memset(&(server_data.sin_zero), 0, 8);

        status = setsockopt(listen_socket_fd, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
        if (status == -1) {
            printf("Error en setsockopt().\n");
            error = 1;
        }
    }
    if (!error) {
        if (bind(listen_socket_fd, (struct sockaddr *)&server_data, sizeof(server_data)) == -1 ||
            listen(listen_socket_fd, BACKLOG) == -1) {
            printf("Error en bind() o listen().\n");
            error = 1;
        }
    }
    if (error && listen_socket_fd != -1) {
        close(listen_socket_fd);
        listen_socket_fd = -1;
    }
    return listen_socket_fd;
}

/**
	\fn      void atender_cliente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo)
	\brief   recibe las instrucciones del cliente mientras queda atento a la alarma
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** lista
	\param   int *ultimoPacID
	\return  int pacientes_cargados
*/

void atender_cliente(int client_fd, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int conectado = 1, comando = 0, bytes_recibidos = 0;

    while (conectado) {
        if (flag_alarma) {
            act_archivos(pac, *u_pac, resp, *u_resp, tur, *tipos, *cant_t, *u_tipo);
            flag_alarma = 0;
        }
        bytes_recibidos = recv(client_fd, &comando, sizeof(int), 0);
        if (bytes_recibidos <= 0) {
            if (flag_alarma) {
                act_archivos(pac, *u_pac, resp, *u_resp, tur, *tipos, *cant_t, *u_tipo);
                flag_alarma = 0;
            } 
            else conectado = 0;
        } else if (comando == CMD_SALIR) {
            act_archivos(pac, *u_pac, resp, *u_resp, tur, *tipos, *cant_t, *u_tipo);
            conectado = 0;
        } else {
            ejecutar_comando_servidor(client_fd, comando, u_pac, u_resp, pac, resp, tur, tipos, cant_t, u_tipo);
        }
    }
} 

/**
	\fn      int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID)
	\brief   actualiza la lista de pacientes desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** lista
	\param   int *ultimoPacID
	\return  int pacientes_cargados
*/


int ejecutar_comando_servidor(int client_fd, int comando, int *u_pac, int *u_resp, nodo_paciente_t **pac, nodo_responsable_t **resp, nodo_turnos_t **tur, tipopac_t **tipos, int *cant_t, int *u_tipo) {
    int estado = ERROR;

    //puntero_cmd_servidor_t acciones_servidor[20] = {
        //consultar_pac_id,      // 1: CMD_CONSULTAR_PAC_ID
        //consultar_pac_nom,     // 2: CMD_CONSULTAR_PAC_NOM
        //consultar_resp_id,     // 3: CMD_CONSULTAR_RESP_ID
        //consultar_resp_nom,    // 4: CMD_CONSULTAR_RESP_NOM
        //turno_pac_nom,         // 5: CMD_TURNO_PAC_NOM
        //turno_resp_nom,        // 6: CMD_TURNO_RESP_NOM
        //turno_fecha,           // 7: CMD_TURNO_FECHA
        //listado_pac,           // 8: CMD_LISTADO_PAC
        //listado_resp,          // 9: CMD_LISTADO_RESP
        //agregar_turno,         // 10: CMD_AGREGAR_TURNO
        //agregar_pac,           // 11: CMD_AGREGAR_PAC
        //modificar_pac,         // 12: CMD_MODIFICAR_PAC
        //eliminar_pac,          // 13: CMD_ELIMINAR_PAC
        //agregar_resp,          // 14: CMD_AGREGAR_RESP
        //modificar_resp,        // 15: CMD_MODIFICAR_RESP
        //eliminar_resp,         // 16: CMD_ELIMINAR_RESP
        //mostrar_tipos,         // 17: CMD_MOSTRAR_TIPOS
        //agregar_tipo,          // 18: CMD_AGREGAR_TIPO
        //modificar_tipo,        // 19: CMD_MODIFICAR_TIPO
        //borrar_tipo            // 20: CMD_BORRAR_TIPO
    //};

    if (comando >= CMD_CONSULTAR_PAC_ID && comando <= CMD_BORRAR_TIPO) {
        //estado = acciones_servidor[comando - 1](client_fd, u_pac, u_resp, pac, resp, tur, tipos, cant_t, u_tipo);
    }

    return estado;
}

/**
	\fn      int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID)
	\brief   actualiza la lista de pacientes desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** lista
	\param   int *ultimoPacID
	\return  int pacientes_cargados
*/

int cargar_pacientes_archivo(nodo_paciente_t ** lista, int *ultimoPacID) {
    FILE *fp;
    paciente_t pacAux;
    int cant_pacientes=0;

    // Abrimos el archivo en modo lectura binaria 
    fp = fopen("dat/pacientes.dat", "rb");

    if (fp != NULL) {
        fread(ultimoPacID, sizeof(int), 1, fp);
        
        while (fread(&pacAux, sizeof(paciente_t), 1, fp) == 1) { 
            anadir_ordenado_p(lista, pacAux);
            cant_pacientes++; 
        }
        
        fclose(fp);
    } 
    return cant_pacientes;
}

/**
	\fn      int cargar_responsables_archivo(nodo_responsable_t ** lista, int *ultimoResponID)
	\brief   actualiza la lista de responsables desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_responsable_t ** lista
	\param   int *ultimoResponID
	\return  int responsables_cargados
*/

int cargar_responsables_archivo(nodo_responsable_t ** lista, int *ultimoResponID) {
    FILE *fp;
	responsable_t respon_aux;
    int cant_responsables=0;

    // Abrimos el archivo en modo lectura binaria 
    fp = fopen("dat/responsables.dat", "rb");

    if (fp != NULL) {
        fread(ultimoResponID, sizeof(int), 1, fp);
        
        while (fread(&respon_aux, sizeof(responsable_t), 1, fp) == 1) { 
            anadirordenado_r(lista, respon_aux); 
            cant_responsables++; 
        }
        
        fclose(fp);
    } 
    return cant_responsables;
}

/**
	\fn      int cargar_turnos_archivo(nodo_turnos_t ** lista) 
	\brief   actualiza la lista de turnos desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_turnos_t ** lista
	\return  int turnos_cargados
*/

int cargar_turnos_archivo(nodo_turnos_t ** lista) {
    FILE *fp;
    turnos_t turnos_aux;
    int cant_turnos=0;

    // Abrimos el archivo en modo lectura binaria 
    fp = fopen("dat/turnos.dat", "rb");

    if (fp != NULL) {
        
        while (fread(&turnos_aux, sizeof(turnos_t), 1, fp) == 1) { 
           aniadir_ordenado_t(lista, turnos_aux); 
           cant_turnos++; 
        }
        
        fclose(fp);
    } 
    return cant_turnos;
}

/**
	\fn      cargar_tipos_archivo(tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID)
	\brief   actualiza el vector dinamico de tipos desde el archivo
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID
	\return  int tipos_cargados
*/

int cargar_tipos_archivo(tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID) {
    FILE * fp = fopen("dat/tipospac.lst", "r");
    tipopac_t * aux = NULL;
    char buffer[50];
    int id_temp = 0, estado = 0;

    *cant_tipos = 0;
    if (fp != NULL) {
        if (fscanf(fp, "%d\n", ultimo_tipoID) == 1) {
            while (fscanf(fp, "%d|%49[^\n]\n", &id_temp, buffer) == 2 && estado != ERROR_MEMORIA) {
                aux = (tipopac_t *)realloc(*vector_tipos, (*cant_tipos + 1) * sizeof(tipopac_t));
                if (aux != NULL) {
                    *vector_tipos = aux;
                    (*vector_tipos)[*cant_tipos].nombre = (char *)malloc((strlen(buffer) + 1) * sizeof(char));
                    if ((*vector_tipos)[*cant_tipos].nombre != NULL) {
                        strcpy((*vector_tipos)[*cant_tipos].nombre, buffer);
                        (*vector_tipos)[*cant_tipos].tipoID = (unsigned char)id_temp;
                        (*cant_tipos)++;
                        estado++;
                    } else {
                        estado = ERROR_MEMORIA;
                    }
                } else {
                    estado = ERROR_MEMORIA;
                }
            }
        }
        fclose(fp);
    }
    return estado;
}

/**
	\fn      importar_desde_archivo(int * ultimo_id_pac, int * ultimo_id_resp, nodo_paciente_t ** primero_pac, nodo_responsable_t ** primero_resp, nodo_turnos_t ** primero_turnos)
	\brief   importa todos los datos de los distintos archivos
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_tipoID
	\return  int tipos_cargados
*/


int importar_desde_archivo(int * ultimo_id_pac, int * ultimo_id_resp, nodo_paciente_t ** primero_pac, nodo_responsable_t ** primero_resp, nodo_turnos_t ** primero_turnos, tipopac_t ** vector_tipos, int * cant_tipos, int * ultimo_id_tipo) {
    int estado = OK;
    int cant_p = 0, cant_r = 0, cant_t = 0, cant_tipos_leidos = 0;

    cant_tipos_leidos = cargar_tipos_archivo(vector_tipos, cant_tipos, ultimo_id_tipo);
    cant_p = cargar_pacientes_archivo(primero_pac, ultimo_id_pac);
    cant_r = cargar_responsables_archivo(primero_resp, ultimo_id_resp);
    cant_t = cargar_turnos_archivo(primero_turnos);

    if (cant_p < 0 || cant_r < 0 || cant_t < 0 || cant_tipos_leidos < 0) {
        estado = ERROR_ARCHIVO;
    }

    return estado;
}

/**
	\fn      int agregar_turno(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo)
	\brief   agrega un turno
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo
	\return  int estado
*/

int agregar_turno(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo){
	int id = 0, estado = ERROR;
	turnos_t nuevo; 
	nodo_paciente_t * paciente = NULL; 
	int dia = 0, mes = 0, anio = 0, hora = 0, min = 0, am_pm = 0;
	
	if (recv(client_fd, &id, sizeof(int), 0) > 0) {
		if(ConsultarCoincidencias_PacienteID(*pac, id, &paciente)){
			nuevo.pacID = id;
			nuevo.responID = paciente->paciente.responID;
		
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
		
			if (es_fecha_valida(nuevo.fecha) && es_hora_valida(hora, min, am_pm)) {
				if (aniadir_ordenado_t(turnos, nuevo) == OK)
				{
					 printf("Turno agregado con exito");
					 estado = OK;
				}
				else estado = ERROR;
			} else {
				printf("\n Fecha u hora invalida\n");
			}
		}
		else printf("\n Paciente no encontrado\n");
	} else printf("ID invalido");	
 return estado;
}
	
/**
	\fn      int comparar_fecha_hora(turnos_t a, turnos_t b)
	\brief   comparar fecha y hora (desendentemente)
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   turnos_t a, turnos_t b
	\return  int resultado
*/	
	
int comparar_fecha_hora(turnos_t a, turnos_t b) {
    int resultado = 0;

    if (a.fecha.bits1.anio != b.fecha.bits1.anio) {
        resultado = a.fecha.bits1.anio - b.fecha.bits1.anio;
    } else if (a.fecha.bits1.mes != b.fecha.bits1.mes) {
        resultado = a.fecha.bits1.mes - b.fecha.bits1.mes;
    } else if (a.fecha.bits1.dia != b.fecha.bits1.dia) {
        resultado = a.fecha.bits1.dia - b.fecha.bits1.dia;
    } else if (a.hora.bits.am_pm != b.hora.bits.am_pm) {
        resultado = a.hora.bits.am_pm - b.hora.bits.am_pm;
    } else if ((a.hora.bits.hora%12) != (b.hora.bits.hora%12)) {
        resultado = a.hora.bits.hora%12 - b.hora.bits.hora%12;
    } else {
        resultado = a.hora.bits.min - b.hora.bits.min;
    }

    return resultado;
}

/**
	\fn      int aniadir_ordenado_t(nodo_turnos_t **lista, turnos_t nuevo)
	\brief   añade un turno de forma ordenada
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_turnos_t **lista, turnos_t nuevo
	\return  int estado
*/	

int aniadir_ordenado_t(nodo_turnos_t **lista, turnos_t nuevo) {
    nodo_turnos_t *agregando = NULL, *actual = NULL, *anterior = NULL;
    int estado = ERROR_MEMORIA;
    int lugar = 0;

    agregando = (nodo_turnos_t *) malloc(sizeof(nodo_turnos_t));

    if (agregando != NULL) {
        agregando->turnos = nuevo;
        agregando->sig = NULL;
        actual = *lista;

        if (*lista != NULL) {
            while ((actual != NULL) && (lugar == 0)) {
                if (comparar_fecha_hora(nuevo, actual->turnos) >= 0) {
                    anterior = actual;
                    actual = actual->sig;
                } 
                else lugar = 1; // actualizo el flag
                
            }

            if (anterior == NULL) {
                agregando->sig = *lista;
                *lista = agregando;
            } else {
            
                agregando->sig = actual;
                anterior->sig = agregando;
            }
            estado = OK;
        } 
        else {
			*lista = agregando;
			estado = OK;
        }
   }
   return estado; 
}
  
	/**
	\fn    	 void alarma_handler(int nsig)
	\brief   setea la flag de actualizacion de archivos en 1
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   int nsig
	\return  void
*/

void alarma_handler(int nsig) {	
	flag_alarma=1;
	alarm(120); 
	signal(SIGALRM, alarma_handler);
	}
	
/**
	\fn    	 int act_archivos(nodo_paciente_t ** pac_primero, nodo_responsable_t ** resp_primero, nodo_turnos_t ** turnos_primero, tipopac_t * vector_tipos, int cant_tipos, int ultimo_id_tipo) 
	\brief   actualiza los archivos con los datos actuales
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_turnos_t **lista, turnos_t nuevo
	\return  int estado
*/
	
int act_archivos(nodo_paciente_t ** pac_primero, int ultimo_id_pac, nodo_responsable_t ** resp_primero, int ultimo_id_resp, nodo_turnos_t ** turnos_primero, tipopac_t * vector_tipos, int cant_tipos, int ultimo_id_tipo) {
    // MUTEX ARCHIVOS LOCK
    act_tipos_archivos(vector_tipos, cant_tipos, ultimo_id_tipo);
    act_pacientes_archivos(pac_primero, ultimo_id_pac);
    act_resp_archivos(resp_primero, ultimo_id_resp);
    act_turnos_archivos(turnos_primero);
    // MUTEX ARCHIVOS UNLOCK
    return OK;
}

/**
	\fn    	 int act_pacientes_archivos(nodo_paciente_t ** primero) 
	\brief   actualiza el archivo pacientes.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_paciente_t ** primero
	\return  int estado
*/

int act_pacientes_archivos(nodo_paciente_t ** primero, int ultimo_id_pac) {
    FILE *fp;
    nodo_paciente_t * actual;
    int estado = 0;
    
    fp = fopen("dat/pacientes.dat", "wb+");
    
    if (fp != NULL) {
		fwrite(&ultimo_id_pac, sizeof(int), 1, fp); 
        actual = *primero; 
        while (actual != NULL) {
            fwrite(&(actual->paciente), sizeof(paciente_t), 1, fp); 
            actual = actual->sig;
            estado++;
        }
        fclose(fp);
    } 
    else {
        estado = ERROR;
    }
    return estado;
} 

/**
	\fn    	 int act_resp_archivos(nodo_responsable_t ** primero)
	\brief   actualiza el archivo responsables.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_responsable_t ** primero
	\return  int estado
*/

int act_resp_archivos(nodo_responsable_t ** primero, int ultimo_id_resp) {
    FILE *fp;
    nodo_responsable_t * actual;
    int estado = 0;
    
    fp = fopen("dat/responsables.dat", "wb+"); 
    
    if (fp != NULL) {
		fwrite(&ultimo_id_resp, sizeof(int), 1, fp); 
        actual = *primero; 
        while (actual != NULL) {
            fwrite(&(actual->responsable), sizeof(responsable_t), 1, fp); 
            actual = actual->sig;
            estado++;
        }
        fclose(fp);
    } 
    else {
        estado = ERROR;
    }
    return estado;
}

/**
	\fn    	 int act_turnos_archivos(nodo_turnos_t ** primero)
	\brief   actualiza el archivo turnos.dat
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   nodo_responsable_t ** primero
	\return  int estado
*/
    
int act_turnos_archivos(nodo_turnos_t ** primero) {
    FILE *fp;
    nodo_turnos_t * actual;
    int estado = 0;
    
    fp = fopen("dat/turnos.dat", "wb+"); 
    
    if (fp != NULL) {
        if (*primero != NULL) {
            actual = *primero; 
            while (actual != NULL) {
                fwrite(&(actual->turnos), sizeof(turnos_t), 1, fp); 
                actual = actual->sig;
                estado++;
            }
        }
        else estado = ERROR;
        fclose(fp);
    }
    return estado;
}

/**
	\fn    	 int act_tipos_archivos(tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID)
	\brief   actualiza el archivo tipospac.lst
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID
	\return  int estado
*/

int act_tipos_archivos(tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID) {
    FILE * fp = fopen("dat/tipospac.lst", "w+");
    int i = 0, estado = ERROR_ARCHIVO;

    if (fp != NULL) {
        fprintf(fp, "%d\n", ultimo_tipoID);
        for (i = 0; i < cant_tipos; i++) {
            fprintf(fp, "%d|%s\n", vector_tipos[i].tipoID, vector_tipos[i].nombre);
        }
        estado = i;
        fclose(fp);
    }
    return estado;
}

/** HACER NOK
	\fn    	 int act_tipos_archivos(tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID)
	\brief   actualiza el archivo tipospac.lst
	\author  <Apellido y Nombre (mail)>
	\date    <Año.Mes.Día>
	\param   tipopac_t * vector_tipos, int cant_tipos, int ultimo_tipoID
	\return  int estado
*/

void liberar_memoria(nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** tur, tipopac_t ** tipos, int cant_tipos) {
    nodo_paciente_t * aux_p = NULL;
    nodo_responsable_t * aux_r = NULL;
    nodo_turnos_t * aux_t = NULL;
    int i = 0;

    while (*pac != NULL) {
        aux_p = *pac;
        *pac = (*pac)->sig;
        free(aux_p);
    }
    while (*resp != NULL) {
        aux_r = *resp;
        *resp = (*resp)->sig;
        free(aux_r);
    }
    while (*tur != NULL) {
        aux_t = *tur;
        *tur = (*tur)->sig;
        free(aux_t);
    }
    if (*tipos != NULL) {
        for (i = 0; i < cant_tipos; i++) {
            free((*tipos)[i].nombre);
        }
        free(*tipos);
        *tipos = NULL;
    }
}
