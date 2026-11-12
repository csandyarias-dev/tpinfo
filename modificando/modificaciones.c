// En funciones_principal.c (cargar_pacientes_archivo, cargar_responsables_archivo, cargar_turnos_archivo, cargar_tipos_archivo e importar_desde_archivo quedan IGUALES)

int agregar_turno(int * u_pac, int * u_resp, nodo_paciente_t ** pac, nodo_responsable_t ** resp, nodo_turnos_t ** turnos, tipopac_t ** tipos, int * cant_t, int * u_tipo){
	int id = 0, estado = ERROR;
	turnos_t nuevo; 
	nodo_paciente_t * paciente = NULL; 
	int dia = 0, mes = 0, anio = 0, hora = 0, min = 0, am_pm = 0;
	
	printf("Ingrese el ID del paciente: ");
	leer_entero(&id);

	printf("Paciente seleccionado:\n");
	
	if(ConsultarCoincidencias_PacienteID(*pac, id, &paciente)){
		nuevo.pacID = id;
		nuevo.responID = paciente->paciente.responID;
	
		printf("Ingrese la fecha siguiendo el siguiente formato: DIA-MES-ANIO: ");
		scanf("%d-%d-%d", &dia, &mes, &anio);
		limpiar_buffer(); // AGREGADO: Limpia el salto de linea
		nuevo.fecha.bits1.dia = dia;
		nuevo.fecha.bits1.mes = mes;
		nuevo.fecha.bits1.anio = anio;    
	
		// MODIFICADO: Se pide en formato 12hs (1 a 12) + AM/PM para respetar los 4 bits de hora y 1 bit de am_pm
		printf("Ingrese la hora formato 12hs (01 a 12) de la siguiente forma HH:MM: ");
		scanf("%d:%d", &hora, &min);
		limpiar_buffer();
		printf("Ingrese 0 para AM o 1 para PM: ");
		leer_entero(&am_pm);

		nuevo.hora.bits.hora = hora;
		nuevo.hora.bits.min = min;
		nuevo.hora.bits.am_pm = am_pm; // AGREGADO: Se guarda el bit AM/PM
    
		// AGREGADO: Verifica fecha valida y rangos de hora (1..12), minutos (0..59) y am_pm (0..1)
		if (es_fecha_valida(nuevo.fecha) && hora >= 1 && hora <= 12 && min >= 0 && min <= 59 && (am_pm == 0 || am_pm == 1)) {
			if (aniadir_ordenado_t(turnos, nuevo) == OK) estado = OK;
			else estado = ERROR;
		} else {
			printf("\n Fecha u hora invalida\n");
		}
	}
	else printf("\n Paciente no encontrado\n");
    
	return estado;
}

int comparar_fecha_hora(turnos_t a, turnos_t b) {
    int resultado = 0;

    if (a.fecha.bits1.anio != b.fecha.bits1.anio) {
        resultado = a.fecha.bits1.anio - b.fecha.bits1.anio;
    } else if (a.fecha.bits1.mes != b.fecha.bits1.mes) {
        resultado = a.fecha.bits1.mes - b.fecha.bits1.mes;
    } else if (a.fecha.bits1.dia != b.fecha.bits1.dia) {
        resultado = a.fecha.bits1.dia - b.fecha.bits1.dia;
    } else if (a.hora.bits.am_pm != b.hora.bits.am_pm) { // AGREGADO: Compara AM (0) vs PM (1) antes de comparar la hora
        resultado = a.hora.bits.am_pm - b.hora.bits.am_pm;
    } else if (a.hora.bits.hora != b.hora.bits.hora) {
        resultado = a.hora.bits.hora - b.hora.bits.hora;
    } else {
        resultado = a.hora.bits.min - b.hora.bits.min;
    }

    return resultado;
}

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
                else lugar = 1;
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

int act_archivos(nodo_paciente_t ** pac_primero, int ultimo_id_pac, nodo_responsable_t ** resp_primero, int ultimo_id_resp, nodo_turnos_t ** turnos_primero, tipopac_t * vector_tipos, int cant_tipos, int ultimo_id_tipo) {
    // MUTEX ARCHIVOS LOCK
    act_tipos_archivos(vector_tipos, cant_tipos, ultimo_id_tipo);
    act_pacientes_archivos(pac_primero, ultimo_id_pac);
    act_resp_archivos(resp_primero, ultimo_id_resp);
    act_turnos_archivos(turnos_primero);
    // MUTEX ARCHIVOS UNLOCK
    return OK;
}

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
    } else {
        estado = ERROR;
    }
    return estado;
} 

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
    } else {
        estado = ERROR;
    }
    return estado;
}

// AGREGADO: Libera la memoria de las 3 listas y del vector de tipos al salir del programa
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
