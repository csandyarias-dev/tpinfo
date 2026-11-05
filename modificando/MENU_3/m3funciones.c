/**
	\file    m3funciones.c
	\brief   Contienen las funciones pertenecientes al menu 3
	\author  Grupo las marmotas
	\date    2026.09.02
	\version 1.0.0
*/

//--------------
//-- Includes --
//--------------

#include "../inc/encabezadogeneral.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//---------------
//-- Funciones --
//---------------

int agregar_paciente(nodo_paciente_t ** primero, int * ultimo_ID_utilizado, tipopac_t ** tipos, int * cant_t, int * u_tipo) {
    paciente_t cliente;
    int estado=ERROR_MEMORIA, dia, mes, anio;
    
    mostrar_tipos_animales(tipos, cant_t, u_tipo);    
    printf("Ingrese el ID del tipo de paciente: "); 
    if(leer_uchar(&(cliente.tipoID))){ 
    
		printf("Ingrese nombre del paciente: ");
		scanf(" %[^\n]", cliente.nombre); 
		
		printf("Ingrese la fecha de nacimiento SIGUIENDO el siguiente formato DD-MM-AAAA: ");
		scanf("%d-%d-%d", &dia, &mes, &anio);
		
		cliente.nacimiento.bits1.dia=dia;
		cliente.nacimiento.bits1.mes=mes;
		cliente.nacimiento.bits1.anio=anio;
		
		printf("Ingrese el ID del responsable: ");
		if (leer_entero(&(cliente.responID))){ 
					
			cliente.pacID=(*ultimo_ID_utilizado)+1;
			if (anadir_ordenado_p(primero, cliente) != OK) printf("ERROR AL AÑADIR"); 
			else { 
				estado=OK;
				(*ultimo_ID_utilizado)++;
			}
	} else printf("ID invalido");
	
	} else printf("Entrada invalida, intentelo nuevamente.");

return estado; 
}

int anadir_ordenado_p(nodo_paciente_t ** lista, paciente_t cliente){
    nodo_paciente_t * nuevo = NULL, * auxp = NULL, * anterior= NULL, *actual = NULL;
    int estado=ERROR_MEMORIA; 
    
    auxp =(nodo_paciente_t *) malloc(sizeof(nodo_paciente_t)); 
    
    if (auxp!=NULL) { 
        nuevo = auxp; 
        
        nuevo->paciente=cliente; 
        nuevo->sig=NULL; 
        
        actual = *lista;
        
        while ((actual!=NULL) && (strcmp(actual->paciente.nombre, cliente.nombre)<0))
        {
            anterior = actual;
            actual = actual->sig;                                                              
        }
        
        if (anterior!=NULL){ 
            anterior->sig=nuevo; 
            nuevo->sig=actual;
        }
        else {
            nuevo->sig=*lista; 
            *lista=nuevo;    
        }
        estado=OK;
    }
    else estado=ERROR_MEMORIA;
    
    return estado; 
}

int modificar_paciente(nodo_paciente_t ** lista, int * ultimo_id, tipopac_t ** tipos, int * cant_t, int * u_tipo) {
    int opcion = 0, idBuscado = 0, coincidencias = 0, modificado = 0; 
    char nombre[30] = {0};
    nodo_paciente_t * actual = NULL; 
    
    do {
        printf("Ingrese 1 para buscar por nombre y 2 para buscar por ID: ");
        leer_entero(&opcion);
    } while ((opcion != 1) && (opcion != 2));
    
    if (opcion == 1) {
        printf("Ingrese nombre: ");
        scanf(" %[^\n]", nombre); 
        limpiar_buffer();
        
		printf("El paciente a modificar es: ");
        coincidencias = ConsultarCoincidencias_PacienteNombre(*lista, nombre, &actual);

        if (coincidencias == 1) {
            modificar_nodo(actual, lista);
            modificado = 1;
        } 
        else if (coincidencias > 1) 
        { 
			printf("Duplicado, debe modificar ingresando el ID\n");
			opcion=2;
		}
        else printf("Paciente no encontrado\n");
    } 
    
    if (opcion == 2) {
        printf("Ingrese ID: ");
        leer_entero(&idBuscado); 
        
        printf("El paciente a modificar es: ");
        if (ConsultarCoincidencias_PacienteID(*lista, idBuscado, &actual) == 1) {
            modificar_nodo(actual, lista);
            modificado = 1;
        } 
        else {
            printf("Paciente no encontrado\n");  
        }
    }

    return modificado;           
}
    
int modificar_nodo(nodo_paciente_t * actual, nodo_paciente_t ** lista){
    int opcion;
    char nombreN[30]={0};
    int estado = 0, dia, mes, anio;
    paciente_t aux; 
    
    printf("Ingrese el numero del item a modificar: \n \t 1- Nombre \n \t 2- Fecha de nacimiento \n \t 3- ID del responsable \n");
    scanf("%d", &opcion);
    
    switch(opcion){
        case NOMBRE: 
            printf("Ingrese el nombre nuevo: ");
            scanf(" %[^\n]", nombreN); 
            strcpy(actual->paciente.nombre, nombreN); 
            aux = actual->paciente;  
            eliminar_nodo(lista, actual);  
            anadir_ordenado_p(lista, aux); 
              
            estado = OK;
        break; 
        
        case FECHA_NACIMIENTO:
            printf("Ingrese la fecha de nacimiento SIGUIENDO el siguiente formato DD-MM-AAAA");
            scanf("%d-%d-%d", &dia, &mes, &anio);
            
			actual->paciente.nacimiento.bits1.dia=dia;
			actual->paciente.nacimiento.bits1.mes=mes;
			actual->paciente.nacimiento.bits1.anio=anio;
	
            estado = OK;
        break;
        
        case ID_RESPONSABLE:
            printf("Ingrese el nuevo ID del responsable: "); 
            scanf("%d", &(actual->paciente.responID)); 
            estado = OK;
        break;
    }
    
    return estado; 
}

int eliminar_paciente(nodo_paciente_t ** lista, int * id_ultimo, tipopac_t ** tipos, int * cant_t, int * u_tipo) {
    int opcion = 0, idBuscado = 0, coincidencias = 0, confirmar = 0, encontrado = 0; 
    char nombre[30] = {0};
    nodo_paciente_t * actual = NULL; 
    
    do {
        printf("Ingrese 1 para buscar el paciente por nombre y 2 para buscar por ID: ");
        leer_entero(&opcion);
    } while ((opcion != 1) && (opcion != 2));
    
    if (opcion == 1) {
        printf("Ingrese nombre: ");
        scanf(" %[^\n]", nombre);
        limpiar_buffer();

        coincidencias = ConsultarCoincidencias_PacienteNombre(*lista, nombre, &actual);

        if (coincidencias == 1) {
            printf("Confirma que desea eliminar al paciente? (1-Si / 0-No): ");
            leer_entero(&confirmar);
            if (confirmar == 1) {
                eliminar_nodo(lista, actual); 
                encontrado = 1;
            }
        } else if (coincidencias > 1) {
            printf("Duplicado, debe eliminar ingresando el ID\n"); 
            opcion = 2; // Pasa directo a pedir el ID como pide la consigna (*)
        } else {
            printf("Paciente no encontrado\n"); 
        }
    }
    
    if (opcion == 2) {
        printf("Ingrese ID: ");
        leer_entero(&idBuscado); 
        
        if (ConsultarCoincidencias_PacienteID(*lista, idBuscado, &actual) == 1) {
            printf("Confirma que desea eliminar al paciente? (1-Si / 0-No): ");
            leer_entero(&confirmar);
            if (confirmar == 1) {
                eliminar_nodo(lista, actual); 
                encontrado = 1; 
            }
        } else {
            printf("Paciente no encontrado\n");        
        }
    }
    
    return encontrado; 
}

int eliminar_nodo(nodo_paciente_t ** lista, nodo_paciente_t * actual) {
    int estado = ERROR; 
    nodo_paciente_t * anterior = *lista;
    
    if (actual != NULL && *lista != NULL) {
        if (*lista == actual) {
            *lista = actual->sig; // Si es el primero de la lista
        } else {
            while (anterior != NULL && anterior->sig != actual) {
                anterior = anterior->sig;
            }
            if (anterior != NULL) {
                anterior->sig = actual->sig;
            }
        }
        free(actual);
        estado = 0; 
    }
    return estado; 
}
  
