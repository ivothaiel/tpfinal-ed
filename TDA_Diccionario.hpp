#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;

// --- DEFINICION DE LA ESTRUCTURA PRINCIPAL (tpalabra) ---
// Arreglo que contiene los datos de la palabra
struct tpalabra { 
	tcad palabra; 
	int longitud; 
	tcad definicion;
	tcad sinonimo;
};

// Define el puntero al nodo de palabra
typedef struct tnodo_palabra *pnodo_palabra;

struct tnodo_palabra {
	    tpalabra dato;          // Datos de la palabra
	    pnodo_palabra ant;      // Puntero Anterior (Lista Doble)
	    pnodo_palabra sig;      // Puntero Siguiente
};

// Define la cabecera de cada lista del diccionario
struct tlista_palabras {
	    pnodo_palabra inicio;
	    pnodo_palabra fin;
};

const int MAX_CLAVES = 26; // Numero de claves (letras A-Z)

// Define la estructura del arreglo de diccionarios
struct tclave {
	    char clave;                  
		    tlista_palabras listado;    
};

// Define el tipo Diccionario (Arreglo Estatico de Listas)
typedef tclave tdiccionario[MAX_CLAVES];

// --- IMPLEMENTACION ---

// Inicializa los punteros de inicio y fin de una lista a NULL.
// Criterio: TDA Lista Doble (Inicializacion).
void iniciarlista_palabras(tlista_palabras &lis) {
	    lis.inicio = NULL;
	    lis.fin = NULL;
}

// Inicializa las 26 listas que conforman el diccionario.
// Criterio: TDA Diccionario (Creacion e Inicializacion).
void creardic(tdiccionario &dic) {
	    int i;
	    char letra = 'A';
	    for (i = 0; i < MAX_CLAVES; i++) {
		        dic[i].clave = letra;
		        iniciarlista_palabras(dic[i].listado); 
			        letra++; 
				    }
}

// Reserva memoria para un nuevo nodo de palabra y asigna datos.
// Criterio: TDA Lista (Crear Nodo).
void crearnodo_palabra(pnodo_palabra &nuevo, tpalabra datos) { 
	    nuevo = new tnodo_palabra;
    if (nuevo != NULL) { 
	        nuevo->dato = datos; 
		        nuevo->sig = NULL; 
			        nuevo->ant = NULL; 
				    }
    else
		        cout<<"\nMemoria Llena"<<endl; 
}

// Inserta el nuevo nodo en su posicion correcta dentro de la lista (orden alfabetico).
// Criterio: Lista Doble (Insercion Ordenada).
void insertar_ordenado_palabras(tlista_palabras &lis, pnodo_palabra nuevo) {
	    pnodo_palabra p;
	    if (lis.inicio == NULL) { // Caso 1: Lista Vacia
		        lis.inicio = nuevo; 
			        lis.fin = nuevo; 
				    } else if (strcmp(nuevo->dato.palabra, lis.inicio->dato.palabra) < 0) { // Caso 2: Nuevo es el primer elemento
					        nuevo->sig = lis.inicio; 
						        lis.inicio->ant = nuevo; 
							        lis.inicio = nuevo;
						    } else if (strcmp(nuevo->dato.palabra, lis.fin->dato.palabra) > 0) { // Caso 3: Nuevo es el ultimo elemento
							        lis.fin->sig = nuevo; 
								        nuevo->ant = lis.fin; 
									        lis.fin = nuevo;
								    } else { // Caso 4: Insercion en el medio
									        p = lis.inicio->sig;
								        while (strcmp(nuevo->dato.palabra, p->dato.palabra) > 0) { 
									            p = p->sig; 
										        }
								// Conexiones del nuevo nodo
								        nuevo->ant = p->ant; 
									        nuevo->sig = p;
								// Conexiones de los nodos adyacentes
								        p->ant->sig = nuevo; 
									        p->ant = nuevo;
								    }
}

// Obtiene el indice del arreglo del diccionario (0-25) a partir de la primera letra.
// Criterio: TDA Diccionario (Funcion de Mapeo).
int obtener_indice(tdiccionario dic, char clave){
	    int i = 0;
	    bool encontrado = false;
	// Se recorre el arreglo buscando la clave
	    while (i < MAX_CLAVES && encontrado == false) {
		        if (clave == dic[i].clave)
			            encontrado = true;
		        else
			            i++;
		    }
	    return i;
}
	
	// Wrapper para crear el nodo y agregarlo a la lista del indice correcto.
	// Criterio: TDA Diccionario (Insercion).
	void agregar_palabra(tdiccionario &dic, tpalabra datos) { 
		    pnodo_palabra nuevo;
	    int indice = obtener_indice(dic, datos.palabra[0]);
	    crearnodo_palabra(nuevo, datos); 
		    insertar_ordenado_palabras(dic[indice].listado, nuevo); 
	}
	
	// Busca una palabra especifica recorriendo solo la lista correspondiente a su letra.
	// Criterio: TDA Diccionario (Busqueda Optimizada).
	pnodo_palabra buscar_palabra_diccionario(tdiccionario &dic, tcad palabra_buscada) {
		    int indice = obtener_indice(dic, palabra_buscada[0]);
		    pnodo_palabra p;
		    
			    p = dic[indice].listado.inicio;
		    while (p != NULL && strcmp(p->dato.palabra, palabra_buscada) != 0) {
			        if (strcmp(p->dato.palabra, palabra_buscada) > 0) 
				            p = NULL; // Si el dato es mayor, no se encuentra (la lista esta ordenada)
			        else
				            p = p->sig; 
					    }
		    return p;
	}
	
	// Quita un nodo de la lista doble segun su valor (palabra) y reajusta los punteros.
	// Criterio: Lista Doble (Extraccion de Nodo Especifico).
	pnodo_palabra quitar_palabra(tlista_palabras &lista, tcad buscado){
		    pnodo_palabra extraido, i;
		// Caso 1: Quitar el inicio
		    if(strcmp(lista.inicio->dato.palabra, buscado) == 0){
			        if(lista.inicio == lista.fin){ // A) Unico nodo
				            extraido = lista.inicio;
				            lista.inicio = NULL;
				            lista.fin = NULL;
				        }else{ // B) Multiples nodos
				            extraido = lista.inicio;
				            lista.inicio = lista.inicio->sig;
				            lista.inicio->ant = NULL;
				            extraido->sig = NULL;
				        }
			    }else{
			// Caso 2: Quitar el final
			        if(strcmp(lista.fin->dato.palabra, buscado) == 0){
				            extraido = lista.fin;
				            lista.fin = lista.fin->ant;
				            lista.fin->sig = NULL;
				            extraido->ant = NULL;
				        }else{ // Caso 3: Quitar del medio
				            for(i = lista.inicio->sig; i != lista.fin && 
					                strcmp(i->dato.palabra, buscado) != 0; i = i->sig); // Buscar predecesor
				            extraido = i;
				            (i->ant)->sig = extraido->sig; // Predecesor apunta a Sucesor
				            (i->sig)->ant = extraido->ant; // Sucesor apunta a Predecesor
				            extraido->sig = NULL;
				            extraido->ant = NULL;
				        }
			    }
		    return extraido; // Devuelve el nodo desconectado
	}
		
		// Wrapper para encontrar el indice y llamar a la funcion de extraccion de la lista.
		// Criterio: TDA Diccionario (Eliminacion).
		pnodo_palabra eliminar_palabra(tdiccionario &dic, tcad buscado){
			    int indice = obtener_indice(dic, buscado[0]);
			    pnodo_palabra quitado = quitar_palabra(dic[indice].listado, buscado);
			    return quitado;
		}
			
			// Recorre y libera la memoria dinamica de una sola lista.
			// Criterio: Liberacion de Lista (Recorrido Iterativo).
			void liberar_lista_palabras(pnodo_palabra &lis) {
				    pnodo_palabra aux;
				    while (lis != NULL){ 
					        aux = lis; 
						        lis = lis->sig; 
							        delete aux;
						    }
			}
			
			// Recorre el arreglo principal y libera la memoria de cada una de las 26 listas.
			// Criterio: Liberacion del TDA Diccionario.
			void liberar_diccionario(tdiccionario &dic) {
				    for (int i = 0; i < MAX_CLAVES; i++) {
					        liberar_lista_palabras(dic[i].listado.inicio);
					        dic[i].listado.inicio = NULL; 
						        dic[i].listado.fin = NULL;
					    }
			}
			
			// Recorre todas las listas del diccionario para obtener el total de palabras almacenadas.
			// Criterio: TDA Diccionario (Contador de Elementos).
			int contar_palabras(tdiccionario dic) {
				    int contador = 0;
				    pnodo_palabra p;
				    for (int i = 0; i < MAX_CLAVES; i++) {
					        p = dic[i].listado.inicio;
					        while (p != NULL) {
						            contador++;
						            p = p->sig;
						        }
					    }
				    return contador;
			}
