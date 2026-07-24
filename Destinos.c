#include "destinos.h"
#include <stdio.h>
#include <stdlib.h>

static void liberarArbolViajes(Viaje *raiz)
{
    if (raiz == NULL)
        return;

    liberarArbolViajes(raiz->izq);
    liberarArbolViajes(raiz->der);
    free(raiz);
}

static void liberarPasajeros(FilaPasajeros *fila)
{
    if (fila == NULL)
        return;

    Pasajero *actual = fila->cabeza;
    while (actual != NULL)
    {
        Pasajero *siguiente = actual->siguiente;
        free(actual);
        actual = siguiente;
    }

    fila->cabeza = NULL;
    fila->final = NULL;
    fila->cantidad = 0;
}

static int destinoExiste(FilaDestinos *fila, int codigo)
{
    if (fila == NULL)
        return 0;

    Destino *actual = fila->cabeza;
    while (actual != NULL)
    {
        if (actual->codigo == codigo)
            return 1;
        actual = actual->siguiente;
    }
    return 0;
}

void inicializarFilaDestinos(FilaDestinos *fila)
{
    if (fila == NULL)
        return;

    fila->cabeza = NULL;
    fila->final = NULL;
    fila->cantidad = 0;
}

void registrarDestino(FilaDestinos *fila)
{
    if (fila == NULL)
        return;

    Destino *nuevo = malloc(sizeof(Destino));
    if (nuevo == NULL)
    {
        printf("\nError: No se pudo reservar memoria.\n");
        return;
    }

    printf("\n===== REGISTRAR DESTINO =====\n");
    printf("Codigo del destino: ");
    if (scanf("%d", &nuevo->codigo) != 1)
    {
        printf("Entrada invalida para el codigo.\n");
        free(nuevo);
        return;
    }

    if (destinoExiste(fila, nuevo->codigo))
    {
        printf("\nError: ya existe un destino con el codigo %d.\n", nuevo->codigo);
        free(nuevo);
        return;
    }

    printf("Nombre del destino: ");
    scanf(" %99[^\n]", nuevo->nombre);

    printf("Empresa de transporte: ");
    scanf(" %99[^\n]", nuevo->empresa);

    nuevo->pasajeros.cabeza = NULL;
    nuevo->pasajeros.final = NULL;
    nuevo->pasajeros.cantidad = 0;
    nuevo->arbolViajes = NULL;
    nuevo->siguiente = NULL;

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
    if (fila == NULL)
        return NULL;

    Destino *actual = fila->cabeza;
    while (actual != NULL)
    {
        if (actual->codigo == codigo)
            return actual;
        actual = actual->siguiente;
    }
    return NULL;
}

void mostrarDestinos(FilaDestinos *fila)
{
    if (fila == NULL || fila->cabeza == NULL)
    {
        printf("\nNo hay destinos registrados.\n");
        return;
    }

    printf("\n=========================================\n");
    printf("      DESTINOS REGISTRADOS\n");
    printf("=========================================\n");

    Destino *actual = fila->cabeza;
    while (actual != NULL)
    {
        printf("\nCodigo: %d\n", actual->codigo);
        printf("Nombre: %s\n", actual->nombre);
        printf("Empresa: %s\n", actual->empresa);
        actual = actual->siguiente;
    }

    printf("\n=========================================\n");
    printf("Total de destinos registrados: %d\n", fila->cantidad);
}

void modificarDestino(FilaDestinos *fila)
{
    if (fila == NULL)
        return;

    int codigo;
    printf("Ingrese el codigo del destino a modificar: ");
    if (scanf("%d", &codigo) != 1)
    {
        printf("Entrada invalida.\n");
        return;
    }

    Destino *destino = buscarDestino(fila, codigo);
    if (destino == NULL)
    {
        printf("\nDestino no encontrado.\n");
        return;
    }

    printf("Ingrese el nuevo nombre del destino: ");
    scanf(" %99[^\n]", destino->nombre);

    printf("Ingrese la nueva empresa de transporte: ");
    scanf(" %99[^\n]", destino->empresa);

    printf("\nDestino modificado correctamente.\n");
}

void liberarFilaDestinos(FilaDestinos *fila)
{
    if (fila == NULL)
        return;

    Destino *actual = fila->cabeza;
    while (actual != NULL)
    {
        Destino *siguiente = actual->siguiente;
        liberarPasajeros(&actual->pasajeros);
        liberarArbolViajes(actual->arbolViajes);
        free(actual);
        actual = siguiente;
    }

    fila->cabeza = NULL;
    fila->final = NULL;
    fila->cantidad = 0;
}
