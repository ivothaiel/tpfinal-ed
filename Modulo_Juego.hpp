#include <iostream>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;

const int PISTAS = 4;
typedef bool tpistas[PISTAS];
typedef int costos[4];
typedef int indices[7];

// Muestra una lista de los jugadores disponibles para empezar a jugar
void jugadores_disponibles(pjugador jugadores){
	limpiarPantalla();
	cout << "\n=============== LISTA DE JUGADORES ===============\n";
	mostrar_jugadores(jugadores);
}

// Permite al jugador selccionar un jugador para iniciar la partida
void seleccion_jugador(pjugador jugadores, pjugador &seleccionado){
	tcad alias;
	bool salir = false;
	while(seleccionado == NULL && !salir){
		limpiarPantalla();
		jugadores_disponibles(jugadores);
		cout << "\n> Ingrese Alias del Jugador - '0' para Cancelar: ";
		leer_ingreso(alias);
		if(strcmp(alias, "0") == 0){
			salir = true;
			juego_cancelado();
		}
		else{
			seleccionado = buscar_jugador(jugadores, alias);
			if(seleccionado == NULL){
				cout << "\nEl alias '" << alias << "' no corresponde a ningun jugador. Intente nuevamente" << endl;
				pausarPantalla();
			}
		}
	}
}

// Devuelve true si el indice aleatorio ya existe dentro del arreglo 'ind'
// Recorre unicamente los elementos cargados hasta el momento (encontrados)
// evitando seleccionar indices repetidos
bool indice_repetido(indices ind, int encontrados, int aleatorio){
	int j;
	for(j = 0; j < encontrados; j++){
		if(ind[j] == aleatorio)
			return true;
	}
	return false;
}

// Selecciona 6 palabras aleatorias del diccionario sin repeticion y las carga en la Pila
// TDA Diccionario/Pila
void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego) {
    indices in;
    int indice_aleatorio;
    int indices_encontrados = 0;
	int total_palabras = contar_palabras(dic);

    // Generar 6 indices aleatorios unicos
    while (indices_encontrados < 6) {
        indice_aleatorio = rand() % total_palabras;
		
        if (indice_repetido(in, indices_encontrados, indice_aleatorio) == false) {
            in[indices_encontrados] = indice_aleatorio;
            indices_encontrados++;
        }
    }

    int indice_global = 0;
    int palabras_cargadas = 0;
    pnodo_palabra p;

    tpalabra pila_palabras[6];

	// Ahorro de iteraciones extra
    for (int i = 0; i < MAX_CLAVES && palabras_cargadas < 6; i++) {
        
		p = dic[i].listado.inicio;
		// Evita seguir buscando cuando ya se agregaron las 6 palabras
        while (p != NULL && palabras_cargadas < 6) {
			
            for (int j = 0; j < 6; j++) {
                if (in[j] == indice_global) {
                    pila_palabras[palabras_cargadas] = p->dato;
                    palabras_cargadas++;
                }
            }
            indice_global++;
            p = p->sig;
        }
    }

    // Cargar palabras en la pila en orden LIFO
    for (int i = 0; i < MAXPILA; i++) {
        agregar_pila(pila_juego, pila_palabras[i]);
    }
}

// Muestra interfaz de adivinanza con puntajes y pistas
void mostrarMenuAdivinar(int puntaje, int intentos, int adivinadas, tpistas pistas_usadas, 
	tpalabra actual, char &op) {
	limpiarPantalla();
	cout << "\n	   J O Y A  " << adivinadas + 1 << "  D E  6" << endl;
	cout << endl;
	cout << "+---------------------------------------+\n";
	cout << "|   A D I V I N A  L A  P A L A B R A   |\n"; 
	cout << "+---------------------------------------+\n";
    cout << " Puntaje Actual: " << puntaje  << " puntos" << endl;
    cout << " Intentos Restantes: " << intentos << " intentos" << endl;

    cout << "\n Pistas Usadas:" << endl;
    if (pistas_usadas[0]) cout << " - Longitud: " << actual.longitud << " caracteres" << endl;
    if (pistas_usadas[1]) cout << " - Primer Letra: " << actual.palabra[0] << endl;
    if (pistas_usadas[2]) cout << " - Definicion: " << actual.definicion << endl;
    if (pistas_usadas[3]) cout << " - Sinonimo: " << actual.sinonimo << endl;

    cout << "\n 1) Adivinar la Palabra" << endl;
    cout << " 2) Pedir una Pista" << endl;
    cout << "\n > Opcion: ";
	cin >> op;
}

// Submenu de pistas
void mostrarMenuPistas(char &op) {
	cout << "\n";
	cout << " +---------------------------------------+\n";
	cout << " |        * Pistas Disponibles *         |\n";
	cout << " +---------------------------------------+\n\n";
    cout << "  1) Cantidad de Letras - 2 puntos" << endl;
    cout << "  2) Primer Letra - 3 puntos" << endl;
    cout << "  3) Definicion - 4 puntos" << endl;
    cout << "  4) Sinonimo - 5 puntos" << endl;
    cout << "\n> Opcion: ";
	cin >> op;
}

// Verifica que las palabras sean iguales
bool palabra_adivinada(tcad actual, tcad intento){
	return strcmp(intento, actual) == 0;
}
	
void elegir_pistas(tpistas &pistas_usadas, int &puntaje, char op){
	costos costos_pistas = {2, 3, 4, 5};
	int indice = op - '1';
	if(indice >= 0 && indice < 4){
		int costo = costos_pistas[indice];
		if(!pistas_usadas[indice] && puntaje >= costo){
			puntaje -= costo;
			pistas_usadas[indice] = true;
		}else{
			if(pistas_usadas[indice])
				cout << "\nYa has usado esta pista" << endl;
			if(puntaje < costo)
				cout << "\nNo tienes puntos suficientes para usar la pista" << endl;
		}
	}
	else
		cout << "\nOPCION INVALIDA" << endl;
	pausarPantalla();
}

// Logica de jugar una palabra
void jugar_palabra(tpalabra &actual, int &puntaje, bool &adivinada, int adivinadas) {
    tcad intento;
    int intentos = 3;
    tpistas pistas_usadas = {false, false, false, false};
    char opcion;
    while (intentos > 0 && !adivinada) {
        mostrarMenuAdivinar(puntaje, intentos, adivinadas, pistas_usadas, actual, opcion);
        
		limpiar_buffer();
		
        if (opcion == '1') {
            leerCadenaValidada("\nIngresa tu Respuesta: ", intento, 1);
			// Controla que siempre la primer letra sea mayuscula
			// para una comparacion correcta
			convertir_letra(intento[0]);
			adivinada = palabra_adivinada(actual.palabra, intento);
			if(!adivinada){
				cout << "\nNo ha adivinado la palabra. Intente nuevamente" << endl;
				intentos--;
				pausarPantalla();
			}
        }else if (opcion == '2') {
            mostrarMenuPistas(opcion);
			elegir_pistas(pistas_usadas, puntaje, opcion);
			limpiarPantalla();
        }
		else{
			cout << "\nOPCION INVALIDA" << endl;
			pausarPantalla();
		}
    }
}

// Actualiza el puntaje del jugador despues de ganar la partida
void actualizar_puntaje(pjugador &seleccionado, int puntaje){
	seleccionado->dato.juegos_ganados++;
	seleccionado->dato.puntaje_acumulado += puntaje;
	if (puntaje > seleccionado->dato.mejor_puntaje) {
		seleccionado->dato.mejor_puntaje = puntaje;
	}
}

// Coordina toda la partida
void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking) {
	pjugador seleccionado = NULL;
	
	cartel_inicio_juego();
	
	seleccion_jugador(arbol_jugadores, seleccionado);
	
	if(seleccionado != NULL){
		
		bienvenida(seleccionado->dato.alias);
		
		tpila pila_juego;
		iniciar_pila(pila_juego);
		seleccionarPalabrasAleatorias(dic, pila_juego);
		
		int puntaje_partida = 7;
		bool victoria = true;
		int palabras_adivinadas = 0;
		
		while (!pila_vacia(pila_juego) && victoria) {
			tpalabra palabra_actual = quitar_pila(pila_juego);
			
			bool adivinada = false;
			jugar_palabra(palabra_actual, puntaje_partida, adivinada, palabras_adivinadas);
			
			if (adivinada) {
				cout << "\n¡ C O R R E C T O ! La Palabra era: " << palabra_actual.palabra << endl;
				cout << "\n¡ G A N A S T E  7  P U N T O S !" << endl;
				puntaje_partida += 7;
				palabras_adivinadas++;
			} else {
				limpiarPantalla();
				cout << "\n¡ H A S  F A L L A D O ! La Palabra Correcta era: " << palabra_actual.palabra << endl;
				cartel_derrota();
				victoria = false;
			}
			pausarPantalla();
		}
		
		if (victoria){
			cartel_victoria();
			actualizar_puntaje(seleccionado, puntaje_partida);
		}
	}
}

// Construye ranking (recorrido en orden)
void construir_ranking(pjugador arbol, tlista_ranking &lista) {
    if (arbol == NULL) return;

    construir_ranking(arbol->izq, lista);

    if (arbol->dato.juegos_ganados > 0) {
        tinfo_ranking info;
        info.puntaje = arbol->dato.mejor_puntaje;
        strcpy(info.alias, arbol->dato.alias);

        pnodo_ranking nuevo;
        crearnodo_ranking(nuevo, info);

        if (nuevo != NULL) {
            agregar_ranking(lista, nuevo);
        }
    }

    construir_ranking(arbol->der, lista);
}

// Muestra Ranking
void mostrarVencedores(pjugador arbol_jugadores, tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- VENCEDORES (Ranking) ---" << endl;

    liberarlista(ranking);
    construir_ranking(arbol_jugadores, ranking);

    char orden_op;
    cout << "\nVer ranking en orden:" << endl;
    cout << " (D)ecreciente" << endl;
    cout << " (C)reciente" << endl;
    cout << "Opcion: ";
    cin >> orden_op;

    bool creciente = (orden_op == 'c' || orden_op == 'C');

    cout << "\n--- RANKING ---" << endl;
    mostrarlista(ranking, creciente);

    liberarlista(ranking);
    cout << "\n(Ranking liberado.)" << endl;
}
