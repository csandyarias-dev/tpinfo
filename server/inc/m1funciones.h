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

//----------------------------------
// Funciones Auxiliares y de Impresión
//----------------------------------

void mostrar_paciente(nodo_paciente_t * actual);
void mostrar_responsable(nodo_responsable_t * actual);
void imprimir_fecha(nfecha_t f);
void imprimir_hora(nhora_t h);
void imprimir_fecha_hora(nfecha_t f, nhora_t h);
void mostrar_turno(nodo_turnos_t * actual);
void limpiar_buffer(void);
int leer_entero(int * valor);
int leer_uchar(unsigned char * valor);
int es_fecha_valida(nfecha_t f);
int es_hora_valida(int hora, int min, int am_pm);
const char * obtener_nombre_paciente(nodo_paciente_t * lista_pac, int pacID);
const char * obtener_nombre_responsable(nodo_responsable_t * lista_resp, int responID);

//----------------------------------
// Búsquedas y Consultas de Datos 
//----------------------------------

/**
    \fn      int ConsultarCoincidencias_PacienteID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe un ID, busca en la lista de pacientes y envia las coincidencias
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de coincidencias encontradas
*/
int ConsultarCoincidencias_PacienteID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarCoincidencias_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe un nombre, busca en la lista de pacientes y envia las coincidencias
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de coincidencias encontradas
*/
int ConsultarCoincidencias_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarCoincidencias_ResponsableID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe un ID, busca en la lista de responsables y envia las coincidencias
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de coincidencias encontradas
*/
int ConsultarCoincidencias_ResponsableID(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarCoincidencias_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe un nombre, busca en la lista de responsables y envia las coincidencias
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de coincidencias encontradas
*/
int ConsultarCoincidencias_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarTurnos_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe el nombre de un paciente y envia los turnos asociados al mismo
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de turnos encontrados
*/
int ConsultarTurnos_PacienteNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarTurnos_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe el nombre de un responsable y envia los turnos asociados al mismo
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de turnos encontrados
*/
int ConsultarTurnos_ResponsableNombre(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int ConsultarTurnos_Fecha(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recibe una fecha y envia todos los turnos registrados para ese dia
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad de turnos encontrados
*/
int ConsultarTurnos_Fecha(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int MostrarListadoCompletoPacientes(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recorre la lista completa de pacientes y los envia al cliente
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad total de pacientes enviados
*/
int MostrarListadoCompletoPacientes(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);


/**
    \fn      int MostrarListadoCompletoResponsables(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);
    \brief   Recorre la lista completa de responsables y los envia al cliente
    \author  Las Marmotas
    \param   socket_fd Socket del cliente
    \param   u_pac Puntero al ultimo ID de paciente
    \param   u_resp Puntero al ultimo ID de responsable
    \param   lista_pacientes Puntero a la cabeza de la lista de pacientes
    \param   lista_responsables Puntero a la cabeza de la lista de responsables
    \param   lista_turnos Puntero a la cabeza de la lista de turnos
    \param   tipos Puntero al vector dinamico de tipos de animales
    \param   cant_t Puntero a la cantidad actual de tipos registrados
    \param   u_tipo Puntero al ultimo ID historico generado para tipos
    \return  int Cantidad total de responsables enviados
*/
int MostrarListadoCompletoResponsables(int socket_fd, int *u_pac, int *u_resp, nodo_paciente_t **lista_pacientes, nodo_responsable_t **lista_responsables, nodo_turnos_t **lista_turnos, tipopac_t **tipos, int *cant_t, int *u_tipo);

#endif 
