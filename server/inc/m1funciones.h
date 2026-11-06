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

int ConsultarCoincidencias_PacienteID(nodo_paciente_t *lista_pacientes, int id_ingresado, nodo_paciente_t **Paciente_encontrado);
int ConsultarCoincidencias_PacienteNombre(nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_paciente_t **Paciente_encontrado);
int ConsultarCoincidencias_ResponsableID(nodo_responsable_t *lista_responsables, int id_ingresado, nodo_responsable_t **Responsable_encontrado);
int ConsultarCoincidencias_ResponsableNombre(nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_responsable_t **Responsable_encontrado);
int ConsultarTurnos_PacienteNombre(nodo_turnos_t *lista_turnos, nodo_paciente_t *lista_pacientes, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);
int ConsultarTurnos_Fecha(nodo_turnos_t *lista_turnos, nfecha_t fecha_ingresada, nodo_turnos_t ***turnos_encontrados);
int ConsultarTurnos_ResponsableNombre(nodo_turnos_t *lista_turnos, nodo_responsable_t *lista_responsables, const char *nombre_ingresado, nodo_turnos_t ***turnos_encontrados);

//----------------------------------
// Opciones de Menú 1
//----------------------------------

void ConsultarPacientePorID_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado);
void ConsultarPacientePorNombre_Menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_paciente_t **Paciente_encontrado);
void ConsultarResponsablePorID_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado);
void ConsultarResponsablePorNombre_Menu1(nodo_responsable_t *lista_resp, nodo_responsable_t **Responsable_encontrado);
void ConsultarTurnosPorPacientes_Menu1(nodo_paciente_t *lista_pac, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
void ConsultarTurnosPorResponsable_Menu1(nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
void ConsultarTurnosPorFecha_Menu1(nodo_turnos_t *lista_turnos, nodo_turnos_t ***turnos_encontrados);
void MostrarListadoCompletoPacientes(nodo_paciente_t *lista_pac);
void MostrarListadoCompletoResponsables(nodo_responsable_t *lista_resp);
// void menu1(nodo_paciente_t *lista_pac, nodo_responsable_t *lista_resp, nodo_turnos_t *lista_turnos);

#endif 
