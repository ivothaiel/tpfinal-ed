#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// --- DEFINICION ---
struct tinfo_ranking {
    tcad alias;
    int puntaje;
};

typedef struct tnodo_ranking *pnodo_ranking;

struct tnodo_ranking {
    tinfo_ranking dato;
    pnodo_ranking ant;
    pnodo_ranking sig;
};

struct tlista_ranking {
    pnodo_ranking inicio;
    int cont;
};

// --- IMPLEMENTACION ---

// Inicializa la lista del ranking.
void iniciarlista(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}

// Crea un nuevo nodo.
void crearnodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking;
    if (nuevo != NULL) {
        nuevo->dato = dato_ranking;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
}

// Inserta un nodo de forma ordenada (de mayor a menor puntaje).
void insertarordenado_ranking(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {

    // Caso 1: insertar antes del actual
    if (nuevo->dato.puntaje >= actual->dato.puntaje) {
        nuevo->ant = actual->ant;
        nuevo->sig = actual;
        actual->ant->sig = nuevo;
        actual->ant = nuevo;
    }
    // Caso 2: insertar al final (actual->sig vuelve al inicio)
    else if (actual->sig == inicio_lista) {
        nuevo->ant = actual;
        nuevo->sig = inicio_lista;
        actual->sig = nuevo;
        inicio_lista->ant = nuevo;
    }
    else {
        // Caso 3: avanzar recursivamente
        insertarordenado_ranking(actual->sig, nuevo, inicio_lista);
    }
}

// Controla el caso de lista vacía y define nuevo inicio si corresponde.
void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {

    // Caso 1: lista vacía
    if (lista.inicio == NULL) {
        lista.inicio = nuevo;
        lista.inicio->sig = lista.inicio;
        lista.inicio->ant = lista.inicio;
    }
    else {
        // Insertar ordenadamente
        insertarordenado_ranking(lista.inicio, nuevo, lista.inicio);
		
        // Si es el mayor puntaje, actualizar inicio
        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje) {
            lista.inicio = nuevo;
        }
    }

    lista.cont++;
}

// Funcion auxiliar para formatear un numero con espacios
void mostrar_numero(int num, int ancho) {
	int digitos = 0;
	int temp = num;
	if (temp == 0) digitos = 1;
	else {
		while (temp > 0) {
			digitos++;
			temp = temp / 10;
		}
	}
	cout << num;
	for (int i = digitos; i < ancho; i++) {
		cout << " ";
	}
}

// Funcion auxiliar para formatear una cadena con espacios
void mostrar_cadena_formato(tcad cad, int ancho) {
	int len = strlen(cad);
	cout << cad;
	for (int i = len; i < ancho; i++) {
		cout << " ";
	}
}

// Recorre la lista circular en orden creciente o decreciente.
void mostrarlista(tlista_ranking lista, bool creciente) {
    pnodo_ranking i;
	int posicion = 1;

    if (lista.inicio == NULL) {
        cout << "No hay vencedores para mostrar." << endl;
    }
    else {
		// Mostrar encabezado de la tabla
		cout << "\n";
		cout << "+-------+--------------------------------------+------------+" << endl;
		cout << "| Pos.  | Alias                                | Puntaje    |" << endl;
		cout << "+-------+--------------------------------------+------------+" << endl;
		
        if (creciente) {
            // Desde el final hacia atras (menor a mayor)
            i = lista.inicio->ant;
			posicion = lista.cont; // Empezar desde la ultima posicion
			
            do {
                cout << "| ";
				mostrar_numero(posicion, 5);
				cout << " | ";
				mostrar_cadena_formato(i->dato.alias, 36);
				cout << " | ";
				mostrar_numero(i->dato.puntaje, 10);
				cout << " |" << endl;
                i = i->ant;
				posicion--;
            } while (i != lista.inicio->ant);
        }
        else {
            // Desde el inicio hacia adelante (mayor a menor)
            i = lista.inicio;
			posicion = 1;
			
            do {
                cout << "| ";
				mostrar_numero(posicion, 5);
				cout << " | ";
				mostrar_cadena_formato(i->dato.alias, 36);
				cout << " | ";
				mostrar_numero(i->dato.puntaje, 10);
				cout << " |" << endl;
                i = i->sig;
				posicion++;
            } while (i != lista.inicio);
        }
		
		// Cerrar la tabla
		cout << "+-------+--------------------------------------+------------+" << endl;
		cout << "\nTotal de vencedores: " << lista.cont << endl;
    }
}

// Libera toda la memoria dinámica de la lista.
void liberarlista(tlista_ranking &lista) {
    pnodo_ranking p, aux;

    if (lista.inicio != NULL) {
        p = lista.inicio;
		
        // Rompe la circularidad para liberar con while normal
        lista.inicio->ant->sig = NULL;
		
        while (p != NULL) {
            aux = p;
            p = p->sig;
            delete aux;
        }
		
        iniciarlista(lista);
    }
}
