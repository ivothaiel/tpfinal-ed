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
void leerCadenaValidada( const tcad mensaje, tcad &cadena, int minLen) {
    bool valido = false;

    while (!valido) {
        cout << mensaje;
        fgets(cadena, MAX, stdin);
		
        int len = strlen(cadena);
		
        // Eliminar salto de linea
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
        }
		
        if ((int)strlen(cadena) >= minLen) {
            valido = true;
        } else {
            cout << "Invalido: La cadena debe tener al menos " 
				<< minLen << " caracteres" << endl;
        }
    }
}

// Lee una cadena asegurando limpiar el buffer antes
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



char leer_opcion_caracter(tcad mensaje, char min, char max) {
    char opcion;
    bool valido = false;
    tcad entrada; 
    while (!valido) {
        cout << mensaje;
        leer_ingreso(entrada);
        if (strlen(entrada) == 1) {
            opcion = entrada[0];
            if (opcion >= min && opcion <= max) {
                valido = true;
            } else {
                cout << "\n>>> Opcion invalida. Ingrese entre '" << min << "' y '" << max << "'.\n";
            }
        } else {
            cout << "\n>>> Entrada invalida. Ingrese un solo caracter.\n";
        }
    }
    return opcion;
}