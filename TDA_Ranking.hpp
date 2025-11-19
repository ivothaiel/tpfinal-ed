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

// Inicializa la lista del ranking a NULL.
// Criterio: Lista Doble Circular.
void iniciarlista(tlista_ranking &lista) {
	    lista.inicio = NULL;
	    lista.cont = 0;
}

// Crea un nuevo nodo de la lista e inicializa sus punteros a NULL.
// Criterio: TDA Lista (Crear Nodo).
void crearnodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
	    nuevo = new tnodo_ranking; 
		    if (nuevo != NULL) { 
			        nuevo->dato = dato_ranking; 
				        nuevo->ant = NULL; 
					        nuevo->sig = NULL;
				    }
}

// Inserta recursivamente el nuevo nodo en su posición ordenada (de mayor a menor puntaje).
// Criterio: Lista Doble Circular, Inserción Ordenada Recursiva.
void insertarordenado_ranking(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {
	    // Caso 1: Insertar antes del nodo actual (si el nuevo es mayor o igual)
		    if (nuevo->dato.puntaje >= actual->dato.puntaje) {
			        nuevo->ant = actual->ant; 
				        nuevo->sig = actual;
			        actual->ant->sig = nuevo; 
				        actual->ant = nuevo;
			    }
		// Caso 2: Insertar al final de la lista (el actual es el último, apuntando al inicio)
		    else if (actual->sig == inicio_lista) {
			        nuevo->ant = actual; 
				        nuevo->sig = inicio_lista;
			        actual->sig = nuevo; 
				        inicio_lista->ant = nuevo;
			    }else{ 
				// Caso 3: Llamada recursiva al siguiente nodo
				        insertarordenado_ranking(actual->sig, nuevo, inicio_lista);
			    }
}

// Agrega el nodo a la lista, maneja el caso de lista vacía y actualiza el puntero de inicio.
// Criterio: Lista Doble Circular.
void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {
	    // Caso 1: Lista vacía (el nodo apunta a sí mismo)
		    if (lista.inicio == NULL) {
			        lista.inicio = nuevo; 
				        lista.inicio->sig = lista.inicio; 
					        lista.inicio->ant = lista.inicio;
				    } else {
			        // Inserta ordenado y luego verifica si el nuevo nodo es el nuevo inicio
				        insertarordenado_ranking(lista.inicio, nuevo, lista.inicio); 
					        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje){ 
						            lista.inicio = nuevo;
					        }
					    }
		    lista.cont++;
}

// Muestra el contenido de la lista en orden creciente o decreciente.
// Criterio: Recorrido de Lista Circular Doble (por punteros ant o sig).
void mostrarlista(tlista_ranking lista, bool creciente) {
	    pnodo_ranking i;
	    if (lista.inicio == NULL) { cout << "  No hay vencedores para mostrar." << endl; }
	    else {
		        if (creciente) {
			            // Recorrido Creciente: Empezar desde el final (inicio->ant) e ir hacia 'ant'
				            i = lista.inicio->ant;
			            do {
				                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
				                i = i->ant; 
					            } while (i != lista.inicio->ant); 
						        } else {
			            // Recorrido Decreciente: Empezar desde el inicio e ir hacia 'sig'
				            i = lista.inicio;
			            do {
				                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
				                i = i->sig; 
					            } while (i != lista.inicio); 
						        }
		    }
}

// Libera toda la memoria dinámica de la lista. Rompe el ciclo antes de la iteración.
// Criterio: Liberación de Lista Dinámica.
void liberarlista(tlista_ranking &lista) {
	    pnodo_ranking p, aux;
	    if (lista.inicio != NULL) {
		        p = lista.inicio; 
			// Romper la circularidad para usar el bucle while(p != NULL)
			        lista.inicio->ant->sig = NULL; 
				        while (p != NULL){ 
					            aux = p; 
						            p = p->sig; 
							            delete aux;
						        }
				        iniciarlista(lista);
				    }
}
