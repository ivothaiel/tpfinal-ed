#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// --- DEFINICION TDA PILA ---
const int MAXPILA = 6;  
typedef tpalabra tcontenedor[MAXPILA]; 


struct tpila {
	    tcontenedor datos;  
	    int cima;           
};

// --- IMPLEMENTACION TDA PILA ---

// Inicializa la pila asignando un valor que indica que esta vacia.
void iniciarpila(tpila &p) {
	    p.cima = -1;
}

// Determina si la pila esta vacia, chequeando el indice de la cima.
bool pilavacia(tpila p) {
	    return p.cima == -1;
}

// Determina si la pila esta llena.
bool pilallena(tpila p) {
	    return p.cima == MAXPILA - 1;
}

// Agrega un nuevo elemento a la cima de la pila.
void agregarpila(tpila &p, tpalabra nuevo) {
	    if (pilallena(p) == true){ 
		        cout << "ERROR: Pila llena." << endl; 
			    }else{ 
				        p.cima++; 
					        p.datos[p.cima] = nuevo; 
						    }
}

// Extrae el elemento de la cima de la pila y reduce el indice.
tpalabra quitarpila(tpila &p) {
	    tpalabra extraido;
	    if (pilavacia(p) == true){ 
		        // Devuelve un valor arbitrario/de error si esta vacia
		        strcpy(extraido.palabra, "ERROR_VACIA"); 
			    }else{ 
				        extraido = p.datos[p.cima]; 
					        p.cima--; 
						    }
	    return extraido;
}
