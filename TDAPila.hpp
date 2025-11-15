#ifndef TDAPILA_HPP
#define TDAPILA_HPP

#include "TDA_Base.hpp" 
const int MAXPILA = 6; 
typedef tpalabra tcontenedor[MAXPILA]; 

struct tpila {
    tcontenedor datos; 
    int cima;         
};


void iniciarpila(tpila &p) {
    p.cima = -1;
}

bool pilavacia(tpila p) {
    return p.cima == -1;
}

bool pilallena(tpila p) {
    return p.cima == MAXPILA - 1;
}


void agregarpila(tpila &p, tpalabra nuevo) {
    if (pilallena(p) == true) {
        cout << "ERROR: La pila del espejo magico esta llena." << endl;
    }
    else {
        p.cima++; 
        p.datos[p.cima] = nuevo; 
    }
}


tpalabra quitarpila(tpila &p) {
    tpalabra extraido;
    if (pilavacia(p) == true) {
        strcpy(extraido.palabra, "ERROR_VACIA");
        strcpy(extraido.definicion, "");
        strcpy(extraido.sinonimo, "");
        extraido.longitud = 0;
    }
    else {
        extraido = p.datos[p.cima]; 
        p.cima--;                   
    }
    return extraido;
}

tpalabra topepila(tpila p) {
    tpalabra consultado;
    if (pilavacia(p) == true) {
        strcpy(consultado.palabra, "ERROR_VACIA");
        strcpy(consultado.definicion, "");
        strcpy(consultado.sinonimo, "");
        consultado.longitud = 0;
    }
    else {
        consultado = p.datos[p.cima]; 
    }
    return consultado;
}

#endif 