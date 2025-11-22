#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
typedef char tcadena[60];

// Valida si un caracter es letra
bool es_letra(char c) {
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Verifica que una palabra solo tenga caracteres alfabeticos
bool verificar_letras(tcad palabra){
	for(int i = 0; i < (int)strlen(palabra); i++){
		if (!es_letra(palabra[i])) return false;
	}
	return true;
}
	
// Convierte un caracter a mayuscula, solo si es minuscula
void convertir_letra(char &c) {
	if (c >= 'a' && c <= 'z') {
		c = c - 32;
	}
}
	
// Imprime una cadena de caracteres, caracter por caracter
void mostrar_cadena(tcad palabra) {
	int i;
	for (i = 0; i < (int)strlen(palabra); i++) {
		char c = palabra[i];
		cout << c;
	}
}
	
void leerPalabra(tcad &palabra){
	leerCadenaValidada("Ingrese palabra: ", palabra, 5);
	convertir_letra(palabra[0]);
}

bool validarPalabra(tcad palabra){
	return verificar_letras(palabra);
}

void leerDatosPalabra(tpalabra_simple &pal){
	leerCadenaValidada("Ingrese Definicion: ", pal.definicion, 5);
	leerCadenaValidada("Ingrese Sinonimo: ", pal.sinonimo,2);
	pal.longitud = strlen(pal.palabra);
}

bool existePalabra(tdiccionario &dic, tcad palabra){
	return buscar_palabra_diccionario(dic, palabra) != NULL;
}

// Permite que se ingrese una palabra, luego se valida su formato y si cumple la longitud
void altaPalabra(tdiccionario &dic) {
    limpiar_buffer();
	tpalabra nueva;
	bool ok = false;
	do{
		leerPalabra(nueva.palabra);
		ok = validarPalabra(nueva.palabra);
		if(!ok){
			cout << "\nLa palabra solo debe contener letras\n";
		}
	} while(!ok);
	leerDatosPalabra(nueva);
	agregar_palabra(dic,nueva);
}

// busca y elimina una palabra del diccionario
void bajaPalabra(tdiccionario &dic) {
   limpiar_buffer();
   tcad buscada;
   leerPalabra(buscada);
   pnodo_palabra nodo = buscar_palabra_diccionario(dic,buscada);
   
   if(nodo == NULL){
	   cout << "\n'" << buscada << "'no existe\n";
   }
   pnodo_palabra quitado = eliminar_palabra(dic,buscada);
   cout << "\n'" << quitado->dato.palabra << "'se ha eliminado correctamente\n";
   delete quitado;
}

void editarPalabra(pnodo_palabra nodo) {
	limpiarPantalla();
	cout << "\nEdicion de la Palabra: " << nodo->dato.palabra << endl;
	leerCadenaValidada("Ingrese Nueva Definicion: ", nodo->dato.definicion, 5);
	leerCadenaValidada("Ingrese Nuevo Sinonimo: ", nodo->dato.sinonimo, 2);
	cout << "\nDatos actualizados\n";
}


void modificarPalabra(tdiccionario &dic) {
	limpiar_buffer();
	tcad buscada;
	leerPalabra(buscada);
	pnodo_palabra nodo = buscar_palabra_diccionario(dic, buscada);
	if (nodo == NULL) {
		cout << "\n'" << buscada << "' no existe\n";
	}
	editarPalabra(nodo);
}



// busca una palabra y modifica sus campos
/*void modificarPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
    int c;
	
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Palabra a Modificar: ", palabra_buscada, 5);
    convertir_letra(palabra_buscada[0]);

    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);

    if (nodo_palabra == NULL) {
        cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
    }
    else {
        limpiarPantalla();
        cout << "\nEdicion de la Palabra: " << nodo_palabra->dato.palabra << endl;
        leerCadenaValidada("Ingrese Nueva Definicion: ", nodo_palabra->dato.definicion, 5);
        leerCadenaValidada("Ingrese Nuevo Sinonimo: ", nodo_palabra->dato.sinonimo, 2);
        cout << "\nDatos de la palabra '" << nodo_palabra->dato.palabra << "' actualizados" << endl;
    }
}*/

void mostrar_palabra(pnodo_palabra palabra) {
    cout << "\n * * DATOS DE LA PALABRA * *" << endl;
    cout << "---------------------------------" << endl;
    cout << "Palabra: " << palabra->dato.palabra << endl;
    cout << "Longitud: " << palabra->dato.longitud << " caracteres" << endl;
    cout << "Definicion: " << palabra->dato.definicion << endl;
    cout << "Sinonimo: " << palabra->dato.sinonimo << endl;
}


void consultarPalabra(tdiccionario &dic) {
	limpiar_buffer();
	tcad buscada;
	leerPalabra(buscada);
	pnodo_palabra nodo = buscar_palabra_diccionario(dic, buscada);
	if (nodo == NULL) {
		cout << "\n'" << buscada << "' no existe\n";
		return;
	}
	mostrar_palabra(nodo);
}


/*void consultarPalabra(tdiccionario &dic) {
    pnodo_palabra palabra;
    tcad palabra_buscada;
    int c;
	
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Palabra a Consultar: ", palabra_buscada, 5);
    convertir_letra(palabra_buscada[0]);

    palabra = buscar_palabra_diccionario(dic, palabra_buscada);

    if (palabra == NULL)
        cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
    else
        mostrar_palabra(palabra);
}*/
void listarPalabrasPorClave(tlista_palabras lista) {
	pnodo_palabra p = lista.inicio;
	while (p != NULL) {
		cout << " - " << p->dato.palabra << "\n Definicion: " << p->dato.definicion << "\n";
		p = p->sig;
	}
}


void listarPalabras(tdiccionario dic) {
	bool hay = false;
	for (int i = 0; i < MAX_CLAVES; i++) {
		if (dic[i].listado.inicio != NULL) {
			hay = true;
			cout << "\n>>> Palabras que comienzan con '" << dic[i].clave << "':\n";
			cout << "--------------------------------------\n";
			listarPalabrasPorClave(dic[i].listado);
		}
	}
	if (!hay) cout << "\nNo hay palabras registradas\n";
}
/*void listarPalabras(tdiccionario dic) {
    bool hayPalabras = false;

    for (int i = 0; i < MAX_CLAVES; i++) {
        if (dic[i].listado.inicio != NULL) {
			dd
            hayPalabras = true;
			
            cout << "\n>>> Palabras que comienzan con '" << dic[i].clave << "':" << endl;
            cout << "--------------------------------------\n";
			
            pnodo_palabra p = dic[i].listado.inicio;
			
            while (p != NULL) {
                cout << " - " << p->dato.palabra
                     << "\n Definicion: " << p->dato.definicion << "\n";
                p = p->sig;
            }
        }
    }

    if (!hayPalabras)
        cout << "\nNo hay palabras registradas en el diccionario" << endl;
}*/

void gestionarPalabras(tdiccionario &dic) {
    char op;
    bool salir = false;
    tcad msg_menu = "\n> Opcion: ";

    while (!salir) {
        limpiarPantalla();
        cout << "\n";
        cout << " +---------------------------------------+\n";
        cout << " |      * Gestion de Palabras * |\n";
        cout << " +---------------------------------------+\n\n";
        cout << "   1) Registrar Palabra" << endl;
        cout << "   2) Eliminar Palabra" << endl;
        cout << "   3) Modificar Palabra" << endl;
        cout << "   4) Consultar Palabra" << endl;
        cout << "   5) Listar Palabras" << endl;
        cout << "   0) Volver\n" << endl;
        cout << "\n> Opcion: ";
        cin >> op;
		
        switch (op) {
            case '1':
                cout << "\n* * Registrar Palabra * *\n" << endl;
                altaPalabra(dic);
                break;
				
            case '2':
                cout << "\n* * Eliminar Palabra * *\n" << endl;
                bajaPalabra(dic);
                break;
				
            case '3':
                cout << "\n* * Modificar Palabra * *\n" << endl;
                modificarPalabra(dic);
                break;
				
            case '4':
                cout << "\n* * Consultar Palabra * *\n" << endl;
                consultarPalabra(dic);
                break;
				
            case '5':
                cout << "\n* * Listado de Palabras * *" << endl;
                listarPalabras(dic);
                break;
				
            case '0':
                cout << "\nVolviendo al menu principal..." << endl;
                salir = true;
                break;
				
            default:
                cout << "\nOPCION INVALIDA" << endl;
        }
		
        if (!salir)
            pausarPantalla();
    }
}