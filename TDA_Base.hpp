
#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  
#include <time.h> 

using namespace std;

const int MAX = 50; 
typedef char tcad[MAX];

// Definicion de la estructura ABB para los jugadores
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

// Definicion de la estructura de diccionario para las palabras magicas
struct tpalabra {
    tcad palabra; 
	int longitud; 
    tcad definicion;
    tcad sinonimo;
};

typedef struct tnodo_palabra *pnodo_palabra;

struct tnodo_palabra {
    tpalabra dato;          
    pnodo_palabra ant;     
    pnodo_palabra sig;     
};

struct tlista_palabras {
    pnodo_palabra inicio;
    pnodo_palabra fin;
};

const int MAX_CLAVES = 26; 

struct tclave {
    char clave;                 
    tlista_palabras listado;    
};

typedef tclave tdiccionario[MAX_CLAVES];

// Definicion de la estructura de lista doble para el ranking de jugadores
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

const int MAXPILA = 6;  

typedef tpalabra tcontenedor[MAXPILA]; 

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
void agregarpila(tpila &p, tpalabra nuevo) {
    if (pilallena(p) == true) { cout << "ERROR: Pila llena." << endl; }
    else { p.cima++; p.datos[p.cima] = nuevo; }
}
tpalabra quitarpila(tpila &p) {
    tpalabra extraido;
    if (pilavacia(p) == true) { strcpy(extraido.palabra, "ERROR_VACIA"); }
    else { extraido = p.datos[p.cima]; p.cima--; }
    return extraido;
}
tpalabra topepila(tpila p) {
    tpalabra consultado;
    if (pilavacia(p) == true) { strcpy(consultado.palabra, "ERROR_VACIA"); }
    else { consultado = p.datos[p.cima]; }
    return consultado;
}


//-------------------------------------
// --- IMPLEMENTACION TDA RANKING -----
//-------------------------------------
void iniciarlista(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}

void crearnodo_ranking(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking; 
    if (nuevo != NULL) { 
        nuevo->dato = dato_ranking; 
        nuevo->ant = NULL; 
        nuevo->sig = NULL;
    }
}

//Inserta un nuevo jugador en la lista de ranking, manteniéndola ordenada de mayor a menor puntaje.
void insertarordenado_ranking(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {
    if (nuevo->dato.puntaje >= actual->dato.puntaje) {
        nuevo->ant = actual->ant; 
        nuevo->sig = actual;
        actual->ant->sig = nuevo; 
        actual->ant = nuevo;
    }
    else if (actual->sig == inicio_lista) {
        nuevo->ant = actual; 
        nuevo->sig = inicio_lista;
        actual->sig = nuevo; 
        inicio_lista->ant = nuevo;
    }else{ 
        insertarordenado_ranking(actual->sig, nuevo, inicio_lista);
    }
}


/*
agrega un nuevo jugador al ranking de forma ordenada y, 
se asegura de que el puntero lista.inicio siempre 
apunte al jugador con el puntaje más alto.
*/
void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {
    if (lista.inicio == NULL) {
        lista.inicio = nuevo; 
        lista.inicio->sig = lista.inicio; 
        lista.inicio->ant = lista.inicio;
    } else {
        insertarordenado_ranking(lista.inicio, nuevo, lista.inicio); 
        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje){ 
            lista.inicio = nuevo;
        }
    }
    lista.cont++;
}


//Esta función recorre y muestra la lista circular de vencedores.
void mostrarlista(tlista_ranking lista, bool creciente) {
    pnodo_ranking i;
    if (lista.inicio == NULL) { cout << "  No hay vencedores para mostrar." << endl; }
    else {
        if (creciente) {
            i = lista.inicio->ant;
            do {
                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->ant; 
            } while (i != lista.inicio->ant); 
        } else {
            i = lista.inicio;
            do {
                cout << "  - Alias: " << i->dato.alias << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->sig; 
            } while (i != lista.inicio); 
        }
    }
}

//ibera toda la memoria de la lista del ranking, es la "limpieza" que se hace después de mostrar los vencedores.
void liberarlista(tlista_ranking &lista) {
    pnodo_ranking p, aux;
    if (lista.inicio != NULL) {
        p = lista.inicio; 
        lista.inicio->ant->sig = NULL; 
        while (p != NULL){ 
            aux = p; 
            p = p->sig; 
            delete aux;
        }
        iniciarlista(lista);
    }
}


//-------------------------------------
// --- IMPLEMENTACION TDA JUGADOR -----
//-------------------------------------
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

// Busca un jugador en el arbol de jugadores de acuerdo al alias enviado
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

// Lista todos los jugadores (recorrido EN-ORDEN) del arbol
void listar_jugadores(pjugador arbol) {
    if (arbol != NULL) {
        listar_jugadores(arbol->izq);
        cout << "-----------------------------" << endl;
		cout << "Alias: " << arbol->dato.alias << endl;
		cout << "Nombre: " << arbol->dato.nombre << " " 
			<< arbol->dato.apellido << endl;
		cout << "Signo: " << arbol->dato.signo << endl;
		cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
		cout << "Mejor Puntaje: " << arbol->dato.mejor_puntaje << endl;
		cout << "Puntaje Acumulado: " << arbol->dato.puntaje_acumulado << endl;
        listar_jugadores(arbol->der);
    }
}



// Cuenta la cantidad de jugadores que tiene el arbol
int contar_jugadores(pjugador arbol) {
    if (arbol == NULL) { 
		return 0; 
	}
    return 1 + contar_jugadores(arbol->izq) + contar_jugadores(arbol->der);
}



//intercambia los datos entre dos jugadores.
void cambio(tjugador &a, tjugador &b){
	tjugador aux = a;
	a = b;
	b = aux;
}


//borrar un nodo que tiene 2 hijos
//Baja por la rama izquierda del subárbol derecho
//busca al menor de los mayores
//una vez que lo encuentra, intercambia sus datos con el nodo que quiere borrar
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

// Elimina un jugador del arbol
// Se aplica criterio menor de mayores si es necesario
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


//-------------------------------------
// -- IMPLEMENTACION TDA DICCIONARIO --
//-------------------------------------
void iniciarlista_palabras(tlista_palabras &lis) {
    lis.inicio = NULL;
    lis.fin = NULL;
}

void creardic(tdiccionario &dic) {
    int i;
    char letra = 'A';
    for (i = 0; i < MAX_CLAVES; i++) {
        dic[i].clave = letra;
        iniciarlista_palabras(dic[i].listado); 
        letra++; 
    }
}

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

//inserta una nueva palabra en el diccionario (que es una lista doble) de forma ordenada alfabéticamente.
void insertar_ordenado_palabras(tlista_palabras &lis, pnodo_palabra nuevo) {
    pnodo_palabra p;
    if (lis.inicio == NULL) { 
		lis.inicio = nuevo; 
		lis.fin = nuevo; 
	} else if (strcmp(nuevo->dato.palabra, lis.inicio->dato.palabra) < 0) { 
        nuevo->sig = lis.inicio; 
		lis.inicio->ant = nuevo; 
		lis.inicio = nuevo;
    } else if (strcmp(nuevo->dato.palabra, lis.fin->dato.palabra) > 0) { 
        lis.fin->sig = nuevo; 
		nuevo->ant = lis.fin; 
		lis.fin = nuevo;
    } else { 
        p = lis.inicio->sig;
        while (strcmp(nuevo->dato.palabra, p->dato.palabra) > 0) { 
			p = p->sig; 
		}
        nuevo->ant = p->ant; 
		nuevo->sig = p;
        p->ant->sig = nuevo; 
		p->ant = nuevo;
    }
}

// Obtiene el indice del diccionario
int obtener_indice(tdiccionario dic, char clave){
	int i = 0;
	bool encontrado = false;
	while (i < MAX_CLAVES && encontrado == false) {
		if (clave == dic[i].clave)
			encontrado = true;
		else
			i++;
	}
	return i;
}


/*
agrega una nueva palabra al diccionario, 
encontrando primero la letra correcta (indice) 
y luego llamando a la función insertar_ordenado_palabras 
para que la ponga en su lista.
*/
void agregar_palabra(tdiccionario &dic, tpalabra datos) { 
    pnodo_palabra nuevo;
	// Si se controla que 'datos' solo contenga letras no hace falta un
	// booleano para saber si se encontr� el indice
	int indice = obtener_indice(dic, datos.palabra[0]);
    crearnodo_palabra(nuevo, datos); 
	insertar_ordenado_palabras(dic[indice].listado, nuevo); 
}



//busca una palabra en el diccionario, devuelve un puntero al nodo de la palabra si la encuentra, o NULL si no la encuentra
pnodo_palabra buscar_palabra_diccionario(tdiccionario &dic, tcad palabra_buscada) {
    int indice = obtener_indice(dic, palabra_buscada[0]);
    pnodo_palabra p;
	
    p = dic[indice].listado.inicio;
    while (p != NULL && strcmp(p->dato.palabra, palabra_buscada) != 0) {
        if (strcmp(p->dato.palabra, palabra_buscada) > 0) 
			p = NULL; 
        else
			p = p->sig; 
	}
    
    return p;
}

/*
bool quitar_de_lista(tlista_palabras &lis, pnodo_palabra &nodo_a_quitar) {
    if (nodo_a_quitar == NULL) 
		return false;
    if (nodo_a_quitar == lis.inicio && nodo_a_quitar == lis.fin) { 
		lis.inicio = NULL; 
		lis.fin = NULL; 
	} else if (nodo_a_quitar == lis.inicio) { 
		lis.inicio = nodo_a_quitar->sig; 
		lis.inicio->ant = NULL; 
	} else if (nodo_a_quitar == lis.fin) { 
		lis.fin = nodo_a_quitar->ant; 
		lis.fin->sig = NULL; 
	} else {
        nodo_a_quitar->ant->sig = nodo_a_quitar->sig;
        nodo_a_quitar->sig->ant = nodo_a_quitar->ant;
    }
    delete nodo_a_quitar;
    return true;
}



/**
 * primero, encuentra la lista correcta (basandose en la primera letra). 
 * luego, llama a buscar_palabra_diccionario para encontrar el nodo exacto 
 * finalmente, pasa ese nodo a quitar_de_lista para que lo borre
 */
 /*
bool quitar_palabra(tdiccionario &dic, tcad palabra_buscada) {
    int i = 0;
    bool encontrado = false;
    while (i < MAX_CLAVES && encontrado == false) {
        if (palabra_buscada[0] == dic[i].clave)
            encontrado = true;
        else
            i++;
    }
    if (!encontrado) return false; 
    pnodo_palabra nodo = buscar_palabra_diccionario(dic, palabra_buscada);
    return quitar_de_lista(dic[i].listado, nodo);
}*/

pnodo_palabra quitar_palabra(tlista_palabras &lista, tcad buscado){
	pnodo_palabra extraido, i;
	if(strcmp(lista.inicio->dato.palabra, buscado) == 0){
		if(lista.inicio == lista.fin){
			extraido = lista.inicio;
			lista.inicio = NULL;
			lista.fin = NULL;
		}else{
			extraido = lista.inicio;
			lista.inicio = lista.inicio->sig;
			lista.inicio->ant = NULL;
			extraido->sig = NULL;
		}
	}else{
		if(strcmp(lista.fin->dato.palabra, buscado) == 0){
			extraido = lista.fin;
			lista.fin = lista.fin->ant;
			lista.fin->sig = NULL;
			extraido->ant = NULL;
		}else{
			for(i = lista.inicio->sig; i != lista.fin && 
				strcmp(i->dato.palabra, buscado) != 0; i = i->sig);
			extraido = i;
			(i->ant)->sig = extraido->sig;
			(i->sig)->ant = extraido->ant;
			extraido->sig = NULL;
			extraido->ant = NULL;
		}
	}
	return extraido;
}

pnodo_palabra eliminar_palabra(tdiccionario &dic, tcad buscado){
	int indice = obtener_indice(dic, buscado[0]);
	pnodo_palabra quitado = quitar_palabra(dic[indice].listado, buscado);
	return quitado;
}

//Libera toda la memoria de una sola lista enlazada
void liberar_lista_palabras(pnodo_palabra &lis) {
    pnodo_palabra aux;
    while (lis != NULL){ 
        aux = lis; 
        lis = lis->sig; 
        delete aux;
    }
}


//Libera toda la memoria de CADA UNA DE LAS 26 LISTAS que forman el diccionario
void liberar_diccionario(tdiccionario &dic) {
    for (int i = 0; i < MAX_CLAVES; i++) {
        liberar_lista_palabras(dic[i].listado.inicio);
        dic[i].listado.inicio = NULL; 
        dic[i].listado.fin = NULL;
    }
}

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

//-----------------------------
//--- FUNCIONES DE UTILIDAD ---
//-----------------------------

void limpiarPantalla() {
    system("cls"); 
}


//pausa la ejecucion del programa hasta que el usuario presione la tecla Enter
void pausarPantalla() {
    cout << "\nPresione Enter para continuar...";
    int c;
    while ((c = getchar()) != '\n');
    getchar(); 
}



/*
pide al usuario que ingrese una cadena de texto y 
se asegura de que esa cadena tenga un largo mínimo antes de aceptarla
si la cadena es muy corta, sigue pidiendo hasta que sea válida.
*/
void leerCadenaValidada(const char* mensaje, tcad &cadena, int minLen) {
    bool valido = false;
    while (!valido) {
        cout << mensaje;
		
        fgets(cadena, MAX, stdin); 
        int len = strlen(cadena);
		
        if (len > 0 && cadena[len - 1] == '\n')
            cadena[len - 1] = '\0'; 
        
        if ((int)strlen(cadena) >= minLen)
            valido = true;
        else
			cout << "Invalido: La cadena debe tener al menos " << minLen << " caracteres" << endl;
    }
}
