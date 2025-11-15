#include <stdio.h>
#include <string.h>
#include <iostream>

#include "TDA_Base.hpp"
#include "TDAJugador.hpp"
#include "TDADiccionario.hpp"

using namespace std;
/* ======================================================
   ARCHIVO: JUGADORES.DAT
   ====================================================== */

void guardar_jugadores_rec(pjugador arbol, FILE *f) {
    if (arbol != NULL) {
        fwrite(&arbol->dato, sizeof(tjugador), 1, f);
        guardar_jugadores_rec(arbol->izq, f);
        guardar_jugadores_rec(arbol->der, f);
    }
}

void guardar_jugadores(pjugador arbol) {
    FILE *f;

    f = fopen("jugadores.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir jugadores.dat\n");
    } else {
        guardar_jugadores_rec(arbol, f);
        fclose(f);
    }
}

void cargar_jugadores(pjugador &arbol) {
    FILE *f;
    tjugador aux;
    pjugador nuevo;

    f = fopen("jugadores.dat", "rb");
    if (f != NULL) {
        fread(&aux, sizeof(tjugador), 1, f);
        while (!feof(f)) {
            crear_jugador(nuevo, aux);
            insertar_jugador(arbol, nuevo);
            fread(&aux, sizeof(tjugador), 1, f);
        }
        fclose(f);
    }
}


/* ======================================================
   ARCHIVO: PALABRAS.DAT
   ====================================================== */

void guardar_palabras_lista(pnodo_palabra lista, FILE *f) {
    pnodo_palabra p = lista;
    while (p != NULL) {
        fwrite(&p->dato, sizeof(tpalabra), 1, f);
        p = p->sig;
    }
}

void guardar_palabras(tdiccionario dic) {
    FILE *f;
    int i;

    f = fopen("palabras.dat", "wb");
    if (f == NULL) {
        printf("Error al abrir palabras.dat\n");
    } else {
        for (i = 0; i < MAX_CLAVES; i++) {
            guardar_palabras_lista(dic[i].listado.inicio, f);
        }
        fclose(f);
    }
}

void cargar_palabras(tdiccionario &dic) {
    FILE *f;
    tpalabra aux;

    pnodo_palabra nuevo;

    f = fopen("palabras.dat", "rb");
    if (f != NULL) {

        fread(&aux, sizeof(tpalabra), 1, f);
        while (!feof(f)) {

            crearnodo(nuevo, aux);
            agregar_palabra(dic, aux);

            fread(&aux, sizeof(tpalabra), 1, f);
        }
        fclose(f);
    }
}