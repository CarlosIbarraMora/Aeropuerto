#include <stdio.h>
#include <stdlib.h>

#define MAX_PISTAS 3
#define MAX_COLA 5

typedef struct {
    int id;
} Avion;

typedef struct {
    Avion *avion;  // Puntero a un avión
    int ocupado;
} Pista;

void llegadaAvion(Avion *avion, Pista *pistas, Avion **cola, int *numAvionesCola) {
    //Busca una pista libre
    for (int i = 0; i < MAX_PISTAS; i++) {
        if (!pistas[i].ocupado) {
            pistas[i].avion = avion;
            pistas[i].ocupado = 1;
            printf("Avion %d asignado a la pista %d.\n", avion->id, i + 1);
            return;
        }
    }

    // Si no hay pista disponible, se va a la cola
    if (*numAvionesCola < MAX_COLA) {
        cola[*numAvionesCola] = avion;
        (*numAvionesCola)++;
        printf("Avion %d aniadido a la cola.\n", avion->id);
    } else {
        printf("Cola de espera llena. Avion %d no puede aterrizar.\n", avion->id);
    }
}

void liberarPista(Pista *pistas, Avion **cola, int *numAvionesCola) {
    for (int i = 0; i < MAX_PISTAS; i++) {
        if (pistas[i].ocupado) {
            printf("Avion %d ha despegado de la pista %d.\n", pistas[i].avion->id, i + 1);
            pistas[i].ocupado = 0;

            // Si hay aviones en la cola, asignar el primero a la pista
            if (*numAvionesCola > 0) {
                pistas[i].avion = cola[0];
                pistas[i].ocupado = 1;
                printf("Avion %d asignado a la pista %d desde la cola.\n", cola[0]->id, i + 1);

                // Mover la cola hacia adelante
                for (int j = 1; j < *numAvionesCola; j++) {
                    cola[j - 1] = cola[j];
                }
                (*numAvionesCola)--;
            }
        }
    }
}

int main() {
    Pista pistas[MAX_PISTAS] = {{NULL, 0}, {NULL, 0}, {NULL, 0}};
    Avion *cola[MAX_COLA];
    int numAvionesCola = 0;

    int opcion, id = 1;

    do {
        printf("\n1. Llega un avion\n2. Liberar pista\n3. Salir\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch (opcion) {
            case 1: {

                Avion *nuevoAvion = (Avion *)malloc(sizeof(Avion));
                nuevoAvion->id = id++;
                llegadaAvion(nuevoAvion, pistas, cola, &numAvionesCola);
                break;
            }
            case 2:
                liberarPista(pistas, cola, &numAvionesCola);
                break;
            case 3:
                printf("Saliendo...\n");
                break;
            default:
                printf("Opcion invalida.\n");
        }
    } while (opcion != 3);

    for (int i = 0; i < numAvionesCola; i++) {
        free(cola[i]);
    }

    return 0;
}
