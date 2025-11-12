#ifndef TDA_RANKING_HPP
#define TDA_RANKING_HPP
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

const int TAM_CAD_RANK = 50; 
typedef char tcad[TAM_CAD_RANK];

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


void iniciar_lista_ranking(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}
void crear_nodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking; //
    if (nuevo != NULL) {
        nuevo->dato = dato_ranking;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
}
void insertar_ranking_ordenado(tlista_ranking &lista, pnodo_ranking nuevo) {
    pnodo_ranking i, ult;
    if (lista.inicio == NULL) {
        lista.inicio = nuevo;
        lista.inicio->sig = lista.inicio;
        lista.inicio->ant = lista.inicio;
    }
    else {
        ult = lista.inicio->ant; 
        if (nuevo->dato.puntaje > lista.inicio->dato.puntaje) {
            nuevo->sig = lista.inicio;
            nuevo->ant = ult;
            lista.inicio->ant = nuevo;
            ult->sig = nuevo;
            lista.inicio = nuevo; 
        }
        else { 
            i = lista.inicio->sig;
            

            while (i != lista.inicio && nuevo->dato.puntaje < i->dato.puntaje) {
                i = i->sig;
            }
            
      
            nuevo->ant = i->ant;
            nuevo->sig = i;
            i->ant->sig = nuevo;
            i->ant = nuevo;
        }
    }
    lista.cont++; // Incrementamos el contador
}


void mostrar_lista_ranking(tlista_ranking lista) {
    pnodo_ranking i;
    if (lista.inicio == NULL) {
        cout << "No hay vencedores para mostrar." << endl;
    }
    else {
        i = lista.inicio;
        do {
            cout << "  - Alias: " << i->dato.alias;
            cout << " (Puntaje: " << i->dato.puntaje << ")" << endl;
            i = i->sig;
        } while (i != lista.inicio);
    }
}


void liberar_lista_ranking(tlista_ranking &lista) {
    pnodo_ranking extraido;
    

    while (lista.inicio != NULL) {
        if (lista.cont == 1) { 
            extraido = lista.inicio;
            lista.inicio = NULL;
        }
        else { 
            extraido = lista.inicio;
            pnodo_ranking ult = lista.inicio->ant;
            lista.inicio = lista.inicio->sig;
            ult->sig = lista.inicio;
            lista.inicio->ant = ult;
        }
        
        lista.cont--;
        extraido->ant = NULL;
        extraido->sig = NULL;
        delete extraido;
    }
   
}

#endif 