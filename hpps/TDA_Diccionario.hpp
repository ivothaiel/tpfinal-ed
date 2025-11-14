
#ifndef TDA_DICCIONARIO_HPP
#define TDA_DICCIONARIO_HPP


#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;
const int TAM_CAD_DIC = 50; 
typedef char tcad[TAM_CAD_DIC];
typedef struct tinfo {
    tcad palabra;    
    tcad definicion;
    tcad sinonimo;
};

typedef struct tnodo_palabra *pnodo_palabra;
struct tnodo_palabra {
    tinfo dato;             
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

void iniciar_lista_palabras(tlista_palabras &lis) {
    lis.inicio = NULL;
    lis.fin = NULL;
}

void crear_dic(tdiccionario &dic) {
    int i;
    char letra = 'A';
    for (i = 0; i < MAX_CLAVES; i++) {
        dic[i].clave = letra;
        iniciar_lista_palabras(dic[i].listado);
        letra++; 
    }
}

void crear_nodo_palabra(pnodo_palabra &nuevo, tinfo datos) {
    nuevo = new tnodo_palabra; 
    if (nuevo != NULL) {
        nuevo->dato = datos;
        nuevo->ant = NULL;
        nuevo->sig = NULL;
    }
}

void insertar_palabra_diccionario(tdiccionario &dic, tinfo datos) {
    int i = 0;
    bool encontrado = false;
    pnodo_palabra nuevo, p;
    while (i < MAX_CLAVES && encontrado == false) {
        if (datos.palabra[0] == dic[i].clave)
            encontrado = true;
        else
            i++;
    }

    if (encontrado) {
        crear_nodo_palabra(nuevo, datos); 
        tlista_palabras &lis = dic[i].listado; 

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
            nuevo->sig = p;
            nuevo->ant = p->ant;
            p->ant->sig = nuevo;
            p->ant = nuevo;
        }
    }
    else {
        cout << "Palabra '" << datos.palabra << "' es incorrecta (no empieza con A-Z)." << endl;
        delete nuevo; 
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
            p = p->sig;
        }
    }
    return p;
}

void liberar_lista_palabras(pnodo_palabra &lis) {
    if (lis != NULL) {
        liberar_lista_palabras(lis->sig); 
        delete lis;                     
        lis = NULL;
    }
}

void liberar_diccionario(tdiccionario &dic) {
    int i;
    for (i = 0; i < MAX_CLAVES; i++) {
        liberar_lista_palabras(dic[i].listado.inicio);
        iniciar_lista_palabras(dic[i].listado);
    }
    cout << "Diccionario liberado." << endl;
}

#endif