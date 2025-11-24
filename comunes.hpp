#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;
const int MAX = 50;
typedef char tcad[MAX];

// ------------------------------------------------------------
// FUNCIONES DE UTILIDAD
// ------------------------------------------------------------

// Limpia la pantalla (solo funciona en Windows y algunas consolas)
void limpiarPantalla() {
    system("cls");
}

// Pausa la ejecucion hasta que el usuario presione Enter
void pausarPantalla() {
    cout << "\nPresione Enter para continuar...";
    int c;
    while ((c = getchar()) != '\n');
    getchar();
}

// Lee una cadena con longitud minima, eliminando salto de linea
/*void leerCadenaValidada( const tcad mensaje, tcad &cadena, int minLen) {
    bool valido = false;

    while (!valido) {
        cout << mensaje;
        fgets(cadena, MAX, stdin);
		
        int len = strlen(cadena);
		
        // Eliminar salto de linea
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
            len--;
        }
		
		// Validar que no este vacia y tenga la longitud minima
        if (len > 0 && (int)strlen(cadena) >= minLen) {
            valido = true;
        } else {
            if (len == 0) {
				cout << "Invalido: No se permiten cadenas vacias" << endl;
        } else {
            cout << "Invalido: La cadena debe tener al menos " 
				<< minLen << " caracteres" << endl;
			}
        }
    }
}*/

void leerCadenaValidada(const char* mensaje, char* cadena, int minLen) {
    bool valido = false;
    int len;

    while (valido == false) {
        cout << mensaje;
        fgets(cadena, 60, stdin); 
        len = strlen(cadena);
        // elimina salto de linea si existe
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
            len--; 
        }
        // validacion
        if (len >= minLen) {
            valido = true;
        } 
        else {
            if (len == 0) {
                cout << "ERROR: El campo no puede estar vacio." << endl;
            } else {
                cout << "ERROR: Debe tener al menos " << minLen << " caracteres." << endl;
            }
        }
    }
}


void leer_ingreso(tcad &cadena) {
    fgets(cadena, MAX, stdin);
    int len = (int)strlen(cadena);
    if (len > 0 && cadena[len - 1] == '\n') {
        cadena[len - 1] = '\0';
    }
}

// Limpia el buffer
void limpiar_buffer(){
	int c;
	while ((c = getchar()) != '\n');
}


