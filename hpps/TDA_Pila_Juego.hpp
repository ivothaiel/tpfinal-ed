
#ifndef TDA_PILA_JUEGO_HPP
#define TDA_PILA_JUEGO_HPP

#include "TDA_Diccionario.hpp" 


const int MAX_PILA = 6;
typedef tinfo tcontenedor_pila[MAX_PILA]; // La pila almacena registros 'tinfo'

struct tpila_palabras {
    tcontenedor_pila datos; // Arreglo estático de palabras
    int cima;               // Índice del tope (se inicializa en -1)
};


void iniciar_pila(tpila_palabras &p) {
    p.cima = -1;
}

bool pila_vacia(tpila_palabras p) {
    return p.cima == -1;
}

bool pila_llena(tpila_palabras p) {
    return p.cima == MAX_PILA - 1;
}

void agregar_pila(tpila_palabras &p, tinfo nuevo) {
    if (pila_llena(p) == true) {
        cout << "ERROR: La pila del espejo magico esta llena." << endl;
    }
    else {
        p.cima++; 
        p.datos[p.cima] = nuevo;
    }
}
tinfo quitar_pila(tpila_palabras &p) {
    tinfo extraido;
    if (pila_vacia(p) == true) {
        strcpy(extraido.palabra, "ERROR_VACIA");
        return extraido;
    }
    else {
        extraido = p.datos[p.cima];
        p.cima--;                   
        return extraido;
    }
}

tinfo tope_pila(tpila_palabras p) {
    tinfo consultado;
    if (pila_vacia(p) == true) {
        strcpy(consultado.palabra, "ERROR_VACIA");
        return consultado;
    }
    else {
        consultado = p.datos[p.cima];
        return consultado;
    }
}

#endif