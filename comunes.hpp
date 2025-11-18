#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  
#include <time.h> 

using namespace std;

// --- CONSTANTES Y TIPOS GLOBALES ---
const int MAX = 50; 
typedef char tcad[MAX];

// --- FUNCIONES DE UTILIDAD ---

void limpiarPantalla() {
    system("cls"); 
}

// Pausa la ejecucion
void pausarPantalla() {
    cout << "\nPresione Enter para continuar...";
    int c;
    while ((c = getchar()) != '\n');
    getchar(); 
}

// Lectura validada de cadenas
void leerCadenaValidada(const char* mensaje, tcad &cadena, int minLen) {
    bool valido = false;
    while (!valido) {
        cout << mensaje;
        fgets(cadena, MAX, stdin); 
        int len = strlen(cadena);
        if (len > 0 && cadena[len - 1] == '\n')
            cadena[len - 1] = '\0'; 
        
        if ((int)strlen(cadena) >= minLen)
            valido = true;
        else
            cout << "Invalido: La cadena debe tener al menos " << minLen << " caracteres" << endl;
    }
}