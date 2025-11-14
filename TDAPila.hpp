//Define el TDA Pila Estática para las 6 palabras del juego.
#include "TDA_Base.hpp" 
const int MAX = 6;
typedef tinfo tcontenedor[MAX]; 

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
    return p.cima == MAX - 1;
}

void agregarpila(tpila &p, tinfo nuevo) {
    if (pilallena(p) == true) {
        cout << "ERROR: La pila del espejo magico esta llena." << endl;
    }
    else {
        p.cima++; 
        p.datos[p.cima] = nuevo; 
    }
}

tinfo quitarpila(tpila &p) {
    tinfo extraido;
    if (pilavacia(p) == true) {
        strcpy(extraido.palabra, "ERROR_VACIA");
        strcpy(extraido.definicion, "");
        strcpy(extraido.sinonimo, "");
    }
    else {
        extraido = p.datos[p.cima]; 
        p.cima--;                   
    }
    return extraido;
}


tinfo topepila(tpila p) {
    tinfo consultado;
    if (pilavacia(p) == true) {
        strcpy(consultado.palabra, "ERROR_VACIA");
        strcpy(consultado.definicion, "");
        strcpy(consultado.sinonimo, "");
    }
    else {
        consultado = p.datos[p.cima]; 
    }
    return consultado;
}