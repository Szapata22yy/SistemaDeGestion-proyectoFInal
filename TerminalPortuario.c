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