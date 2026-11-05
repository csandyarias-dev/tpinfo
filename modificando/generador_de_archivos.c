#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#define NOMBRE_SIZE 32

// Estructuras idénticas a tu encabezadogeneral.h para respetar los tipos y tamaños
typedef struct {
    unsigned short int min : 6;
    unsigned short int vacio1 : 2;
    unsigned short int hora : 5;   
    unsigned short int vacio2 : 2; 
    unsigned short int am_pm : 1;  
} bits_hora_t;

typedef union {
    unsigned short int valor; 
    bits_hora_t bits;     
} nhora_t;

typedef struct {
    unsigned int anio : 12;  
    unsigned int vacio1 : 1; 
    unsigned int mes : 4;   
    unsigned int vacio2 : 1;  
    unsigned int dia : 5;    
    unsigned int vacio3 : 1;  
} bits_fecha_t;

typedef union {
    unsigned int valor;   
    bits_fecha_t bits1; 
} nfecha_t;

typedef struct {
    int pacID;
    unsigned char tipoID;
    char nombre[30];
    nfecha_t nacimiento; 
    int responID;
} paciente_t;

typedef struct {
    int responID;
    char nombre[30];
    char apellido[30];
    unsigned long int telcont;
} responsable_t;

typedef struct {
    int responID; 
    int pacID; 
    nfecha_t fecha; 
    nhora_t hora;
} turnos_t;

int main(void) {
    FILE *fp;
    int ultimoID;

    // Crear la carpeta dat si no existe
    mkdir("dat", 0777);

    // ----------------------------------------------------
    // 1. Generar pacientes.dat (Lleva entero de último ID al inicio)
    // ----------------------------------------------------
    fp = fopen("dat/pacientes.dat", "wb");
    if (fp != NULL) {
        ultimoID = 2;
        fwrite(&ultimoID, sizeof(int), 1, fp);

        paciente_t p1 = {1, 1, "Firulais", {0}, 1};
        paciente_t p2 = {2, 2, "Michi", {0}, 2};

        fwrite(&p1, sizeof(paciente_t), 1, fp);
        fwrite(&p2, sizeof(paciente_t), 1, fp);

        fclose(fp);
        printf("[OK] pacientes.dat generado correctamente.\n");
    }

    // ----------------------------------------------------
    // 2. Generar responsables.dat (Lleva entero de último ID al inicio)
    // ----------------------------------------------------
    fp = fopen("dat/responsables.dat", "wb");
    if (fp != NULL) {
        ultimoID = 2;
        fwrite(&ultimoID, sizeof(int), 1, fp);

        responsable_t r1 = {1, "Juan", "Perez", 1122334455UL};
        responsable_t r2 = {2, "Maria", "Gomez", 1199887766UL};

        fwrite(&r1, sizeof(responsable_t), 1, fp);
        fwrite(&r2, sizeof(responsable_t), 1, fp);

        fclose(fp);
        printf("[OK] responsables.dat generado correctamente.\n");
    }

    // ----------------------------------------------------
    // 3. Generar turnos.dat (SOLO estructuras turnos_t, sin entero inicial)
    // ----------------------------------------------------
    fp = fopen("dat/turnos.dat", "wb");
    if (fp != NULL) {
        turnos_t t1;
        t1.responID = 1;
        t1.pacID = 1;
        t1.fecha.bits1.dia = 10;
        t1.fecha.bits1.mes = 9;
        t1.fecha.bits1.anio = 2026;
        t1.hora.bits.hora = 14;
        t1.hora.bits.min = 30;
        t1.hora.bits.am_pm = 0;

        turnos_t t2;
        t2.responID = 2;
        t2.pacID = 2;
        t2.fecha.bits1.dia = 12;
        t2.fecha.bits1.mes = 9;
        t2.fecha.bits1.anio = 2026;
        t2.hora.bits.hora = 10;
        t2.hora.bits.min = 15;
        t2.hora.bits.am_pm = 0;

        fwrite(&t1, sizeof(turnos_t), 1, fp);
        fwrite(&t2, sizeof(turnos_t), 1, fp);

        fclose(fp);
        printf("[OK] turnos.dat generado correctamente con estructuras turnos_t.\n");
    }

    printf("\n¡Archivos binarios y de texto listos en la carpeta 'dat/' respetando estrictamente las estructuras!\n");
    return 0;
}
