

/**
	\fn     int ConsultarCoincidencias_PacienteID(nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Busca pacientes por ID e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pacientes: lista de pacientes
	\param  id_ingresado: ID a buscar
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteID(nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado){
    int contador = 0;
    nodo_paciente_t *aux_pacientes = lista_pacientes;

    while (aux_pacientes != NULL) {
        if (aux_pacientes->paciente.pacID == id_ingresado) {
            // Imprime los datos del paciente encontrado
            mostrar_paciente(aux_pacientes);
            send(socket_fd, &(aux_pacientes->paciente), sizeof(paciente_t), 0);

            // Guarda la primera coincidencia (si el llamador quiere recibirla)
            if (Paciente_encontrado != NULL && contador == 0) {
                *Paciente_encontrado = aux_pacientes;
            }
            contador++;
        }
        aux_pacientes = aux_pacientes->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_PacienteNombre(nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado);
	\brief  Busca pacientes por nombre e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_pacientes: lista de pacientes
	\param  nombre_ingresado: nombre a buscar
	\param  Paciente_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_PacienteNombre(nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado){
    int contador = 0;
    nodo_paciente_t *aux_pacientes = lista_pacientes;

    while (aux_pacientes != NULL) {
        if (strcmp(aux_pacientes->paciente.nombre, nombre_ingresado) == 0) {
            // Imprime los datos del paciente encontrado
            mostrar_paciente(aux_pacientes);

            if (Paciente_encontrado != NULL && contador == 0) {
                *Paciente_encontrado = aux_pacientes;
            }
            contador++;
        }
        aux_pacientes = aux_pacientes->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableID(nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Busca responsables por ID e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_responsables: lista de responsables
	\param  id_ingresado: ID a buscar
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableID(nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado){
    int contador = 0;
    nodo_responsable_t *aux_responsables = lista_responsables;

    while (aux_responsables != NULL) {
        if (aux_responsables->responsable.responID == id_ingresado) {
            // Imprime los datos del responsable encontrado
            mostrar_responsable(aux_responsables);

            if (Responsable_encontrado != NULL && contador == 0) {
                *Responsable_encontrado = aux_responsables;
            }
            contador++;
        }
        aux_responsables = aux_responsables->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarCoincidencias_ResponsableNombre(nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado);
	\brief  Busca responsables por nombre e imprime cada coincidencia
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_responsables: lista de responsables
	\param  nombre_ingresado: nombre a buscar
	\param  Responsable_encontrado: guarda la primera coincidencia (puede ser NULL)
	\return Cantidad de coincidencias
*/
int ConsultarCoincidencias_ResponsableNombre(nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado){
    int contador = 0;
    nodo_responsable_t *aux_responsables = lista_responsables;

    while (aux_responsables != NULL) {
        if (strcmp(aux_responsables->responsable.nombre, nombre_ingresado) == 0) {
            // Imprime los datos del responsable encontrado
            mostrar_responsable(aux_responsables);

            if (Responsable_encontrado != NULL && contador == 0) {
                *Responsable_encontrado = aux_responsables;
            }
            contador++;
        }
        aux_responsables = aux_responsables->sig;
    }

    return contador; // Devuelve la cantidad de coincidencias
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_PacienteNombre(nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de un paciente por nombre (usar antes ConsultarCoincidencias_PacienteNombre)
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  lista_pacientes: lista de pacientes (el turno solo guarda el pacID)
	\param  nombre_ingresado: nombre del paciente
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_PacienteNombre(nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;
    const char *nombre_pac = NULL;

    // Primer recorrido: contamos cuantos turnos hay registrados con ese nombre
    while (aux_turnos != NULL) {
        nombre_pac = obtener_nombre_paciente(lista_pacientes, aux_turnos->turnos.pacID);
        if (nombre_pac != NULL && strcmp(nombre_pac, nombre_ingresado) == 0) {
            contador++;
        }
        aux_turnos = aux_turnos->sig;
    }

    // Si se encontraron turnos, reservar memoria y hacer el segundo recorrido
    if (contador > 0) {
        if (turnos_encontrados != NULL) {
            // Se le da memoria al vector segun la cantidad de turnos encontrados
            vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
        }

        if (turnos_encontrados == NULL || vector_turnos != NULL) {
            aux_turnos = lista_turnos;

            while (aux_turnos != NULL) {
                nombre_pac = obtener_nombre_paciente(lista_pacientes, aux_turnos->turnos.pacID);
                if (nombre_pac != NULL && strcmp(nombre_pac, nombre_ingresado) == 0) {
                    mostrar_turno(aux_turnos);          // Imprime fecha y hora mediante la funcion atomica

                    if (vector_turnos != NULL) {        // Almacena el puntero en el vector dinamico
                        vector_turnos[i] = aux_turnos;
                        i++;
                    }
                }
                aux_turnos = aux_turnos->sig;
            }
        } else {
            contador = 0;   // Si fallo el malloc, la cantidad devuelta se resetea a 0
        }
    }

    // Asignacion final del vector reservado (o NULL si no hubo coincidencias/fallo malloc)
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_Fecha(nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de una fecha
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  fecha_ingresada: fecha a buscar
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_Fecha(nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;

    if (es_fecha_valida(fecha_ingresada)) {
        // Primer recorrido: contar coincidencias en dia, mes y año
        while (aux_turnos != NULL) {
            if (aux_turnos->turnos.fecha.bits1.dia  == fecha_ingresada.bits1.dia &&
                aux_turnos->turnos.fecha.bits1.mes  == fecha_ingresada.bits1.mes &&
                aux_turnos->turnos.fecha.bits1.anio == fecha_ingresada.bits1.anio) {
                contador++;
            }
            aux_turnos = aux_turnos->sig;
        }

        // Si hay coincidencias, reservar memoria dinamica con malloc
        if (contador > 0) {
            if (turnos_encontrados != NULL) {
                vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
            }

            // Si la memoria se asigno correctamente o no se requirio guardar el arreglo
            if (turnos_encontrados == NULL || vector_turnos != NULL) {
                aux_turnos = lista_turnos;

                // Segundo recorrido: imprimir y guardar los turnos
                while (aux_turnos != NULL) {
                    if (aux_turnos->turnos.fecha.bits1.dia  == fecha_ingresada.bits1.dia &&
                        aux_turnos->turnos.fecha.bits1.mes  == fecha_ingresada.bits1.mes &&
                        aux_turnos->turnos.fecha.bits1.anio == fecha_ingresada.bits1.anio) {

                        mostrar_turno(aux_turnos);      // Imprime los datos del turno (fecha y hora)

                        if (vector_turnos != NULL) {    // Almacena la direccion del nodo en el vector dinamico
                            vector_turnos[i] = aux_turnos;
                            i++;
                        }
                    }
                    aux_turnos = aux_turnos->sig;
                }
            } else {
                contador = 0;   // Si malloc falla, resetea el contador a 0
            }
        }

    } else {
        printf("Error: La fecha ingresada (%02d/%02d/%04d) no existe o es invalida.\n",
               fecha_ingresada.bits1.dia, fecha_ingresada.bits1.mes, fecha_ingresada.bits1.anio);
    }

    // Guardar el puntero al vector reservado en la variable dada por referencia
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------

/**
	\fn     int ConsultarTurnos_ResponsableNombre(nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
	\brief  Busca e imprime los turnos de un responsable por nombre
	\author Las Marmotas
	\date   2026.10.29
	\param  lista_turnos: lista de turnos
	\param  lista_responsables: lista de responsables (el turno solo guarda el responID)
	\param  nombre_ingresado: nombre del responsable
	\param  turnos_encontrados: vector dinamico con los turnos encontrados (puede ser NULL)
	\return Cantidad de turnos encontrados
*/
int ConsultarTurnos_ResponsableNombre(nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados) {
    int contador = 0, i = 0;
    nodo_turnos_t *aux_turnos = lista_turnos, **vector_turnos = NULL;
    const char *nombre_resp = NULL;

    // 1. Primer recorrido: contamos cuantos turnos hay registrados con el nombre del responsable
    while (aux_turnos != NULL) {
        nombre_resp = obtener_nombre_responsable(lista_responsables, aux_turnos->turnos.responID);
        if (nombre_resp != NULL && strcmp(nombre_resp, nombre_ingresado) == 0) {
            contador++;
        }
        aux_turnos = aux_turnos->sig;
    }

    // 2. Si se encontraron turnos, reservamos memoria dinamica y realizamos el segundo recorrido
    if (contador > 0) {
        if (turnos_encontrados != NULL) {
            vector_turnos = (nodo_turnos_t **) malloc(contador * sizeof(nodo_turnos_t *));
        }

        if (turnos_encontrados == NULL || vector_turnos != NULL) {
            aux_turnos = lista_turnos;

            while (aux_turnos != NULL) {
                nombre_resp = obtener_nombre_responsable(lista_responsables, aux_turnos->turnos.responID);
                if (nombre_resp != NULL && strcmp(nombre_resp, nombre_ingresado) == 0) {
                    mostrar_turno(aux_turnos);          // Imprime fecha y hora mediante la funcion atomica

                    if (vector_turnos != NULL) {        // Almacena el puntero en el vector dinamico
                        vector_turnos[i] = aux_turnos;
                        i++;
                    }
                }
                aux_turnos = aux_turnos->sig;
            }
        } else {
            contador = 0;   // Si fallo el malloc, la cantidad devuelta se resetea a 0
        }
    }

    // Asignacion final del vector reservado (o NULL si no hubo coincidencias/fallo malloc)
    if (turnos_encontrados != NULL) {
        *turnos_encontrados = vector_turnos;
    }

    return contador;
}

//-------------------------------------------------------------
