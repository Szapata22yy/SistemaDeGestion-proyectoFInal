#include "viajes.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int alturaNodo(Viaje *n) {
    if (n == NULL) return 0;
    return n->altura;
}

static int max(int a, int b) {
    return (a > b) ? a : b;
}

static Viaje *rotarDerecha(Viaje *y) {
    Viaje *x = y->izq;
    Viaje *T2 = x->der;

    x->der = y;
    y->izq = T2;

    y->altura = max(alturaNodo(y->izq), alturaNodo(y->der)) + 1;
    x->altura = max(alturaNodo(x->izq), alturaNodo(x->der)) + 1;

    return x;
}

static Viaje *rotarIzquierda(Viaje *x) {
    Viaje *y = x->der;
    Viaje *T2 = y->izq;

    y->izq = x;
    x->der = T2;

    x->altura = max(alturaNodo(x->izq), alturaNodo(x->der)) + 1;
    y->altura = max(alturaNodo(y->izq), alturaNodo(y->der)) + 1;

    return y;
}

static int getBalance(Viaje *n) {
    if (n == NULL) return 0;
    return alturaNodo(n->izq) - alturaNodo(n->der);
}

static Viaje *crearNodoViaje(int codigo, const char *hora, const char *embar, int capacidad) {
    Viaje *n = (Viaje *)malloc(sizeof(Viaje));
    if (!n) return NULL;
    n->codigoViaje = codigo;
    strncpy(n->hora, hora, sizeof(n->hora)-1);
    n->hora[sizeof(n->hora)-1] = '\0';
    strncpy(n->embarcacion, embar, sizeof(n->embarcacion)-1);
    n->embarcacion[sizeof(n->embarcacion)-1] = '\0';
    n->capacidad = capacidad;
    n->izq = n->der = NULL;
    n->altura = 1;
    return n;
}

Viaje *insertarViaje(Viaje *raiz, int codigo, const char *hora, const char *embar, int capacidad) {
    if (raiz == NULL) {
        return crearNodoViaje(codigo, hora, embar, capacidad);
    }

    if (codigo < raiz->codigoViaje)
        raiz->izq = insertarViaje(raiz->izq, codigo, hora, embar, capacidad);
    else if (codigo > raiz->codigoViaje)
        raiz->der = insertarViaje(raiz->der, codigo, hora, embar, capacidad);
    else
        return raiz; // claves duplicadas no permitidas

    raiz->altura = 1 + max(alturaNodo(raiz->izq), alturaNodo(raiz->der));

    int balance = getBalance(raiz);

    // Rotaciones
    if (balance > 1 && codigo < raiz->izq->codigoViaje)
        return rotarDerecha(raiz);

    if (balance < -1 && codigo > raiz->der->codigoViaje)
        return rotarIzquierda(raiz);

    if (balance > 1 && codigo > raiz->izq->codigoViaje) {
        raiz->izq = rotarIzquierda(raiz->izq);
        return rotarDerecha(raiz);
    }

    if (balance < -1 && codigo < raiz->der->codigoViaje) {
        raiz->der = rotarDerecha(raiz->der);
        return rotarIzquierda(raiz);
    }

    return raiz;
}

Viaje *buscarViaje(Viaje *raiz, int codigo) {
    if (raiz == NULL) return NULL;
    if (codigo == raiz->codigoViaje) return raiz;
    if (codigo < raiz->codigoViaje) return buscarViaje(raiz->izq, codigo);
    return buscarViaje(raiz->der, codigo);
}

void mostrarViajes(Viaje *raiz) {
    if (raiz == NULL) return;
    mostrarViajes(raiz->izq);
    printf("\nCodigo: %d\n", raiz->codigoViaje);
    printf("Hora: %s\n", raiz->hora);
    printf("Embarcacion: %s\n", raiz->embarcacion);
    printf("Capacidad: %d\n", raiz->capacidad);
    mostrarViajes(raiz->der);
}
