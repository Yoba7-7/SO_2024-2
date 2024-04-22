#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

#define NRO_PROCESOS = 5
#define QUANTUM_INIC = 10
#define QUANTUM_FINAL = 10
#define NRO_TICKETS = 100

struct Proceso
{
	int id;
	int tickets;
	int quantum;
	int tiempo_rest;
	int estado;
	int posicion;
};

void imprime_progreso(int tiempo_rest, int tiempo_total)
{
	printf("Ejecutando proceso: %d de %d. Tiempo restante. \n", tiempo_total - tiempo_rest + 1, tiempo_total);
}

void schedule(struct Proceso procs[], int num procs)
{
	int tickets_totales = 0;
	int i , ganador;
	int id_ganador;

	
}