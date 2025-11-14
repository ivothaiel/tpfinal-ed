#include "TDA_Base.hpp" 

typedef struct tnodo_jugador *pnodo_jugador;
struct tnodo_jugador {
    tjugador dato;        
    pnodo_jugador izq;   
    pnodo_jugador der;   
};


void iniciar(pnodo_jugador &arbol) {
    arbol = NULL;
}

void crearnodo(pnodo_jugador &nuevo, tjugador dato_jugador) {
    nuevo = new tnodo_jugador; 
    
    if (nuevo != NULL) {
        nuevo->dato = dato_jugador; 
        nuevo->izq = NULL;         
        nuevo->der = NULL;         
    }
}


void insertar(pnodo_jugador &arbol, pnodo_jugador nuevo) {
    if (arbol == NULL) {
        arbol = nuevo;
    }
    else {
        if (strcmp(nuevo->dato.alias, arbol->dato.alias) < 0) {
            insertar(arbol->izq, nuevo);
        }
        else {
            insertar(arbol->der, nuevo);
        }
    }
}


pnodo_jugador buscar(pnodo_jugador arbol, tcad alias_buscado) {
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
                return buscar(arbol->izq, alias_buscado);
            }
            else {
                return buscar(arbol->der, alias_buscado);
            }
        }
    }
}


void listar(pnodo_jugador arbol) {
    if (arbol != NULL) {
        listar(arbol->izq);
        cout << "----------------------------------------" << endl;
        cout << "Alias: " << arbol->dato.alias << endl;
        cout << "Nombre: " << arbol->dato.nombre << " " << arbol->dato.apellido << endl;
        cout << "Signo: " << arbol->dato.signo << endl;
        cout << "Puntaje Max: " << arbol->dato.mejor_puntaje << endl;
        cout << "Puntaje Acum: " << arbol->dato.puntaje_acumulado << endl;
        cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;

        listar(arbol->der);
    }
}
void liberar(pnodo_jugador &arbol) {
    if (arbol != NULL) {
        liberar(arbol->izq);
        liberar(arbol->der);
        delete arbol; 
        arbol = NULL; 
    }
}