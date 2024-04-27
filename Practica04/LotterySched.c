#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define NUM_PROCESOS 5
#define QUANTUM_TOTAL 10

typedef struct {
    int id;
    int quantum;
    int tiempo_cpu;
    int boletos;
    int *numeros;
    int estado; // 0: En espera, 1: Ejecutando, 2: Terminado
} Proceso;

Proceso procesos[NUM_PROCESOS];

void asignar_recursos() {
    srand(time(NULL));
    for (int i = 0; i < NUM_PROCESOS; i++) {
        procesos[i].id = i + 1; // Asignar un ID único a cada proceso
        procesos[i].quantum = rand() % (QUANTUM_TOTAL / 2) + 1; // Quantum aleatorio
        procesos[i].tiempo_cpu = 0;
        procesos[i].boletos = rand() % 10 + 1; // Número aleatorio de boletos
        procesos[i].numeros = (int *)malloc(sizeof(int) * procesos[i].boletos);
        for (int j = 0; j < procesos[i].boletos; j++) {
            procesos[i].numeros[j] = rand() % 100; // Números aleatorios
        }
        procesos[i].estado = 0; // Estado inicial: En espera
    }
}

void imprimir_proceso(Proceso p) {
    printf("Proceso ID: %d | Estado: %d | Quantum restante: %d | Tiempo restante: %d\n", p.id, p.estado, p.quantum, QUANTUM_TOTAL - p.tiempo_cpu);
}

void imprimir_detalles() {
    for (int i = 0; i < NUM_PROCESOS; i++) {
        imprimir_proceso(procesos[i]);
    }
}

int rifa_loteria() {
    int total_boletos = 0;
    for (int i = 0; i < NUM_PROCESOS; i++) {
        total_boletos += procesos[i].boletos;
    }
    return rand() % total_boletos;
}

void ejecutar_proceso(int ganador) {
    int boletos_acumulados = 0;
    for (int i = 0; i < NUM_PROCESOS; i++) {
        boletos_acumulados += procesos[i].boletos;
        if (ganador < boletos_acumulados) {
            printf("Ejecutando proceso ID: %d\n", procesos[i].id);
            procesos[i].estado = 1; // Estado: Ejecutando
            procesos[i].quantum--;
            procesos[i].tiempo_cpu++;
            if (procesos[i].quantum == 0) {
                if (procesos[i].tiempo_cpu < QUANTUM_TOTAL) {
                    printf("Proceso ID: %d utiliza todo su quantum, pero aún no ha terminado.\n", procesos[i].id);
                } else {
                    printf("Proceso ID: %d termina su ejecución.\n", procesos[i].id);
                    procesos[i].estado = 2; // Estado: Terminado
                    free(procesos[i].numeros); // Liberar memoria aquí
                }
            }
            break;
        }
    }
}

int main() {
    asignar_recursos();
    int todos_terminados = 0; // Cambiamos a 0 para que el bucle se ejecute al menos una vez
    while (!todos_terminados) { // Verificamos si todos los procesos han terminado
        imprimir_detalles();
        int ganador = rifa_loteria();
        ejecutar_proceso(ganador);
        // Verificamos si todos los procesos han terminado
        todos_terminados = 1;
        for (int i = 0; i < NUM_PROCESOS; i++) {
            if (procesos[i].estado != 2) {
                todos_terminados = 0;
                break;
            }
        }
    }

    printf("Todos los procesos han terminado. Finalizando el programa.\n");

    return 0;
}
