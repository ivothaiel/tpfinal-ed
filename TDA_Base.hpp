#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  

using namespace std;

const int MAX = 50; 
typedef char tcad[MAX];

typedef struct tjugador {
    tcad nombre;
    tcad apellido;
    tcad signo;
    tcad alias; 
    int juegos_ganados;
    int mejor_puntaje;
    int puntaje_acumulado;
};

typedef struct tpalabra {
    tcad palabra; 
	int longitud; 
    tcad definicion;
    tcad sinonimo;
};

struct tinfo_ranking {
    tcad alias;
    int puntaje; 
};


//implementacion tda jugador
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

void eliminarjugador(pjugador &arbol, tcad alias_buscado) {
    pjugador aux;

    if (arbol == NULL) {
        cout << "Alias no encontrado." << endl;
        return;
    }

    int comparacion = strcmp(alias_buscado, arbol->dato.alias);

    if (comparacion < 0) { 
        eliminarjugador(arbol->izq, alias_buscado);
    } 
    else if (comparacion > 0) { 
        eliminarjugador(arbol->der, alias_buscado);
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

//----------------------------------------------------------------------

//implementacion tda diccionario
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



void iniciarlista(tlista_palabras &lis) {
    lis.inicio = NULL;
    lis.fin = NULL;
}

void creardic(tdiccionario &dic) {
    int i;
    char letra = 'A';
    for (i = 0; i < MAX_CLAVES; i++) {
        dic[i].clave = letra;
        iniciarlista(dic[i].listado);
        letra++; 
    }
}

void crearnodo(pnodo_palabra &nuevo, tpalabra datos) { 
    nuevo = new tnodo_palabra;
    if (nuevo != NULL) {
        nuevo->dato = datos;
        nuevo->sig = NULL;
        nuevo->ant = NULL;
    }
    else
       cout<<"Memoria llena"<<endl;
}

void insertarordenado(tlista_palabras &lis, pnodo_palabra nuevo) {
    pnodo_palabra p;

    if (lis.inicio == NULL) { 
        lis.inicio = nuevo;
        lis.fin = nuevo;
    }
    else if (strcmp(nuevo->dato.palabra, lis.inicio->dato.palabra) < 0) { 
        nuevo->sig = lis.inicio;
        lis.inicio->ant = nuevo;
        lis.inicio = nuevo;
    }
    else if (strcmp(nuevo->dato.palabra, lis.fin->dato.palabra) > 0) { 
        lis.fin->sig = nuevo;
        nuevo->ant = lis.fin;
        lis.fin = nuevo;
    }
    else { 
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

void agregar_palabra(tdiccionario &dic, tpalabra datos) { 
    int i;
    bool encontrado = false;
    pnodo_palabra nuevo;

    i = 0;
    while (i < MAX_CLAVES && encontrado == false) {
        if (datos.palabra[0] == dic[i].clave)
            encontrado = true;
        else
            i++;
    }

    if (encontrado) {
        crearnodo(nuevo, datos); 
        insertarordenado(dic[i].listado, nuevo);
    }
    else {
        cout << "Palabra '" << datos.palabra << "' es incorrecta (no empieza con A-Z)." << endl;
    }
}

pnodo_palabra buscar_palabra_diccionario(tdiccionario &dic, tcad palabra_buscada) {
    int i = 0;
    bool encontrado = false;
    pnodo_palabra p = NULL;
    while (i < MAX_CLAVES && encontrado == false) {
        if (palabra_buscada[0] == dic[i].clave)
            encontrado = true;
        else
            i++;
    }
    if (encontrado) {
        p = dic[i].listado.inicio;
        while (p != NULL && strcmp(p->dato.palabra, palabra_buscada) != 0) {
            if (strcmp(p->dato.palabra, palabra_buscada) > 0) {
                p = NULL; 
            } else {
                p = p->sig; 
            }
        }
    }
    return p;
}


bool quitar_de_lista(tlista_palabras &lis, pnodo_palabra &nodo_a_quitar) {
    if (nodo_a_quitar == NULL) return false;
    if (nodo_a_quitar == lis.inicio && nodo_a_quitar == lis.fin) {
        lis.inicio = NULL;
        lis.fin = NULL;
    }
    else if (nodo_a_quitar == lis.inicio) {
        lis.inicio = nodo_a_quitar->sig;
        lis.inicio->ant = NULL;
    }
    else if (nodo_a_quitar == lis.fin) {
        lis.fin = nodo_a_quitar->ant;
        lis.fin->sig = NULL;
    }
    else {
        nodo_a_quitar->ant->sig = nodo_a_quitar->sig;
        nodo_a_quitar->sig->ant = nodo_a_quitar->ant;
    }

    delete nodo_a_quitar;
    return true;
}


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
}


void liberar_lista_palabras(pnodo_palabra &lis) {
    pnodo_palabra aux;
    while (lis != NULL) {
        aux = lis;
        lis = lis->sig;
        delete aux; 
    }
}

void liberar_diccionario(tdiccionario &dic) {
    cout << "Liberando diccionario..." << endl;
    for (int i = 0; i < MAX_CLAVES; i++) {
        liberar_lista_palabras(dic[i].listado.inicio);
        dic[i].listado.inicio = NULL; 
        dic[i].listado.fin = NULL;
    }
}



//implementacion tda ranking ----------------------------------------------------------------------
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

void iniciarlista(tlista_ranking &lista) {
    lista.inicio = NULL;
    lista.cont = 0;
}

void crearnodo(pnodo_ranking &nuevo, tinfo_ranking dato_ranking) {
    nuevo = new tnodo_ranking; 
    if (nuevo != NULL) {
        nuevo->dato = dato_ranking;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
}

void insertarordenado(pnodo_ranking actual, pnodo_ranking nuevo, pnodo_ranking inicio_lista) {
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
    }
    else {
        insertarordenado(actual->sig, nuevo, inicio_lista);
    }
}

void agregar_ranking(tlista_ranking &lista, pnodo_ranking nuevo) {
    
    
    if (lista.inicio == NULL) {
        lista.inicio = nuevo;
        lista.inicio->sig = lista.inicio;
        lista.inicio->ant = lista.inicio;
    }
    else {
        insertarordenado(lista.inicio, nuevo, lista.inicio);
        if (nuevo->dato.puntaje >= lista.inicio->dato.puntaje) {
            lista.inicio = nuevo;
        }
    }
    lista.cont++; //
}

void mostrarlista(tlista_ranking lista, bool creciente) {
    pnodo_ranking i;
    if (lista.inicio == NULL) {
        cout << "  No hay vencedores para mostrar." << endl;
    }
    else {
        if (creciente) {
            i = lista.inicio->ant;
            do {
                cout << "  - Alias: " << i->dato.alias;
                cout << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->ant; 
            } while (i != lista.inicio->ant); 
        } else {
            i = lista.inicio;
            do {
                cout << "  - Alias: " << i->dato.alias;
                cout << " (Puntaje: " << i->dato.puntaje << ")" << endl;
                i = i->sig; 
            } while (i != lista.inicio); 
        }
    }
}

void liberarlista(tlista_ranking &lista) {
    pnodo_ranking p, aux;
    
    if (lista.inicio != NULL) {
        p = lista.inicio;
        lista.inicio->ant->sig = NULL; 
        
        while (p != NULL) {
            aux = p;
            p = p->sig;
            delete aux; 
        }
        
        iniciarlista(lista);
    }
}



//implementacion tda pila ---------------------------------------------------------------------
const int MAXPILA = 6;  
typedef tpalabra tcontenedor[MAXPILA]; 

struct tpila {
    tcontenedor datos; 
    int cima;         
};

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
    if (pilallena(p) == true) {
        cout << "ERROR: La pila del espejo magico esta llena." << endl;
    }
    else {
        p.cima++; 
        p.datos[p.cima] = nuevo; 
    }
}


tpalabra quitarpila(tpila &p) {
    tpalabra extraido;
    if (pilavacia(p) == true) {
        strcpy(extraido.palabra, "ERROR_VACIA");
        strcpy(extraido.definicion, "");
        strcpy(extraido.sinonimo, "");
        extraido.longitud = 0;
    }
    else {
        extraido = p.datos[p.cima]; 
        p.cima--;                   
    }
    return extraido;
}

tpalabra topepila(tpila p) {
    tpalabra consultado;
    if (pilavacia(p) == true) {
        strcpy(consultado.palabra, "ERROR_VACIA");
        strcpy(consultado.definicion, "");
        strcpy(consultado.sinonimo, "");
        consultado.longitud = 0;
    }
    else {
        consultado = p.datos[p.cima]; 
    }
    return consultado;
}





