#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// --- DEFINICION ---
struct tinfo_ranking {
    tcad alias;
    int puntaje;
};

typedef struct tnodo_ranking *pnodo_ranking;

struct tnodo_ranking {
    tinfo_ranking dato;
    pnodo_ranking ant;
    pnodo_ranking sig;
};

struct tlista_ranking {
    pnodo_ranking inicio;
    int cont;
};

// --- IMPLEMENTACION ---

// Inicializa la lista del ranking.
void iniciarlista(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}

// Crea un nuevo nodo.
void crearnodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking;
    if (nuevo != NULL) {
        nuevo->dato = dato_ranking;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
}

// Inserta un nodo de forma ordenada (de mayor a menor puntaje).
void insertarordenado_ranking(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {

    // Caso 1: insertar antes del actual
    if (nuevo->dato.puntaje >= actual->dato.puntaje) {
        nuevo->ant = actual->ant;
        nuevo->sig = actual;
        actual->ant->sig = nuevo;
        actual->ant = nuevo;
    }
    // Caso 2: insertar al final (actual->sig vuelve al inicio)
    else if (actual->sig == inicio_lista) {
        nuevo->ant = actual;
        nuevo->sig = inicio_lista;
        actual->sig = nuevo;
        inicio_lista->ant = nuevo;
    }
    else {
        // Caso 3: avanzar recursivamente
        insertarordenado_ranking(actual->sig, nuevo, inicio_lista);
    }
}

// Controla el caso de lista vacía y define nuevo inicio si corresponde.
void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {

    // Caso 1: lista vacía
    if (lista.inicio == NULL) {
        lista.inicio = nuevo;
        lista.inicio->sig = lista.inicio;
        lista.inicio->ant = lista.inicio;
    }
    else {
        // Insertar ordenadamente
        insertarordenado_ranking(lista.inicio, nuevo, lista.inicio);

        // Si es el mayor puntaje, actualizar inicio
        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje) {
            lista.inicio = nuevo;
        }
    }

    lista.cont++;
}

// Recorre la lista circular en orden creciente o decreciente.
void mostrarlista(tlista_ranking lista, bool creciente) {
    pnodo_ranking i;

    if (lista.inicio == NULL) {
        cout << "No hay vencedores para mostrar." << endl;
    }
    else {
        if (creciente) {
            // Desde el final hacia atrás
            i = lista.inicio->ant;

            do {
                cout << " - Alias: " << i->dato.alias
                     << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->ant;
            } while (i != lista.inicio->ant);
        }
        else {
            // Desde el inicio hacia adelante
            i = lista.inicio;

            do {
                cout << " - Alias: " << i->dato.alias
                     << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->sig;
            } while (i != lista.inicio);
        }
    }
}

// Libera toda la memoria dinámica de la lista.
void liberarlista(tlista_ranking &lista) {
    pnodo_ranking p, aux;

    if (lista.inicio != NULL) {
        p = lista.inicio;

        // Rompe la circularidad para liberar con while normal
        lista.inicio->ant->sig = NULL;

        while (p != NULL) {
            aux = p;
            p = p->sig;
            delete aux;
        }

        iniciarlista(lista);
    }
}
