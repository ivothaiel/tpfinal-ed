#include <stdlib.h>     
#include <stdio.h>      
#include <time.h>       
#include "TDA_Base.hpp"

using namespace std;


void gestionarJugadores(pjugador &arbol_jugadores);
void altaJugador(pjugador &arbol_jugadores);
void bajaJugador(pjugador &arbol_jugadores);
void modificarJugador(pjugador arbol_jugadores);
void consultarJugador(pjugador arbol_jugadores);

void gestionarPalabras(tdiccionario &dic);
void altaPalabra(tdiccionario &dic);
void bajaPalabra(tdiccionario &dic);
void modificarPalabra(tdiccionario &dic);
void consultarPalabra(tdiccionario &dic);
void listarPalabras(tdiccionario dic);

void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking);
pjugador seleccionarJugador(pjugador arbol_jugadores);
int contarPalabras(tdiccionario dic);
void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego, int &conteo);
bool jugarPalabra(tpalabra &palabra_actual, int &puntaje_partida);

void mostrarVencedores(tlista_ranking &ranking);



void limpiarPantalla() {
    system("cls"); 
}

void pausarPantalla() {
    cout << endl;
    system("pause"); 
}

void leerCadenaValidada(const char* mensaje, tcad &cadena, int minLen) {
    bool valido = false;
    while (!valido) {
        cout << mensaje;
        fflush(stdin);
        gets(cadena);
        if (strlen(cadena) >= minLen) {
            valido = true;
        } else {
            cout << "Entrada invalida. Debe tener al menos " << minLen << " caracteres." << endl;
        }
    }
}

// GESTIÓN DE PALABRAS ---

void gestionarPalabras(tdiccionario &dic) {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- GESTION DE PALABRAS ---" << endl;
        cout << "1. Alta de Palabra" << endl;
        cout << "2. Baja de Palabra" << endl;
        cout << "3. Modificar Palabra" << endl;
        cout << "4. Consultar Palabra" << endl;
        cout << "5. Listar todas las Palabras" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "Ingrese opcion: ";
        cin >> opc;

        switch(opc) {
            case 1: altaPalabra(dic); break;
            case 2: bajaPalabra(dic); break;
            case 3: modificarPalabra(dic); break;
            case 4: consultarPalabra(dic); break;
            case 5: listarPalabras(dic); break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        if (opc != 0) pausarPantalla();
    } while (opc != 0);
}

void altaPalabra(tdiccionario &dic) {
    tpalabra nueva_palabra;
    limpiarPantalla();
    cout << "--- ALTA DE PALABRA ---" << endl;
    
    leerCadenaValidada("Ingrese la palabra (min 5 caracteres): ", nueva_palabra.palabra, 5);
    
    if (nueva_palabra.palabra[0] < 'A' || nueva_palabra.palabra[0] > 'Z') {
        cout << "ERROR: La palabra debe comenzar con una letra mayuscula (A-Z)." << endl;
        return;
    }
    
    if (buscar_palabra_diccionario(dic, nueva_palabra.palabra) != NULL) {
        cout << "ERROR: La palabra '" << nueva_palabra.palabra << "' ya existe." << endl;
        return;
    }

    leerCadenaValidada("Ingrese la definicion: ", nueva_palabra.definicion, 1);
    leerCadenaValidada("Ingrese un sinonimo: ", nueva_palabra.sinonimo, 1);
    nueva_palabra.longitud = strlen(nueva_palabra.palabra);

    agregar_palabra(dic, nueva_palabra);
    cout << "Palabra '" << nueva_palabra.palabra << "' registrada con exito." << endl;
}

void bajaPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
    limpiarPantalla();
    cout << "--- BAJA DE PALABRA ---" << endl;
    leerCadenaValidada("Ingrese la palabra a eliminar: ", palabra_buscada, 1);

    if (quitar_palabra(dic, palabra_buscada)) {
        cout << "Palabra '" << palabra_buscada << "' eliminada con exito." << endl;
    } else {
        cout << "ERROR: Palabra no encontrada." << endl;
    }
}

void modificarPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
    limpiarPantalla();
    cout << "--- MODIFICAR PALABRA ---" << endl;
    leerCadenaValidada("Ingrese la palabra a modificar: ", palabra_buscada, 1);
    
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);

    if (nodo_palabra == NULL) {
        cout << "Palabra no encontrada." << endl;
    } else {
        cout << "Palabra encontrada. Ingrese nuevos datos (la palabra en si no se puede modificar):" << endl;
        cout << "Palabra: " << nodo_palabra->dato.palabra << " (No modificable)" << endl;
        
        leerCadenaValidada("Ingrese nueva definicion: ", nodo_palabra->dato.definicion, 1);
        leerCadenaValidada("Ingrese nuevo sinonimo: ", nodo_palabra->dato.sinonimo, 1);
        
        cout << "Datos de la palabra '" << nodo_palabra->dato.palabra << "' actualizados." << endl;
    }
}

void consultarPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
    limpiarPantalla();
    cout << "--- CONSULTAR PALABRA ---" << endl;
    leerCadenaValidada("Ingrese la palabra a consultar: ", palabra_buscada, 1);
    
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);

    if (nodo_palabra == NULL) {
        cout << "Palabra no encontrada." << endl;
    } else {
        cout << "--- DATOS DE LA PALABRA ---" << endl;
        cout << "Palabra: " << nodo_palabra->dato.palabra << endl;
        cout << "Longitud: " << nodo_palabra->dato.longitud << endl;
        cout << "Definicion: " << nodo_palabra->dato.definicion << endl;
        cout << "Sinonimo: " << nodo_palabra->dato.sinonimo << endl;
    }
}

void listarPalabras(tdiccionario dic) {
    limpiarPantalla();
    cout << "--- LISTADO DE PALABRAS (Ordenado Alfabeticamente) ---" << endl;
    for (int i = 0; i < MAX_CLAVES; i++) {
        if (dic[i].listado.inicio != NULL) {
            cout << "\n--- Palabras con '" << dic[i].clave << "' ---" << endl;
            pnodo_palabra p = dic[i].listado.inicio;
            while (p != NULL) {
                cout << "  - " << p->dato.palabra << " (" << p->dato.definicion << ")" << endl;
                p = p->sig;
            }
        }
    }
}
