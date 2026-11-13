//==============================================================================
//-- PROTOTIPOS DE FUNCIONES MAIN 1 --
//==============================================================================
/*
Menú 1 - Consultar información
Una vez ingresado al menú 1 mostrará las siguientes opciones:
1.01) Consultar Paciente por ID
1.02) Consultar Paciente por Nombre
1.03) Consultar Responsable por ID
1.04) Consultar Responsable por Nombre y Apellido
1.05) Consultar Turnos por Pacientes
1.06) Consultar Turnos por Responsables
1.07) Consultar Turnos por fecha
1.08) Mostrar el listado completo de Pacientes
1.09) Mostrar el listado completo de Responsables
1.10) Volver
*/
#ifndef ENCABEZADO_MAIN1_H
#define ENCABEZADO_MAIN1_H

#define RECORRIENDO 1
#define FIN 0

//----------------------------------
// Funciones Auxiliares y de Impresión
//----------------------------------


/**
	\fn     void mostrar_paciente(paciente_t * actual)
	\brief  Imprime el paciente
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  paciente_t * actual
	\return void
*/
void mostrar_paciente(paciente_t * actual);


/**
	\fn     void mostrar_responsable(responsable_t * actual)
	\brief  Imprime el responsable
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  responsable_t * actual
	\return void
*/
void mostrar_responsable(responsable_t * actual);


/**
	\fn     void imprimir_fecha(nfecha_t f) 
	\brief  Imprime la fecha 
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nfecha_t f
	\return void
*/
void imprimir_fecha(nfecha_t f);


/**
	\fn     void imprimir_hora(nhora_t h) 
	\brief  Imprime la hora
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nhora_t h
	\return void
*/
void imprimir_hora(nhora_t h);


/**
	\fn     void imprimir_fecha_hora(nfecha_t f, nhora_t h) 
	\brief  Imprime la fecha y la hora
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  nfecha_t f, nhora_t h
	\return void
*/
void imprimir_fecha_hora(nfecha_t f, nhora_t h);


/**
	\fn     void mostrar_turno(turnos_t * actual);
	\brief  Imprime el turno
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  turnos_t * actual
	\return void
*/
void mostrar_turno(turnos_t * actual);


/**
	\fn     void limpiar_buffer(void);
	\brief  Descarta lo que quedo en el buffer de entrada hasta el salto de linea
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  No recibe parametros
	\return No retorna
*/
void limpiar_buffer(void);


/**
	\fn     int leer_entero(int * valor);
	\brief  Lee un numero entero por teclado y chequea que sea un numero
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  valor: puntero donde se guarda el numero leido
	\return 1 si se leyo un numero, 0 si no
*/
int leer_entero(int * valor);


/**
	\fn     int leer_uchar(int * valor);
	\brief  Lee un unsigned char por teclado y chequea que sea un unsigned char
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  valor: puntero donde se guarda el uchar leido
	\return 1 si se leyo un numero, 0 si no
*/
int leer_uchar(unsigned char * valor);


/**
	\fn     int es_fecha_valida(nfecha_t f);
	\brief  Chequea que la fecha exista (contempla años bisiestos)
	\author Las Marmotas
	\date   2026.10.29
	\param  f: fecha a chequear
	\return 1 si la fecha es valida, 0 si no
*/
int es_fecha_valida(nfecha_t f);


/**
	\fn     int es_hora_valida(int hora, int min, int am_pm)
	\brief  Chequea que la hora sea valida
	\author Las Marmotas
	\date   2026.10.29
	\param  int hora, int min, int am_pm
	\return 1 si la hora es valida, 0 si no
*/
int es_hora_valida(int hora, int min, int am_pm);


/**
	\fn     int coincide_responsable(responsable_t r, const char *nom, const char *ape);
	\brief  Verifica si el responsable coincide por nombre y/o apellido (insensible a mayusculas)
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  responsable_t r, const char *nom, const char *ape
	\return int coincide
*/
int coincide_responsable(responsable_t r, const char *nom, const char *ape);

//----------------------------------
// Opciones de Menú 1
//----------------------------------

/**
	\fn     void ConsultarPacientePorID_Menu1(int socket_fd);
	\brief  Consulta el paciente en el servidor por medio del ID
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarPacientePorID_Menu1(int socket_fd);


/**
	\fn     void ConsultarPacientePorNombre_Menu1(int socket_fd);
	\brief  Consulta el paciente en el servidor por medio del Nombre
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarPacientePorNombre_Menu1(int socket_fd);


/**
	\fn     void ConsultarResponsablePorID_Menu1(int socket_fd);
	\brief  Consulta el responsable en el servidor por medio del ID
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarResponsablePorID_Menu1(int socket_fd);


/**
	\fn     void ConsultarResponsablePorNombre_Menu1(int socket_fd);
	\brief  Consulta el responsable en el servidor por medio del nombre
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarResponsablePorNombre_Menu1(int socket_fd);


/**
	\fn     void ConsultarTurnosPorPacientes_Menu1(int socket_fd);
	\brief  Consulta un turno en el servidor por medio del paciente
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarTurnosPorPacientes_Menu1(int socket_fd);


/**
	\fn     void ConsultarTurnosPorResponsable_Menu1(int socket_fd);
	\brief  Consulta un turno en el servidor por medio del responsable
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarTurnosPorResponsable_Menu1(int socket_fd);


/**
	\fn     void ConsultarTurnosPorFecha_Menu1(int socket_fd);
	\brief  Consulta un turno en el servidor por medio de su fecha
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void ConsultarTurnosPorFecha_Menu1(int socket_fd);


/**
	\fn     void MostrarListadoCompletoPacientes(int socket_fd);
	\brief  Muestra el listado completo de los pacientes registrados
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void MostrarListadoCompletoPacientes(int socket_fd);


/**
	\fn     void MostrarListadoCompletoResponsable(int socket_fd);
	\brief  Muestra el listado completo de los responsables registrados
	\author Grupo Las Marmotas
	\date   2026.11.13
	\param  int socket_fd
	\return void
*/
void MostrarListadoCompletoResponsable(int socket_fd);

#endif 
