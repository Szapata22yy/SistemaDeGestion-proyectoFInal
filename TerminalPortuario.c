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
    Pasajero *cabeza;
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
    Destino *cabeza;
    Destino *final;
    int cantidad;
} FilaDestinos;

void inicializarFilaDestinos(FilaDestinos *fila);
void registrarDestino(FilaDestinos *fila);
Destino *buscarDestino(FilaDestinos *fila, int codigo);
void mostrarDestinos(FilaDestinos *fila);
void modificarDestino(FilaDestinos *fila);
void menu(FilaDestinos *fila); 

int main()
{
    FilaDestinos destinos;

    inicializarFilaDestinos(&destinos);

    menu(&destinos);

    return 0;
}
void inicializarFilaDestinos(FilaDestinos *fila)
{
    fila->cabeza = NULL;
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
    nuevo->pasajeros.cabeza = NULL;
    nuevo->pasajeros.final = NULL;
    nuevo->pasajeros.cantidad = 0;

    // Inicializar el árbol de viajes
    nuevo->arbolViajes = NULL;

    nuevo->siguiente = NULL;

    // Insertar en la cola FIFO
    if (fila->cabeza == NULL)
    {
        fila->cabeza = nuevo;
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
    // Si la cola esta vacia
    if(fila->cabeza == NULL)
    {
        printf("\nNo hay destinos registrados. \n");
        return NULL;
    }
    
    // Apuntador auxiliar para recorrer la cola
    Destino *aux = fila->cabeza;
    
    // Recorrer toda la cola

    while (aux != NULL)
    {
        if(aux->codigo == codigo)
        {
            return aux; //Destino encontrado

        }

        aux = aux->siguiente;
    }

    // Si termina el recorrido y no lo encontro
    printf("\nNo existe un destino con el codigo %d.\n", codigo);

    return NULL; 
}

void mostrarDestinos(FilaDestinos *fila)
{
    // Verificar si la cola está vacía
    if (fila->cabeza == NULL)
    {
        printf("\nNo hay destinos registrados.\n");
        return;
    }

    Destino *aux = fila->cabeza;

    printf("\n=========================================\n");
    printf("      DESTINOS REGISTRADOS\n");
    printf("=========================================\n");

    while (aux != NULL)
    {
        printf("\nCodigo: %d\n", aux->codigo);
        printf("Nombre: %s\n", aux->nombre);
        printf("Empresa: %s\n", aux->empresa);

        aux = aux->siguiente;
    }

    printf("\n=========================================\n");
    printf("Total de destinos registrados: %d\n", fila->cantidad);

}

void modificarDestino(FilaDestinos *fila)
{

}

void menu(FilaDestinos *fila)
{
    int opcion;

    do
    {
        printf("\n=========================================\n");
        printf("   SISTEMA PORTUARIO TURISTICO\n");
        printf("          BUENAVENTURA\n");
        printf("=========================================\n");
        printf("1. Registrar nuevo destino\n");
        printf("2. Mostrar destinos registrados\n");
        printf("3. Buscar destino\n");
        printf("4. Modificar destino\n");
        printf("5. Salir\n");
        printf("=========================================\n");
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion)
        {
            case 1:
                registrarDestino(fila);
                break;

            case 2:
                mostrarDestinos(fila);
                break;

            case 3:
                printf("\nFuncion en desarrollo.\n");
                break;

            case 4:
                printf("\nFuncion en desarrollo.\n");
                break;

            case 5:
                printf("\nGracias por usar el sistema.\n");
                break;

            default:
                printf("\nOpcion invalida. Intente nuevamente.\n");
        }

    } while(opcion != 5);
}