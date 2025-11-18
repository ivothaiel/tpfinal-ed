#include <iostream>
#include <string.h>
#include <stdio.h>
using namespace std;
const char* ARCHIVO_JUGADOR = "jugadores.dat"; 
const char* ARCHIVO_PALABRAS = "palabras.dat";

void guardar(pjugador arbol, FILE *archivo) {
    if (arbol != NULL) {
        fwrite(&(arbol->dato), sizeof(tjugador), 1, archivo);
        guardar(arbol->izq, archivo);
        guardar(arbol->der, archivo);
    }
}

void guardarjugadores(pjugador arbol_jugadores) {
    FILE *archivo;
    archivo = fopen(ARCHIVO_JUGADOR, "wb"); 
    if (archivo == NULL) {
        cout << "ERROR: No se pudo crear 'jugadores.dat'." << endl;
        return;
    }
    guardar(arbol_jugadores, archivo);
    fclose(archivo);
    cout << "Jugadores guardados." << endl;
}

void cargarjugadores(pjugador &arbol_jugadores) {
    FILE *archivo; 
    tjugador jugador_leido;
    pjugador nuevo;
    archivo = fopen(ARCHIVO_JUGADOR, "rb"); 
    if (archivo == NULL) {
        cout << "Archivo 'jugadores.dat' no encontrado. Se creara uno nuevo al salir." << endl;
        return; 
    }
    fread(&jugador_leido, sizeof(tjugador), 1, archivo);
    while (!feof(archivo)) {
        crear_jugador(nuevo, jugador_leido); 
        insertar_jugador(arbol_jugadores, nuevo);
        fread(&jugador_leido, sizeof(tjugador), 1, archivo);
    }
    fclose(archivo); 
    cout << "Jugadores cargados en el arbol." << endl;
}

void guardarpalabras(tdiccionario dic) {
    FILE *archivo;
    pnodo_palabra p; 
    archivo = fopen(ARCHIVO_PALABRAS, "wb");
    if (archivo == NULL) {
        cout << "ERROR: No se pudo crear 'palabras.dat'." << endl;
        return;
    }
    for (int i = 0; i < MAX_CLAVES; i++) {
        p = dic[i].listado.inicio;
        while (p != NULL) {
            fwrite(&(p->dato), sizeof(tpalabra), 1, archivo);
            p = p->sig; 
        }
    }
    fclose(archivo);
    cout << "Palabras guardadas." << endl;
}

void cargarpalabras(tdiccionario &dic) {
    FILE *archivo;
    tpalabra palabra_leida;
    archivo = fopen(ARCHIVO_PALABRAS, "rb");
    if (archivo == NULL) {
        cout << "Archivo 'palabras.dat' no encontrado. Se creara uno nuevo al salir." << endl;
        return;
    }
    fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
    while (!feof(archivo)) {
        agregar_palabra(dic, palabra_leida); 
        fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
    }
    fclose(archivo);
    cout << "Palabras cargadas en el diccionario." << endl;
}
