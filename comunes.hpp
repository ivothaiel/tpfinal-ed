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
void leerCadenaValidada(const tcad mensaje, tcad &cadena, int minLen) {
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


// Lee una cadena de caracteres asegurando que el buffer este limpio
// antes de la lectura y eliminando el caracter de salto de linea (\n).
void leer_ingreso(tcad &cadena) {
	int c;
	// 1. Limpia el buffer antes de la lectura
	while ((c = getchar()) != '\n'); 
	
	// 2. Lee la cadena
	fgets(cadena, MAX, stdin); 
	
	// 3. Elimina el salto de linea ('\n') y lo reemplaza por el caracter nulo ('\0')
	int len = strlen(cadena);
	if (len > 0 && cadena[len - 1] == '\n') {
		cadena[len - 1] = '\0'; 
	}
}
