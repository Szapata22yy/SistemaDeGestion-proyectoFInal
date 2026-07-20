#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_TEXTO 100
 
 
//nodo de pasajero
typedef struct Pasajero {
    int  cedula;
    char nombre[MAX_TEXTO];
    struct Pasajero *siguiente;
} Pasajero;
 
//Cola FIFO de pasajeros
typedef struct {
    Pasajero *frente;
    Pasajero *final;
    int cantidad;
} FilaPasajeros;
 
//Nodo del ABB de viajes programados
typedef struct Viaje {
    int  codigoViaje;          
    char hora[10];              
    char embarcacion[MAX_TEXTO];
    int  capacidad;
    struct Viaje *izq;
    struct Viaje *der;
} Viaje;
 
//Nodo de destino (nodo de la FIFO de destinos) ---- */
typedef struct Destino {
    int  codigo;
    char nombre[MAX_TEXTO];
    char empresa[MAX_TEXTO];    //empresa de transporte maritimo
    FilaPasajeros pasajeros;    //FIFO de pasajeros del destino 
    Viaje *arbolViajes;         //raiz del ABB de viajes del destino
    struct Destino *siguiente;
} Destino;
 
//Cola FIFO de destinos
typedef struct {
    Destino *frente;
    Destino *final;
    int cantidad;
} FilaDestinos;

void inicializarFilaDestinos(FilaDestinos *fila);
void registrarDestino(FilaDestinos *fila);
Destino *buscarDestino(FilaDestinos *fila, int codigo);
void mostrarDestinos(FilaDestinos *fila);
void modificarDestino(FilaDestinos *fila);

int main()
{
    FilaDestinos destinos;

    inicializarFilaDestinos(&destinos);

    registrarDestino(&destinos);

    return 0;
}
void inicializarFilaDestinos(FilaDestinos *fila)
{
    fila->frente = NULL;
    fila->final = NULL;
    fila->cantidad = 0;
}

void registrarDestino(FilaDestinos *fila)
{
 Destino *nuevo = (Destino *)malloc(sizeof(Destino));

    if (nuevo == NULL)
    {
        printf("\nError: No se pudo reservar memoria.\n");
        return;
    }

    printf("\n===== REGISTRAR DESTINO =====\n");

    printf("Codigo del destino: ");
    scanf("%d", &nuevo->codigo);

    printf("Nombre del destino: ");
    scanf(" %[^\n]", nuevo->nombre);

    printf("Empresa de transporte: ");
    scanf(" %[^\n]", nuevo->empresa);

    // Inicializar la cola de pasajeros
    nuevo->pasajeros.frente = NULL;
    nuevo->pasajeros.final = NULL;
    nuevo->pasajeros.cantidad = 0;

    // Inicializar el árbol de viajes
    nuevo->arbolViajes = NULL;

    nuevo->siguiente = NULL;

    // Insertar en la cola FIFO
    if (fila->frente == NULL)
    {
        fila->frente = nuevo;
        fila->final = nuevo;
    }
    else
    {
        fila->final->siguiente = nuevo;
        fila->final = nuevo;
    }

    fila->cantidad++;

    printf("\nDestino registrado correctamente.\n");
}

Destino *buscarDestino(FilaDestinos *fila, int codigo)
{
    return NULL;
}

void mostrarDestinos(FilaDestinos *fila)
{

}

void modificarDestino(FilaDestinos *fila)
{

}