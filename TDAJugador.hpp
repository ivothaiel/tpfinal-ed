#ifndef TDAJUGADOR_HPP
#define TDAJUGADOR_HPP

#include "TDA_Base.hpp" 

typedef struct tnodo_jugador *pjugador;
struct tnodo_jugador {
    tjugador dato;       
    pjugador izq;   
    pjugador der;   
};

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
        if (strcmp(nuevo->dato.alias, arbol->dato.alias) == 0) {
            cout << "ERROR: El alias '" << nuevo->dato.alias << "' ya existe." << endl;
            delete nuevo; 
        }
        else if (strcmp(nuevo->dato.alias, arbol->dato.alias) < 0) {
            insertar_jugador(arbol->izq, nuevo);
        }
        else {
            insertar_jugador(arbol->der, nuevo);
        }
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
        cout << "----------------------------------------" << endl;
        cout << "Alias: " << arbol->dato.alias << endl;
        cout << "Nombre: " << arbol->dato.nombre << " " << arbol->dato.apellido << endl;
        cout << "Signo: " << arbol->dato.signo << endl;
        cout << "Puntaje Max: " << arbol->dato.mejor_puntaje << endl;
        cout << "Puntaje Acum: " << arbol->dato.puntaje_acumulado << endl;
        cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
        listar_jugadores(arbol->der);
    }
}

pjugador menor_mayores(pjugador &nodo_derecho) {
    pjugador aux;
    if (nodo_derecho->izq != NULL) {
        aux = menor_mayores(nodo_derecho->izq);
    } else {
        aux = nodo_derecho;
        nodo_derecho = nodo_derecho->der;
    }
    return aux;
}

void eliminar_nodo_jugador(pjugador &arbol, tcad alias_buscado) {
    pjugador aux;

    if (arbol == NULL) {
        cout << "Alias no encontrado." << endl;
        return;
    }

    int comparacion = strcmp(alias_buscado, arbol->dato.alias);

    if (comparacion < 0) { 
        eliminar_nodo_jugador(arbol->izq, alias_buscado);
    } 
    else if (comparacion > 0) { 
        eliminar_nodo_jugador(arbol->der, alias_buscado);
    } 
    else { 
        if (arbol->izq == NULL && arbol->der == NULL) {
            aux = arbol;
            arbol = NULL;
            delete aux;
            cout << "Jugador eliminado (hoja)." << endl;
        }
        else if (arbol->izq == NULL) {
            aux = arbol;
            arbol = arbol->der;
            delete aux;
            cout << "Jugador eliminado (1 hijo der)." << endl;
        } 
        else if (arbol->der == NULL) {
            aux = arbol;
            arbol = arbol->izq;
            delete aux;
            cout << "Jugador eliminado (1 hijo izq)." << endl;
        }
        else {
            aux = menor_mayores(arbol->der);
            arbol->dato = aux->dato; 
            delete aux; 
            cout << "Jugador eliminado (2 hijos)." << endl;
        }
    }
}

void liberar(pjugador &arbol) {
    if (arbol != NULL) {
        liberar(arbol->izq); 
        liberar(arbol->der);
        delete arbol; 
        arbol = NULL; 
    }
}

#endif 