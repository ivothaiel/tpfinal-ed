#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#include "TDA_Base.hpp"
const char* ARCHIVO_JUGADOR = "jugadores.dat"; 
const char* ARCHIVO_PALABRAS = "palabras.dat";

void guardar_recursivo(pjugador arbol, FILE *archivo) {
    if (arbol != NULL) {
        // 1. Raíz (Procesar): Escribimos el dato
        fwrite(&(arbol->dato), sizeof(tjugador), 1, archivo); //
        // 2. Izquierda
        guardar_recursivo(arbol->izq, archivo);
        // 3. Derecha
        guardar_recursivo(arbol->der, archivo);
    }
}

void guardarjugadores(pjugador arbol_jugadores) {
    FILE *archivo;
    
    // 1. Abrimos en modo "wb" (write binary)
    archivo = fopen(ARCHIVO_JUGADOR, "wb"); //

    if (archivo == NULL) {
        cout << "ERROR: No se pudo crear 'jugadores.dat'." << endl;
        return;
    }
    guardar_recursivo(arbol_jugadores, archivo);
    fclose(archivo); //
    cout << "Jugadores guardados." << endl;
}

void cargarjugadores(pjugador &arbol_jugadores) {
    FILE *archivo; 
    tjugador jugador_leido; // Esta es 'tjugador' (de TDA_Base.hpp)
    pjugador nuevo;

    // 1. Abrimos en modo "rb" (read binary)
    archivo = fopen(ARCHIVO_JUGADOR, "rb"); //

    if (archivo == NULL) {
        cout << "Archivo 'jugadores.dat' no encontrado. Se creara uno nuevo al salir." << endl;
        return; 
    }

    // 3. Leemos registro por registro
    fread(&jugador_leido, sizeof(tjugador), 1, archivo); //
    while (!feof(archivo)) { //
        
        // ¡ESTA ES LA LÍNEA QUE DABA ERROR!
        // Ahora 'jugador_leido' es 'tjugador' (de TDA_Base)
        // y 'crear_jugador' (de TDAJugador) espera 'tjugador' (de TDA_Base).
        // ¡Ahora sí coinciden!
        crear_jugador(nuevo, jugador_leido); 
        insertar_jugador(arbol_jugadores, nuevo);
        
        fread(&jugador_leido, sizeof(tjugador), 1, archivo);
    }

    fclose(archivo); 
    cout << "Jugadores cargados en el arbol." << endl;
}


// --- 4. Operaciones de Archivo de PALABRAS (Diccionario) ---

void guardarpalabras(tdiccionario dic) {
    FILE *archivo;
    pnodo_palabra p; 

    archivo = fopen(ARCHIVO_PALABRAS, "wb");
    if (archivo == NULL) {
        cout << "ERROR: No se pudo crear 'palabras.dat'." << endl;
        return;
    }

    // Recorremos el arreglo (A-Z)
    for (int i = 0; i < MAX_CLAVES; i++) {
        // Recorremos cada lista doble
        p = dic[i].listado.inicio;
        while (p != NULL) {
            // Escribimos el dato (tpalabra)
            fwrite(&(p->dato), sizeof(tpalabra), 1, archivo);
            p = p->sig; 
        }
    }
    fclose(archivo);
    cout << "Palabras guardadas." << endl;
}

void cargarpalabras(tdiccionario &dic) {
    FILE *archivo;
    tpalabra palabra_leida; // (de TDA_Base.hpp)

    archivo = fopen(ARCHIVO_PALABRAS, "rb");

    if (archivo == NULL) {
        cout << "Archivo 'palabras.dat' no encontrado. Se creara uno nuevo al salir." << endl;
        return;
    }

    fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
    while (!feof(archivo)) {
        // Usamos la función de tu TDADiccionario.hpp
        agregar_palabra(dic, palabra_leida); 
        
        fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
    }

    fclose(archivo);
    cout << "Palabras cargadas en el diccionario." << endl;
}
