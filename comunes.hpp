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
	

// Valida si un caracter es letra
bool es_letra(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Verifica que una palabra solo tenga caracteres alfabeticos
bool verificar_letras(tcad palabra){
	for(int i = 0; i < (int)strlen(palabra); i++){
		if (!es_letra(palabra[i])) 
			return false;
	}
	return true;
}
	
// Convierte un caracter a mayuscula, solo si es minuscula
void convertir_letra(char &c) {
	if (c >= 'a' && c <= 'z') {
		c = c - 32;
	}
}

bool validar_longitud(tcad cadena, int minimo){
	int longitud = (int)strlen(cadena);
	return (longitud > 0 && longitud >= minimo);
}

// Lee una cadena con longitud minima, eliminando salto de linea
// Valida que la cadena ingresada no contenga espacios
void leerCadenaValidada(const tcad mensaje, tcad &cadena, int minLen) {
    bool valido = false;

    while (!valido) {
        cout << mensaje;
        fgets(cadena, MAX, stdin);
		
        int len = (int)strlen(cadena);
		
        // Eliminar salto de linea
        if (len > 0 && cadena[len - 1] == '\n') {
            cadena[len - 1] = '\0';
            len--;
        }
		
		// Validar que no este vacia y tenga la longitud minima
        if (validar_longitud(cadena, minLen)) {
			// Antes de validar, verificamos las letras
            if(verificar_letras(cadena))
				valido = true;
			else
				cout << "Invalido: La cadena debe contener solo caracteres alfabeticos" << endl;
        } else {
            cout << "Invalido: La cadena debe tener al menos " 
				<< minLen << " caracteres" << endl;
		}
    }
	convertir_letra(cadena[0]);
}


void leer_ingreso(const tcad mensaje, tcad &cadena) {
	bool valido = false;
	while(!valido){
		cout << mensaje;
		fgets(cadena, MAX, stdin);
		
		int len = (int)strlen(cadena);
		
		if (len > 0 && cadena[len - 1] == '\n') {
			cadena[len - 1] = '\0';
		}
		
		if(validar_longitud(cadena, 1)){
			valido = true;
		}else{
			cout << "Invalido: La cadena debe tener al menos 1 caracter" << endl;
		}
	}
}

// Limpia el buffer
void limpiar_buffer(){
	int c;
	while ((c = getchar()) != '\n');
}


