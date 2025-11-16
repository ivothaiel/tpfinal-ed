
#include <iostream>
#include <stdlib.h>     
#include <stdio.h>      
#include <time.h>
#include <string.h>
    
//#include "TDA_Base.hpp"
#include "TDAJugador.hpp"
#include "TDA_Base.hpp"
//#include "TDADiccionario.hpp"
//#include "TDARanking.hpp"
//#include "TDAPila.hpp"

typedef char tcad[30];

//using namespace std;

// --- Prototipos de funciones ---
/*
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
*/

// --- Funciones Auxiliares ---

void limpiar_pantalla() {
    system("cls"); 
}

void pausar_pantalla() {
    cout << endl;
    system("pause"); 
}

// -------------------------
/*
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
}*/

/*
void gestionarJugadores(pjugador &arbol_jugadores) {
    int opc;
    do {
        limpiarPantalla();
        cout << "--- GESTION DE JUGADORES ---" << endl;
        cout << "1. Alta de Jugador" << endl;
        cout << "2. Baja de Jugador" << endl;
        cout << "3. Modificar Jugador" << endl;
        cout << "4. Consultar Jugador" << endl;
        cout << "5. Listar todos los Jugadores" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "Ingrese opcion: ";
        cin >> opc;

        switch(opc) {
            case 1: altaJugador(arbol_jugadores); break;
            case 2: bajaJugador(arbol_jugadores); break;
            case 3: modificarJugador(arbol_jugadores); break;
            case 4: consultarJugador(arbol_jugadores); break;
            case 5: 
                limpiarPantalla();
                cout << "--- LISTADO DE JUGADORES (Ordenado por Alias) ---" << endl;
                listar_jugadores(arbol_jugadores);
                break;
            case 0: cout << "Volviendo al menu principal..." << endl; break;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        if (opc != 0) pausarPantalla();
    } while (opc != 0);
}*/


// Valida la que la longitud de la cadena sea >= 'longitud'
bool validar_longitud(tcad cadena, int longitud){
	return (int)strlen(cadena) >= longitud;
}

// Permite la carga de datos de un nuevo jugador
// Controla que las cadenas tengan una longitud >= 4
void cargar_jugador(tjugador &jugador){
	fflush(stdin);
	cout << "\n* * REGISTRO DE JUGADOR * *" << endl;
	
	bool valido = false;
	
	while (!valido) {
		
		cout << "Ingrese Nombre: ";
		gets(jugador.nombre);
		
		cout << "Ingrese Apellido: ";
		gets(jugador.apellido);
		
		cout << "Ingrese Alias: ";
		gets(jugador.alias);
		
		cout << "Ingrese Signo: ";
		gets(jugador.signo);
		
		// Validar cadenas
		if (validar_longitud(jugador.alias, 4) &&
			validar_longitud(jugador.nombre, 4) &&
			validar_longitud(jugador.apellido, 4)) {
			valido = true;
		} else {
			cout << "\nERROR: Todos los campos deben tener al menos 4 caracteres.\n";
			cout << "Vuelva a ingresar los datos del jugador.\n\n";
		}
	}
	
	// Inicializar otros datos
	jugador.juegos_ganados = 0;
	jugador.mejor_puntaje = 0;
	jugador.puntaje_acumulado = 0;
}

// Realiza el alta de un nuevo jugador
// Realiza un control para determinar si el jugador debe ser agregado o no
void alta_jugador(pjugador &jugadores){
	pjugador nuevo;
	tjugador jugador;
	cargar_jugador(jugador);
	if(buscar_alias(jugadores, jugador.alias)){
		cout << "\nERROR: El alias ya est� registrado. No se puede dar de alta el jugador.\n";
	}else{
		crear_jugador(nuevo, jugador);
		insertar_jugador(jugadores, jugador);
		cout << "\nJugador registrado correctamente.\n"
	}
}

	/*
void altaJugador(pjugador &arbol_jugadores) {
    tjugador nuevo_dato;
    pjugador nuevo_nodo;
    
    limpiarPantalla();
    cout << "--- ALTA DE JUGADOR ---" << endl;
    
    leerCadenaValidada("Ingrese Alias (min 4 caracteres): ", nuevo_dato.alias, 4);
    
    if (buscar_jugador(arbol_jugadores, nuevo_dato.alias) != NULL) {
        cout << "ERROR: El alias '" << nuevo_dato.alias << "' ya existe." << endl;
        return;
    }

    leerCadenaValidada("Ingrese Nombre (min 4 caracteres): ", nuevo_dato.nombre, 4);
    leerCadenaValidada("Ingrese Apellido (min 4 caracteres): ", nuevo_dato.apellido, 4);
    leerCadenaValidada("Ingrese Signo Zodiacal: ", nuevo_dato.signo, 1);
    
    nuevo_dato.juegos_ganados = 0;
    nuevo_dato.mejor_puntaje = 0;
    nuevo_dato.puntaje_acumulado = 0;

    crear_jugador(nuevo_nodo, nuevo_dato);
    if (nuevo_nodo != NULL) {
        insertar_jugador(arbol_jugadores, nuevo_nodo);
        cout << "Jugador '" << nuevo_dato.alias << "' registrado con exito." << endl;
    }
}*/

/*
void bajaJugador(pjugador &arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- BAJA DE JUGADOR ---" << endl;
    leerCadenaValidada("Ingrese Alias del jugador a eliminar: ", alias_buscado, 1);

    eliminar_nodo_jugador(arbol_jugadores, alias_buscado);
}*/
	
/*
void modificarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- MODIFICAR JUGADOR ---" << endl;
    leerCadenaValidada("Ingrese Alias del jugador a modificar: ", alias_buscado, 1);
    
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);

    if (nodo_jugador == NULL) {
        cout << "Jugador no encontrado." << endl;
    } else {
        cout << "Jugador encontrado. Ingrese nuevos datos (alias, puntajes y juegos ganados NO se pueden modificar):" << endl;
        
        cout << "Alias: " << nodo_jugador->dato.alias << " (No modificable)" << endl;
        leerCadenaValidada("Ingrese nuevo Nombre: ", nodo_jugador->dato.nombre, 4);
        leerCadenaValidada("Ingrese nuevo Apellido: ", nodo_jugador->dato.apellido, 4);
        leerCadenaValidada("Ingrese nuevo Signo Zodiacal: ", nodo_jugador->dato.signo, 1);
        
        cout << "Datos del jugador '" << nodo_jugador->dato.alias << "' actualizados." << endl;
    }
}*/

/*
void consultarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- CONSULTAR JUGADOR ---" << endl;
    leerCadenaValidada("Ingrese Alias del jugador a consultar: ", alias_buscado, 1);
    
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);

    if (nodo_jugador == NULL) {
        cout << "Jugador no encontrado." << endl;
    } else {
        cout << "--- DATOS DEL JUGADOR ---" << endl;
        cout << "Alias: " << nodo_jugador->dato.alias << endl;
        cout << "Nombre: " << nodo_jugador->dato.nombre << " " << nodo_jugador->dato.apellido << endl;
        cout << "Signo: " << nodo_jugador->dato.signo << endl;
        cout << "Puntaje Max: " << nodo_jugador->dato.mejor_puntaje << endl;
        cout << "Puntaje Acum: " << nodo_jugador->dato.puntaje_acumulado << endl;
        cout << "Juegos Ganados: " << nodo_jugador->dato.juegos_ganados << endl;
    }
}*/

void mostrar_jugador(pjugador jugador){
	//cout << "\n* * DATOS DEL JUGADOR * *\n" << endl;
	cout << "Alias: " << jugador->dato.alias << endl;
	cout << "Nombre: " << jugador->dato.nombre << " " << jugador->dato.apellido << endl;
	cout << "Signo: " << jugador->dato.signo << endl;
	cout << "Puntaje Max: " << jugador->dato.mejor_puntaje << endl;
	cout << "Puntaje Acum: " << jugador->dato.puntaje_acumulado << endl;
	cout << "Juegos Ganados: " << jugador->dato.juegos_ganados << endl;
}

void consultar_jugador(pjugador jugadores){
	fflush(stdin);
	tcad buscado;
	cout << "\nIngrese el alias del usuario: ";
	gets(buscado);
	pjugador jugador_buscado = buscar_jugador(jugadores, buscado);
	if(jugador_buscado != NULL){
		cout << "\n* * DATOS DEL JUGADOR * *\n" << endl;
		mostrar_jugador(jugador_buscado);
	}else
		cout << "\nEl alias ingresado no pertenece a ningun jugador" << endl;
}


// --- MÓDULO 2: GESTIÓN DE PALABRAS ---
/*
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

int contarPalabras(tdiccionario dic) {
    int conteo = 0;
    for (int i = 0; i < MAX_CLAVES; i++) {
        pnodo_palabra p = dic[i].listado.inicio;
        while (p != NULL) {
            conteo++;
            p = p->sig;
        }
    }
    return conteo;
}

void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- INICIANDO JUEGO: EL MISTERIO DE LA PRINCESA DE FUEGO ---" << endl;

    int num_jugadores = contarJugadores(arbol_jugadores);
    int num_palabras = contarPalabras(dic);

    if (num_jugadores < 1) { 
        cout << "No se puede iniciar. Deben existir al menos 1 jugador." << endl;
        return;
    }
    if (num_palabras < 6) {
        cout << "No se puede iniciar. Deben existir al menos 6 palabras en el diccionario." << endl;
        return;
    }
    
    pjugador jugador_actual = seleccionarJugador(arbol_jugadores);
    if (jugador_actual == NULL) return; 

    tpila pila_juego;
    int conteo_palabras_pila = 0;
    seleccionarPalabrasAleatorias(dic, pila_juego, conteo_palabras_pila);
    
    if (conteo_palabras_pila < 6) {
        cout << "Error critico: No se pudieron cargar las 6 palabras en la pila." << endl;
        return;
    }

    int puntaje_partida = 7; 
    bool jugador_pierde = false;
    int palabras_adivinadas = 0;

    cout << "\n¡Comienza el desafio, " << jugador_actual->dato.alias << "!" << endl;
    cout << "La princesa te obsequia 7 puntos." << endl;
    pausarPantalla();

    while (pilavacia(pila_juego) == false && jugador_pierde == false) {
        limpiarPantalla();
        tpalabra palabra_actual = quitarpila(pila_juego);
        
        cout << "--- JOYA " << (palabras_adivinadas + 1) << " DE 6 ---" << endl;
        cout << "Puntaje actual: " << puntaje_partida << endl;
        
        if (jugarPalabra(palabra_actual, puntaje_partida)) {
            puntaje_partida += 7; 
            palabras_adivinadas++;
            cout << "¡CORRECTO! Has ganado 7 puntos." << endl;
            if (pilavacia(pila_juego) == false) {
                 cout << "Preparando siguiente joya..." << endl;
            }
        } else {
            jugador_pierde = true;
            cout << "Has fallado. La guardiana del espejo te convierte en piedra..." << endl;
        }
        pausarPantalla();
    }

    limpiarPantalla();
    if (jugador_pierde == false) {
        cout << "¡FELICIDADES, " << jugador_actual->dato.alias << "!" << endl;
        cout << "¡Has descubierto las 6 palabras y liberado a la princesa!" << endl;
        cout << "Puntaje final de la partida: " << puntaje_partida << endl;

        jugador_actual->dato.juegos_ganados++;
        jugador_actual->dato.puntaje_acumulado += puntaje_partida;
        if (puntaje_partida > jugador_actual->dato.mejor_puntaje) {
            jugador_actual->dato.mejor_puntaje = puntaje_partida;
        }

        tinfo_ranking info_r;
        strcpy(info_r.alias, jugador_actual->dato.alias);
        info_r.puntaje = puntaje_partida;
        
        pnodo_ranking nuevo_ranking;
        crearnodo(nuevo_ranking, info_r);
        if(nuevo_ranking != NULL) {
            agregar_ranking(ranking, nuevo_ranking);
            cout << "Tu puntaje ha sido anadido al ranking de Vencedores." << endl;
        }
    } else {
        cout << "--- HAS PERDIDO ---" << endl;
        cout << "La princesa sigue atrapada. Tu puntaje de " << puntaje_partida << " se ha perdido." << endl;
    }
}

pjugador seleccionarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    pjugador jugador_seleccionado = NULL;
    bool valido = false;
    
    while (!valido) {
        limpiarPantalla();
        cout << "--- SELECCIONAR JUGADOR ---" << endl;
        cout << "Jugadores disponibles:" << endl;
        listar_jugadores(arbol_jugadores);
        cout << "----------------------------------------" << endl;
        leerCadenaValidada("Ingrese el Alias del jugador (o 'SALIR'): ", alias_buscado, 1);

        if (strcmp(alias_buscado, "SALIR") == 0) {
            return NULL;
        }

        jugador_seleccionado = buscar_jugador(arbol_jugadores, alias_buscado);
        if (jugador_seleccionado != NULL) {
            cout << "Jugador seleccionado: " << jugador_seleccionado->dato.alias << endl;
            valido = true;
        } else {
            cout << "Alias no encontrado. Intente de nuevo." << endl;
            pausarPantalla();
        }
    }
    pausarPantalla();
    return jugador_seleccionado;
}

void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego, int &conteo) {
    iniciarpila(pila_juego);
    int total_palabras = contarPalabras(dic);
    
    for (int i = 0; i < 6; i++) {
        int random_index = rand() % total_palabras;
        int k = 0;
        bool encontrada = false;

        for (int j = 0; j < MAX_CLAVES && !encontrada; j++) {
            pnodo_palabra p = dic[j].listado.inicio;
            while (p != NULL && !encontrada) {
                if (k == random_index) {
                    if (topepila(pila_juego).longitud != p->dato.longitud) {
                        agregarpila(pila_juego, p->dato);
                        conteo++;
                        encontrada = true;
                    } else {
                        random_index = (random_index + 1) % total_palabras;
                    }
                }
                k++;
                p = p->sig;
            }
        }
    }
}

bool jugarPalabra(tpalabra &palabra_actual, int &puntaje_partida) {
    int intentos = 3;
    bool adivinada = false;
    bool pistas_usadas[4] = {false, false, false, false}; 
    tcad intento_palabra;

    while (intentos > 0 && adivinada == false) {
        cout << "\nPalabra Oculta. Intentos restantes: " << intentos << endl;
        cout << "Puntaje actual: " << puntaje_partida << endl;
        cout << "--- PISTAS DISPONIBLES ---" << endl;
        cout << "1. Cantidad de letras (Costo: 2 pts) " << (pistas_usadas[0] ? "(Usada)" : "") << endl;
        cout << "2. Primera letra (Costo: 3 pts) " << (pistas_usadas[1] ? "(Usada)" : "") << endl;
        cout << "3. Definicion (Costo: 4 pts) " << (pistas_usadas[2] ? "(Usada)" : "") << endl;
        cout << "4. Sinonimo (Costo: 5 pts) " << (pistas_usadas[3] ? "(Usada)" : "") << endl;
        cout << "5. Adivinar la palabra" << endl;
        cout << "0. Rendirse (Pierdes el juego)" << endl;
        
        int opc;
        cout << "Elija una opcion: ";
        cin >> opc;
        
        int costo_pista = 0;
        switch(opc) {
            case 1: costo_pista = 2;
                if (puntaje_partida >= costo_pista) {
                    puntaje_partida -= costo_pista;
                    cout << "PISTA: La palabra tiene " << palabra_actual.longitud << " letras." << endl;
                    pistas_usadas[0] = true;
                } else { cout << "Puntos insuficientes." << endl; }
                break;
            case 2: costo_pista = 3;
                if (puntaje_partida >= costo_pista) {
                    puntaje_partida -= costo_pista;
                    cout << "PISTA: La primera letra es '" << palabra_actual.palabra[0] << "'" << endl;
                    pistas_usadas[1] = true;
                } else { cout << "Puntos insuficientes." << endl; }
                break;
            case 3: costo_pista = 4;
                if (puntaje_partida >= costo_pista) {
                    puntaje_partida -= costo_pista;
                    cout << "PISTA (Definicion): " << palabra_actual.definicion << endl;
                    pistas_usadas[2] = true;
                } else { cout << "Puntos insuficientes." << endl; }
                break;
            case 4: costo_pista = 5;
                if (puntaje_partida >= costo_pista) {
                    puntaje_partida -= costo_pista;
                    cout << "PISTA (Sinonimo): " << palabra_actual.sinonimo << endl;
                    pistas_usadas[3] = true;
                } else { cout << "Puntos insuficientes." << endl; }
                break;
            case 5:
                leerCadenaValidada("Adivina la palabra: ", intento_palabra, 1);
                if (strcmp(intento_palabra, palabra_actual.palabra) == 0) {
                    adivinada = true;
                } else {
                    cout << "Incorrecto." << endl;
                    intentos--;
                }
                break;
            case 0:
                intentos = 0;
                break;
            default:
                cout << "Opcion incorrecta." << endl;
                break;
        }
        if (opc > 0 && opc < 5) pausarPantalla();
    }
    return adivinada;
}


// --- MÓDULO 4: VENCEDORES ---

void mostrarVencedores(tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- RANKING DE VENCEDORES ---" << endl;
    
    if (ranking.inicio == NULL) {
        cout << "Aun no hay vencedores en el ranking." << endl;
        return;
    }

    char orden;
    cout << "Elija el orden (d=decreciente, c=creciente): ";
    cin >> orden;

    if (orden == 'c') {
        cout << "\n--- Orden Creciente (Menor a Mayor) ---" << endl;
        mostrarlista(ranking, true);
    } else {
        cout << "\n--- Orden Decreciente (Mayor a Menor) ---" << endl;
        mostrarlista(ranking, false);
    }
    
    liberarlista(ranking);
    cout << "\n(El ranking se ha reiniciado como pide la consigna)" << endl;
}

#endif // MODULOS_HPP*/
