#include <iostream>
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
void iniciarlista(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}

void crearnodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking; 
    if (nuevo != NULL) { 
        nuevo->dato = dato_ranking; 
        nuevo->ant = NULL; 
        nuevo->sig = NULL;
    }
}

void insertarordenado_ranking(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {
    if (nuevo->dato.puntaje >= actual->dato.puntaje) {
        nuevo->ant = actual->ant; 
        nuevo->sig = actual;
        actual->ant->sig = nuevo; 
        actual->ant = nuevo;
    }
    else if (actual->sig == inicio_lista) {
        nuevo->ant = actual; 
        nuevo->sig = inicio_lista;
        actual->sig = nuevo; 
        inicio_lista->ant = nuevo;
    }else{ 
        insertarordenado_ranking(actual->sig, nuevo, inicio_lista);
    }
}

void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {
    if (lista.inicio == NULL) {
        lista.inicio = nuevo; 
        lista.inicio->sig = lista.inicio; 
        lista.inicio->ant = lista.inicio;
    } else {
        insertarordenado_ranking(lista.inicio, nuevo, lista.inicio); 
        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje){ 
            lista.inicio = nuevo;
        }
    }
    lista.cont++;
}

void mostrarlista(tlista_ranking lista, bool creciente) {
    pnodo_ranking i;
    if (lista.inicio == NULL) { cout << "  No hay vencedores para mostrar." << endl; }
    else {
        if (creciente) {
            i = lista.inicio->ant;
            do {
                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->ant; 
            } while (i != lista.inicio->ant); 
        } else {
            i = lista.inicio;
            do {
                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->sig; 
            } while (i != lista.inicio); 
        }
    }
}

void liberarlista(tlista_ranking &lista) {
    pnodo_ranking p, aux;
    if (lista.inicio != NULL) {
        p = lista.inicio; 
        lista.inicio->ant->sig = NULL; 
        while (p != NULL){ 
            aux = p; 
            p = p->sig; 
            delete aux;
        }
        iniciarlista(lista);
    }
}