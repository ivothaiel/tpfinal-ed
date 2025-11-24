#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;
typedef char tcadena[60];

bool existePalabra(tdiccionario &dic, tcad palabra){
	return buscar_palabra_diccionario(dic, palabra) != NULL;
}

// Permite que se ingrese una palabra, luego se valida su formato y si cumple la longitud
void altaPalabra(tdiccionario &dic) {
    tpalabra nueva_palabra;
    bool validar;

    do {
        leerCadenaValidada("Ingrese Palabra: ", nueva_palabra.palabra, 5);
		
        validar = verificar_letras(nueva_palabra.palabra);
		
        if (!validar)
            cout << "\nLa palabra solo debe contener letras" << endl;
		
    } while (!validar);

    if (buscar_palabra_diccionario(dic, nueva_palabra.palabra) != NULL)
        cout << "\nLa palabra '" << nueva_palabra.palabra << "' ya esta registrada" << endl;
    else {
        leer_ingreso("Ingrese Definicion: ", nueva_palabra.definicion);
        leerCadenaValidada("Ingrese Sinonimo: ", nueva_palabra.sinonimo, 2);
        nueva_palabra.longitud = (int)strlen(nueva_palabra.palabra);
        agregar_palabra(dic, nueva_palabra);
        cout << "Palabra '" << nueva_palabra.palabra << "' registrada con exito." << endl;
    }
	pausarPantalla();
}

// Busca y elimina una palabra del diccionario
void bajaPalabra(tdiccionario &dic){
    if (contar_palabras(dic) > 0) {
        tcad palabra_buscada;
        pnodo_palabra eliminado;
        
        leerCadenaValidada("Ingrese Palabra a Eliminar: ", palabra_buscada, 5);
        
		eliminado = eliminar_palabra(dic, palabra_buscada);
        
        if (eliminado != NULL) {
            cout << "\n'" << eliminado->dato.palabra << "' se ha eliminado correctamente" << endl;
            delete eliminado;
        }
        else {
            cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
        }
    }
    else {
        // Si no hay palabras, cae directo aca sin pedir nada
        cout << "\nNo hay palabras registradas para eliminar" << endl;
    }
    pausarPantalla();
}

void editarPalabra(pnodo_palabra nodo) {
	limpiarPantalla();
	cout << "\nEdicion de la Palabra: " << nodo->dato.palabra << endl;
	leerCadenaValidada("Ingrese Nueva Definicion: ", nodo->dato.definicion, 5);
	leerCadenaValidada("Ingrese Nuevo Sinonimo: ", nodo->dato.sinonimo, 10);
	cout << "\nDatos actualizados\n";
}

// Busca una palabra y modifica sus campos
void modificarPalabra(tdiccionario &dic) {
    if (contar_palabras(dic) > 0) {
        tcad palabra_buscada;
        
        leerCadenaValidada("Ingrese Palabra a Modificar: ", palabra_buscada, 5);
        pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);
		
        if (nodo_palabra == NULL) {
            cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
        }
        else {
            limpiarPantalla();
            cout << "\nEdicion de la Palabra: " << nodo_palabra->dato.palabra << endl;
            leer_ingreso("Ingrese Nueva Definicion: ", nodo_palabra->dato.definicion);
            leerCadenaValidada("Ingrese Nuevo Sinonimo: ", nodo_palabra->dato.sinonimo, 2);
            cout << "\nDatos de la palabra '" << nodo_palabra->dato.palabra << "' actualizados" << endl;
        }
    }
    else {
        cout << "\nNo hay palabras registradas para modificar" << endl;
    }
    pausarPantalla();
}

void mostrar_palabra(pnodo_palabra palabra) {
    cout << "\n * * DATOS DE LA PALABRA * *" << endl;
    cout << "---------------------------------" << endl;
    cout << "Palabra: " << palabra->dato.palabra << endl;
    cout << "Longitud: " << palabra->dato.longitud << " caracteres" << endl;
    cout << "Definicion: " << palabra->dato.definicion << endl;
    cout << "Sinonimo: " << palabra->dato.sinonimo << endl;
}

void consultarPalabra(tdiccionario &dic) {
    // Solo entramos si HAY palabras
    if (contar_palabras(dic) > 0) {
        pnodo_palabra palabra;
        tcad palabra_buscada;
        
        leerCadenaValidada("Ingrese Palabra a Consultar: ", palabra_buscada, 5);
		
        palabra = buscar_palabra_diccionario(dic, palabra_buscada);
		
        if (palabra == NULL)
            cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
        else
            mostrar_palabra(palabra);
    }
    else {
        cout << "\nNo hay palabras registradas para consultar" << endl;
    }
    pausarPantalla();
}

// Quitar si no se usa
void listarPalabrasPorClave(tlista_palabras lista) {
	pnodo_palabra p = lista.inicio;
	while (p != NULL) {
		cout << " - " << p->dato.palabra << "\n   Definicion: " << p->dato.definicion << "\n   Sinonimo: " << p->dato.sinonimo << "\n";
		p = p->sig;
	}
}



void listarPalabras(tdiccionario dic) {
    bool hayPalabras = false;

    for (int i = 0; i < MAX_CLAVES; i++) {
        if (dic[i].listado.inicio != NULL) {
            hayPalabras = true;
            
            cout << "\n>>> Palabras que comienzan con '" << dic[i].clave << "':" << endl;
            cout << "--------------------------------------\n";
            
            pnodo_palabra p = dic[i].listado.inicio;
            
            while (p != NULL) {
                cout << " - " << p->dato.palabra << "\n   Definicion: " << p->dato.definicion << "\n   Sinonimo: " << p->dato.sinonimo << "\n";
                p = p->sig;
            }
        }
    }

    if (!hayPalabras)
        cout << "\nNo hay palabras registradas en el diccionario" << endl;
        
    pausarPantalla(); // Mover pausa aqui para evitar duplicados
}

void gestionarPalabras(tdiccionario &dic) {
    char opc;
    bool salir = false;

    while (!salir) {
        limpiarPantalla();
        cout << "\n";
        cout << " +---------------------------------------+\n";
        cout << " |      * Gestion de Palabras *          |\n";
        cout << " +---------------------------------------+\n\n";
        cout << "   1) Registrar Palabra" << endl;
        cout << "   2) Eliminar Palabra" << endl;
        cout << "   3) Modificar Palabra" << endl;
        cout << "   4) Consultar Palabra" << endl;
        cout << "   5) Listar Palabras" << endl;
        cout << "   0) Volver\n" << endl;
        cout << "> Opcion: ";
        cin >> opc;
		limpiar_buffer(); // Limpiar DESPUES de leer para eliminar el \n que queda
		
        switch (opc) {
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
                pausarPantalla();
        }
    }
}
