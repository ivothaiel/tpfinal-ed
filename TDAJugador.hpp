
#include <iostream>

#include "modulos.hpp" 
#include "TDA_Base.hpp"

typedef char tcad[30];

typedef struct tnodo_jugador *pjugador;

typedef struct tnodo_jugador {
    tjugador dato;       
    pjugador izq;   
    pjugador der;   
};

// Inicializa el arbol de jugadores
void iniciar(pjugador &arbol) {
    arbol = NULL;
}

// Crea un nuevo puntero jugador
void crear_jugador(pjugador &nuevo, tjugador dato_jugador) {
    nuevo = new tnodo_jugador; 
    if (nuevo != NULL) {
        nuevo->dato = dato_jugador; 
        nuevo->izq = NULL;         
        nuevo->der = NULL;         
    }
}

// Agrega un nuevo jugador al arbol de jugadores
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

// Retorna un jugador de acuerdo a un alias enviado
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

// Determina la existencia de un alias en la lista de jugadores
bool buscar_alias(pjugador arbol, tcad alias){
	bool encontrado = false;
	if(arbol != NULL){
		int comparacion = strcmp(alias, arbol->dato.alias);
		if(comparacion == 0)
			encontrado = true;
		else if(comparacion < 0){
			encontrado = buscar_alias(arbol->izq, alias);
		}else{
			encontrado = buscar_alias(arbol->der, alias);
		}
	}
	return encontrado;
}

// Muestra el listado de jugadores en recorrido PRE-ORDEN (ordenado)
	/*
void listar_jugadores(pjugador arbol) {
    if (arbol != NULL) {
        listar_jugadores(arbol->izq);
        cout << "----------------------------------------" << endl;
        mostrar_jugador(arbol);
        listar_jugadores(arbol->der);
    }
}*/

int contar_jugadores(pjugador arbol) {
	if (arbol == NULL) {
		return 0;
	}
	return 1 + contar_jugadores(arbol->izq) + contar_jugadores(arbol->der);
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

