#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

tcad ARCHIVO_JUGADOR = "jugadores.dat";
tcad ARCHIVO_PALABRAS = "palabras.dat";


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
    //solo entram si el archivo no es NULL
    if (archivo != NULL) {
        guardar(arbol_jugadores, archivo);
        fclose(archivo);
        cout << "Jugadores guardados." << endl;
    } else {
        cout << "ERROR: No se pudo crear 'jugadores.dat'." << endl;
    }
}

void cargarjugadores(pjugador &arbol_jugadores) {
    FILE *archivo;
    tjugador jugador_leido;
    pjugador nuevo;
    int contador = 0;

    archivo = fopen(ARCHIVO_JUGADOR, "rb");
    if (archivo != NULL) {
        fread(&jugador_leido, sizeof(tjugador), 1, archivo);
        while (!feof(archivo)) {
            crear_jugador(nuevo, jugador_leido);
            if (nuevo != NULL) {
                insertar_jugador(arbol_jugadores, nuevo);
                contador++;
            } else {
                cout << "ERROR: No se pudo cargar un jugador (memoria insuficiente)" << endl;
            }
            fread(&jugador_leido, sizeof(tjugador), 1, archivo);
        }

        fclose(archivo);
        
        if (contador > 0) {
            cout << "Jugadores cargados en el arbol: " << contador << " jugador(es)" << endl;
        } else {
            cout << "El archivo de jugadores esta vacio." << endl;
        }

    } else {
        cout << "Archivo 'jugadores.dat' no encontrado. Se creara uno nuevo al salir." << endl;
    }
}

void guardarpalabras(tdiccionario dic) {
    FILE *archivo;
    pnodo_palabra p;

    archivo = fopen(ARCHIVO_PALABRAS, "wb");
    if (archivo != NULL) {
        for (int i = 0; i < MAX_CLAVES; i++) {
            p = dic[i].listado.inicio;
            while (p != NULL) {
                fwrite(&(p->dato), sizeof(tpalabra), 1, archivo);
                p = p->sig;
            }
        }
        fclose(archivo);
        cout << "Palabras guardadas." << endl;
    } else {
        cout << "ERROR: No se pudo crear 'palabras.dat'." << endl;
    }
}

void cargarpalabras(tdiccionario &dic) {
    FILE *archivo;
    tpalabra palabra_leida;
    int contador = 0;
    archivo = fopen(ARCHIVO_PALABRAS, "rb");
    if (archivo != NULL) {
        fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
        
        while (!feof(archivo)) {
            agregar_palabra(dic, palabra_leida);
            contador++;
            fread(&palabra_leida, sizeof(tpalabra), 1, archivo);
        }

        fclose(archivo);

        if (contador > 0) {
            cout << "Palabras cargadas en el diccionario: " << contador << " palabra(s)" << endl;
        } else {
            cout << "El archivo de palabras esta vacio." << endl;
        }
    } else {
        cout << "Archivo 'palabras.dat' no encontrado. Se creara uno nuevo al salir." << endl;
    }
}