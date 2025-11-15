#ifndef TDADICCIONARIO_HPP
#define TDADICCIONARIO_HPP

#include "TDA_Base.hpp" 

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

#endif 