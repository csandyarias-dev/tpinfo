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

void mostrar_paciente(paciente_t * actual);
void mostrar_responsable(responsable_t * actual);
void imprimir_fecha(nfecha_t f);
void imprimir_hora(nhora_t h);
void imprimir_fecha_hora(nfecha_t f, nhora_t h);
void mostrar_turno(turnos_t * actual);
void limpiar_buffer(void);
int leer_entero(int * valor);
int leer_uchar(unsigned char * valor);
int es_fecha_valida(nfecha_t f);
int es_hora_valida(int hora, int min, int am_pm);

//----------------------------------
// Opciones de Menú 1
//----------------------------------

void ConsultarPacientePorID_Menu1(int socket_fd);
void ConsultarPacientePorNombre_Menu1(int socket_fd);
void ConsultarResponsablePorID_Menu1(int socket_fd);
void ConsultarResponsablePorNombre_Menu1(int socket_fd);
void ConsultarTurnosPorPacientes_Menu1(int socket_fd);
void ConsultarTurnosPorResponsable_Menu1(int socket_fd);
void ConsultarTurnosPorFecha_Menu1(int socket_fd);
void MostrarListadoCompletoPacientes(int socket_fd);
void MostrarListadoCompletoResponsables(int socket_fd);

#endif 
