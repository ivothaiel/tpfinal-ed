#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
// --- DEFINICION TDA PILA ---
struct tpalabra_simple { // estructura minima necesaria para la pila si no incluimos diccionario aun
    tcad palabra; 
    int longitud; 
    tcad definicion;
    tcad sinonimo;
};
// se usa tpalabra_simple aca para mantener orden

const int MAXPILA = 6;  
typedef tpalabra_simple tcontenedor[MAXPILA]; 

struct tpila {
    tcontenedor datos; 
    int cima;         
};

// --- IMPLEMENTACION TDA PILA ---
void iniciarpila(tpila &p) {
    p.cima = -1;
}
bool pilavacia(tpila p) {
    return p.cima == -1;
}
bool pilallena(tpila p) {
    return p.cima == MAXPILA - 1;
}
void agregarpila(tpila &p, tpalabra_simple nuevo) {
    if (pilallena(p) == true){ 
		cout << "ERROR: Pila llena." << endl; 
	}else{ 
		p.cima++; 
		p.datos[p.cima] = nuevo; 
	}
}


tpalabra_simple quitarpila(tpila &p) {
    tpalabra_simple extraido;
    if (pilavacia(p) == true){ 
		strcpy(extraido.palabra, "ERROR_VACIA"); 
	}else{ 
		extraido = p.datos[p.cima]; 
		p.cima--; 
	}
    return extraido;
}
