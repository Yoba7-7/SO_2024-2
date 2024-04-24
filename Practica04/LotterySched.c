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

void schedule(struct Proceso procs[], int num_procs)
{
	int tickets_totales = 0;
	int i , ganador;
	int id_ganador = 0;

	//calucla el numero total de tickets
	for (int i = 0; i < num_procs; ++i)
	{
		tickets_totales += procs[i].tickets;
	}

	//selecciona un numero ganador
	ganador = rand() % tickets_totales;

	//encuentra el ticket ganador
	for (int i = 0; i < num_procs; ++i)
	{
		if (ganador < procs[i].tickets && procs[i].estado == 1)
		{
			printf("Proceso ganador: %d \n" , procs[i].id);
			id_ganador = procs[i].id;
			break;
		}
		ganador -= procs[i].tickets,
	}

	// ejecutar el proceso ganador
	printf("Ejecutando el proceso %d ...\n", id_ganador);
	for (int i = 0; i < num_procs; ++i)
	{
		imprime_progreso(procs[id_ganador].tiempo_rest, procs[id_ganador].quantum);
		sleep(1);
		procs[id_ganador].tiempo_rest --;
		procs[id_ganador].tickets = 0;
		if (procs[id_ganador].tiempo_rest <= 0)
		{
			procs[id_ganador].estado = 0;
			printf("Proceso terminado, se ha ejecutado con exito.\n Procesos por ejecutar: ");
			for (int j = 0; j < NRO_PROCESOS; ++j)
			{
				if (procs[j].estado == 1)
				{
					printf("Proceso: %d" , procs[j].id);
				}
			}
		}
	}























}