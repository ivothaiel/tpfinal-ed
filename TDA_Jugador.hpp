#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// --- DEFINICION ---
struct tjugador {
    tcad nombre;
    tcad apellido;
    tcad signo;
    tcad alias; 
    int juegos_ganados;
    int mejor_puntaje;
    int puntaje_acumulado;
};

typedef struct tnodo_jugador *pjugador;

struct tnodo_jugador {
    tjugador dato;       
    pjugador izq;   
    pjugador der;   
};

// --- IMPLEMENTACION ---
void iniciar(pjugador &arbol) {
    arbol = NULL;
}

void crear_jugador(pjugador &nuevo, tjugador dato_jugador) {
    nuevo = new tnodo_jugador; 
    if (nuevo != NULL) { 
        nuevo->dato = dato_jugador; 
        nuevo->izq = NULL; 
        nuevo->der = NULL; 
    }
}

void insertar_jugador(pjugador &arbol, pjugador nuevo) {
    if (arbol == NULL) {
        arbol = nuevo;
    }
    else {
        if (strcmp(nuevo->dato.alias, arbol->dato.alias) < 0)
            insertar_jugador(arbol->izq, nuevo);
        else
            insertar_jugador(arbol->der, nuevo);
    }
}

pjugador buscar_jugador(pjugador arbol, tcad alias_buscado) {
    if (arbol == NULL) { 
        return NULL; 
    }
    else {
        int comparacion = strcmp(alias_buscado, arbol->dato.alias);
        if (comparacion == 0) { 
            return arbol; 
        }
        else if (comparacion < 0) { 
            return buscar_jugador(arbol->izq, alias_buscado); 
        }
        else { 
            return buscar_jugador(arbol->der, alias_buscado); 
        }
    }
}

void listar_jugadores(pjugador arbol) {
    if (arbol != NULL) {
        listar_jugadores(arbol->izq);
        cout << "-----------------------------" << endl;
        cout << "Alias: " << arbol->dato.alias << endl;
        cout << "Nombre: " << arbol->dato.nombre <<endl; 
		cout << "Apellido: " << arbol->dato.apellido << endl;
        cout << "Signo: " << arbol->dato.signo << endl;
        cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
        cout << "Mejor Puntaje: " << arbol->dato.mejor_puntaje << endl;
        cout << "Puntaje Acumulado: " << arbol->dato.puntaje_acumulado << endl;
        listar_jugadores(arbol->der);
    }
}

int contar_jugadores(pjugador arbol) {
    if (arbol == NULL) { 
        return 0; 
    }
    return 1 + contar_jugadores(arbol->izq) + contar_jugadores(arbol->der);
}

void cambio(tjugador &a, tjugador &b){
    tjugador aux = a;
    a = b;
    b = aux;
}

pjugador menor_mayores(pjugador elegido, pjugador &menor) {
    pjugador aux;
    if (menor->izq != NULL) { 
        aux = menor_mayores(elegido, menor->izq); 
    } 
    else { 
        cambio(elegido->dato, menor->dato);
        aux = menor; 
        menor = menor->der; 
    }
    return aux;
}

pjugador eliminar_jugador(pjugador &arbol, tcad alias_buscado) {
    pjugador aux;
    if (arbol == NULL) { 
        aux = NULL; 
    }else{
        int comparacion = strcmp(alias_buscado, arbol->dato.alias);
        if (comparacion < 0) { 
            aux = eliminar_jugador(arbol->izq, alias_buscado); 
        } 
        else if (comparacion > 0) { 
            aux = eliminar_jugador(arbol->der, alias_buscado); 
        } 
        else {
            aux = arbol;
            if (arbol->izq == NULL && arbol->der == NULL) { 
                arbol = NULL; 
            }
            else if (arbol->izq == NULL) { 
                arbol = arbol->der;
            } 
            else if (arbol->der == NULL) { 
                arbol = arbol->izq;
            }
            else {
                aux = menor_mayores(arbol, arbol->der);
            }
        }
    }
    return aux;
}

void liberar(pjugador &arbol) {
    if (arbol != NULL) {
        liberar(arbol->izq); 
        liberar(arbol->der);
        delete arbol; 
        arbol = NULL; 
    }
}
