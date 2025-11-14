// Define el TDA Pila Estatica para las 6 palabras del juego

#include "TDA_Base.hpp" 

const int MAX = 6;

typedef tpalabra tcontenedor[MAX]; 

struct tpila {
    tcontenedor datos; 
    int cima;         
};


void iniciar_pila(tpila &p) {
    p.cima = -1;
}


bool pila_vacia(tpila p) {
    return p.cima == -1;
}


bool pila_llena(tpila p) {
    return p.cima == MAX - 1;
}

void agregar_pila(tpila &p, tinfo nuevo) {
    if (pila_llena(p) == true) {
        cout << "ERROR: La pila del espejo magico esta llena." << endl;
    }
    else {
        p.cima++; 
        p.datos[p.cima] = nuevo; 
    }
}

tpalabra quitar_pila(tpila &p) {
    tpalabra extraido;
    if (pila_vacia(p) == true) {
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


tpalabra tope_pila(tpila p) {
    tpalabra consultado;
    if (pila_vacia(p) == true) {
        strcpy(consultado.palabra, "ERROR_VACIA");
		consultado.longitud = 0;
        strcpy(consultado.definicion, "");
        strcpy(consultado.sinonimo, "");
    }
    else {
        consultado = p.datos[p.cima]; 
    }
    return consultado;
}
