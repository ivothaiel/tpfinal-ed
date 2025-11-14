
#ifndef TDA_JUGADOR_ABB_HPP 
#define TDA_JUGADOR_ABB_HPP

#include <iostream>
#include <stdio.h>   
#include <stdlib.h>  
#include <string.h>   

using namespace std; 

const int TAM_CAD = 50; 
typedef char tcad[TAM_CAD];

typedef struct tjugador {
    tcad nombre;
    tcad apellido;
    tcad signo;
    tcad alias; //clave
    int juegos_ganados;
    int mejor_puntaje;
    int puntaje_acumulado;
};


typedef struct tnodo_jugador *pnodo_jugador;
struct tnodo_jugador {
    tjugador dato;        // El registro del jugador
    pnodo_jugador izq;    // Puntero al sub-árbol izquierdo (< alias)
    pnodo_jugador der;    // Puntero al sub-árbol derecho (> alias)
};

// --- 3. Implementación de Operaciones del TDA ---


void iniciar_abb(pnodo_jugador &arbol) {
    arbol = NULL;
}


void crear_nodo_jugador(pnodo_jugador &nuevo, tjugador dato_jugador) {
    nuevo = new tnodo_jugador; //
    
    if (nuevo != NULL) {
        nuevo->dato = dato_jugador; 
        nuevo->izq = NULL;          
        nuevo->der = NULL;          
    }
}


void insertar_jugador_abb(pnodo_jugador &arbol, pnodo_jugador nuevo) {
    if (arbol == NULL) {
        arbol = nuevo;
    }
    else {
        if (strcmp(nuevo->dato.alias, arbol->dato.alias) < 0) {

            insertar_jugador_abb(arbol->izq, nuevo);
        }
        else {

            insertar_jugador_abb(arbol->der, nuevo);
        }
    }
}

pnodo_jugador buscar_jugador_abb(pnodo_jugador arbol, tcad alias_buscado) {
    if (arbol == NULL) {
        return NULL;
    }
    else {
       
        int comparacion = strcmp(alias_buscado, arbol->dato.alias);


        if (comparacion == 0) {
            return arbol;
        }
        else {
  
            if (comparacion < 0) {

                return buscar_jugador_abb(arbol->izq, alias_buscado);
            }
            else {
   
                return buscar_jugador_abb(arbol->der, alias_buscado);
            }
        }
    }
}

void listar_jugadores_abb(pnodo_jugador arbol) {
    if (arbol != NULL) {
        listar_jugadores_abb(arbol->izq);
        cout << "----------------------------------------" << endl;
        cout << "Alias: " << arbol->dato.alias << endl;
        cout << "Nombre: " << arbol->dato.nombre << " " << arbol->dato.apellido << endl;
        cout << "Signo: " << arbol->dato.signo << endl;
        cout << "Puntaje Max: " << arbol->dato.mejor_puntaje << endl;
        cout << "Puntaje Acum: " << arbol->dato.puntaje_acumulado << endl;
        cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
        listar_jugadores_abb(arbol->der);
    }
}
void liberar_abb(pnodo_jugador &arbol) {
    if (arbol != NULL) {
        // 1. Izquierda
        liberar_abb(arbol->izq);
        // 2. Derecha
        liberar_abb(arbol->der);
        
        // 3. Raíz (Procesar)
        delete arbol; 
        arbol = NULL; 
    }
}

#endif 