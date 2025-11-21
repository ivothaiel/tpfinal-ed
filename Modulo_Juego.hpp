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
	cout << "\n=============== LISTA DE JUGADORES ===============\n";
	mostrar_jugadores(jugadores);
}

// Permite al jugador seleccionar un alias existente para iniciar la partida
// ABB (Busqueda de Nodos)
pjugador seleccionarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    pjugador jugador_encontrado = NULL;
    bool salir = false;

    while (jugador_encontrado == NULL && !salir) {
        limpiarPantalla();
		
		jugadores_disponibles(arbol_jugadores);
        cout << "\n> Ingrese Alias del Jugador - '0' para Cancelar: ";
		
        // Lectura segura
        leer_ingreso(alias_buscado);
		
        if (strcmp(alias_buscado, "0") == 0) {
            salir = true;
        } else {
            jugador_encontrado = buscar_jugador(arbol_jugadores, alias_buscado);
            if (jugador_encontrado == NULL) {
				cout << "\nEl alias '" << alias_buscado 
					<< "' no corresponde a ningun jugador. Intente nuevamente" << endl;
                pausarPantalla();
            }
        }
    }

    return jugador_encontrado;
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

// Selecciona 6 palabras aleatorias del diccionario sin repeticion y las carga en la Pila.
// TDA Diccionario/Pila
void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego, int totalPalabras) {
    indices in;
    int indice_aleatorio;
    int indices_encontrados = 0;

    // Generar 6 indices aleatorios unicos
    while (indices_encontrados < 6) {
        indice_aleatorio = rand() % totalPalabras;
		
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
void mostrarMenuAdivinar(int puntaje, int intentos, tpistas pistas_usadas, tpalabra palabra_actual) {
    //cout << "--- ADIVINA LA PALABRA ---" << endl;
	cout << endl;
	cout << "+---------------------------------------+\n";
	cout << "|   A D I V I N A  L A  P A L A B R A   |\n"; 
	cout << "+---------------------------------------+\n";
    cout << "Puntaje Actual: " << puntaje  << " puntos" << endl;
    cout << "Intentos Restantes: " << intentos << " intentos" << endl;

    cout << "\nPistas Usadas:" << endl;
    if (pistas_usadas[0]) cout << " - Longitud: " << palabra_actual.longitud << " caracteres" << endl;
    if (pistas_usadas[1]) cout << " - Primer Letra: " << palabra_actual.palabra[0] << endl;
    if (pistas_usadas[2]) cout << " - Definicion: " << palabra_actual.definicion << endl;
    if (pistas_usadas[3]) cout << " - Sinonimo: " << palabra_actual.sinonimo << endl;

    //cout << "\nOpciones:" << endl;
    cout << " Adivinar la Palabra (a)" << endl;
    cout << " Pedir una Pista (p)" << endl;
    cout << "\n> Opcion: ";
}

// Submenu de pistas
void mostrarMenuPistas(char &op) {
	cout << "\n";
	cout << " +---------------------------------------+\n";
	cout << " |        * Pistas Disponibles *          |\n";
	cout << " +---------------------------------------+\n\n";
    cout << "  1) Cantidad de Letras (Costo: 2 puntos)" << endl;
    cout << "  2) Primera Letra (Costo: 3 puntos)" << endl;
    cout << "  3) Definicion (Costo: 4 puntos)" << endl;
    cout << "  4) Sinonimo (Costo: 5 puntos)" << endl;
    cout << "  0) Cancelar" << endl;
    cout << "\n> Opcion: ";
	cin >> op;
}

// Logica de jugar una palabra
bool jugarPalabra(tpalabra &palabra_actual, int &puntaje_partida) {
    tcad intento_palabra;
    int intentos = 3;
    bool adivinada = false;
    tpistas pistas_usadas = {false, false, false, false};
    char opcion;

    while (intentos > 0 && !adivinada) {
        limpiarPantalla();
        mostrarMenuAdivinar(puntaje_partida, intentos, pistas_usadas, palabra_actual);
        cin >> opcion;
        
		int c;
        while ((c = getchar()) != '\n');
		
        if (opcion == 'a' || opcion == 'A') {
            leerCadenaValidada("Ingresa tu Respuesta: ", intento_palabra, 1);
			
            if (strcmp(intento_palabra, palabra_actual.palabra) == 0) {
                adivinada = true;
            } else {
                intentos--;
                pausarPantalla();
            }
        }else if (opcion == 'p' || opcion == 'P') {
            mostrarMenuPistas(opcion);
            //cin >> opcion;
			
            int idx = opcion - '1';
			
            costos costos_pistas = {2, 3, 4, 5};
			
            if (idx >= 0 && idx < 4) {
                int costo = costos_pistas[idx];

                if (!pistas_usadas[idx] && puntaje_partida >= costo) {
                    puntaje_partida -= costo;
                    pistas_usadas[idx] = true;
                } else {
                    cout << "No tienes puntos suficientes o ya usaste esa pista." << endl;
                    pausarPantalla();
                }
            }
        }
    }

    return adivinada;
}

// Coordina toda la partida
void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking) {

    int total_jugadores = contar_jugadores(arbol_jugadores);
    int total_palabras = contar_palabras(dic);

    if (total_jugadores < 2) {
        cout << "\nDebe registrar al menos 2 jugadores para iniciar el juego" << endl;
		return;
    }
    if (total_palabras < 6) {
        cout << "\nDebe registrar al menos 6 palabras para iniciar el juego" << endl;
		return;
    }

	limpiarPantalla();
	cartel_inicio_juego();
	
    pjugador jugador_seleccionado = seleccionarJugador(arbol_jugadores);
    if (jugador_seleccionado == NULL) {
        juego_cancelado();
        return;
    }

    bienvenida(jugador_seleccionado->dato.alias);
    
	tpila pila_juego;
    iniciar_pila(pila_juego);
    seleccionarPalabrasAleatorias(dic, pila_juego, total_palabras);

    int puntaje_partida = 7;
    bool victoria = true;
    int palabras_adivinadas = 0;

    while (!pila_vacia(pila_juego) && victoria) {
        tpalabra palabra_actual = quitar_pila(pila_juego);
        palabras_adivinadas++;
		
        cout << "\n--- Preparando palabra " << palabras_adivinadas << " de 6 ---" << endl;
        pausarPantalla();
		
        bool adivino = jugarPalabra(palabra_actual, puntaje_partida);
		
        if (adivino) {
            cout << "Correcto! La palabra era: " << palabra_actual.palabra << endl;
            cout << "Ganas 7 puntos." << endl;
            puntaje_partida += 7;
        } else {
            cout << "HAS FALLADO! La palabra correcta era: " << palabra_actual.palabra << endl;
            cout << "GAME OVER" << endl;
            victoria = false;
        }
    }

    limpiarPantalla();

    if (victoria) {
        jugador_seleccionado->dato.juegos_ganados++;
        jugador_seleccionado->dato.puntaje_acumulado += puntaje_partida;

        if (puntaje_partida > jugador_seleccionado->dato.mejor_puntaje) {
            jugador_seleccionado->dato.mejor_puntaje = puntaje_partida;
        }
    } else {
        cout << "Puntaje Final: 0" << endl;
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
