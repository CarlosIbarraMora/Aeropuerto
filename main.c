#include <stdio.h>
#define MAX_COLA 100

typedef struct {
    int id;
} Avion;

typedef struct {
    int ocupada;  // Indica si la pista está ocupada (1) o libre (0)
    Avion avion;  // Avión actualmente en la pista
} Pista;

Avion cola[MAX_COLA];  // Cola de espera de aviones
int frente = -1, final = -1;  // Indican los extremos de la cola

Pista pistas[3];  // Las tres pistas del aeropuerto

void llegadaAvion(Avion avion);
void liberarPista(int numeroPista);

int main() {
   // Iniciar pistas
    for (int i = 0; i < 3; i++) pistas[i].ocupada = 0;

    // 4 aviones de ejemplo con ID sencillo
    Avion avion1 = {1}, avion2 = {2}, avion3 = {3}, avion4 = {4};

    llegadaAvion(avion1);
    llegadaAvion(avion2);
    llegadaAvion(avion3);
    llegadaAvion(avion4);

    // Liberar dos pistas para mostrar cómo los aviones en cola se asignan a pistas
    liberarPista(2);
    liberarPista(1);

    return 0;
}

void llegadaAvion(Avion avion) {
    // Revisar si hay alguna pista libre para asignarle un avión
    for (int i = 0; i < 3; i++) {
        if (!pistas[i].ocupada) {
            pistas[i].ocupada = 1;
            pistas[i].avion = avion;
            printf("Avion %d asignado a la pista %d.\n", avion.id, i + 1);
            return;
        }
    }

    // Si no hay pistas libres, agregar el avión a la cola de espera
    if ((final + 1) % MAX_COLA == frente) {
        printf("La cola está llena, no se puede registrar el avion.\n");
        return;
    }

    final = (final + 1) % MAX_COLA;
    cola[final] = avion;
    if (frente == -1) frente = 0;
    printf("No hay pistas disponibles. Avion %d en cola.\n", avion.id);
}

void liberarPista(int numeroPista) {
    // Verificar si el número de pista es válido y está ocupada
    if (numeroPista < 1 || numeroPista > 3 || !pistas[numeroPista - 1].ocupada) {
        printf("Pista %d ya está libre o no es valida.\n", numeroPista);
        return;
    }

    printf("Pista %d liberada por el avion %d.\n", numeroPista, pistas[numeroPista - 1].avion.id);
    pistas[numeroPista - 1].ocupada = 0;

    if (frente == -1) {
        printf("No hay aviones en cola para asignar a la pista %d.\n", numeroPista);
        return;
    }

    // Asignar el primer avión de la cola a la pista liberada
    pistas[numeroPista - 1].ocupada = 1;
    pistas[numeroPista - 1].avion = cola[frente];
    printf("Avion %d de la cola asignado a la pista %d.\n", cola[frente].id, numeroPista);

    if (frente == final) {
        frente = final = -1;
    } else {
        frente = (frente + 1) % MAX_COLA;
    }
}