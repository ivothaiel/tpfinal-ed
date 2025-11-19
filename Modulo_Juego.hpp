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

// Permite al jugador seleccionar un alias existente para iniciar la partida.
// ABB (Busqueda de Nodos)
pjugador seleccionarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    pjugador jugador_encontrado = NULL;
    bool salir = false;

    while (jugador_encontrado == NULL && !salir) {
        limpiarPantalla();
        cout << "--- SELECCIONAR JUGADOR ---" << endl;
        cout << "Jugadores disponibles:" << endl;
        listar_jugadores(arbol_jugadores);

        cout << "\nIngrese el alias del jugador (o '0' para cancelar): ";

        // Lectura segura
        leer_ingreso(alias_buscado);

        if (strcmp(alias_buscado, "0") == 0) {
            salir = true;
        } else {
            jugador_encontrado = buscar_jugador(arbol_jugadores, alias_buscado);
            if (jugador_encontrado == NULL) {
                cout << "Alias no encontrado. Intente de nuevo." << endl;
                pausarPantalla();
            }
        }
    }

    return jugador_encontrado;
}

// Selecciona 6 palabras aleatorias del diccionario sin repeticion y las carga en la Pila.
// TDA Diccionario/Pila
void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego, int totalPalabras) {
    indices in;
    int indice_aleatorio;
    int indices_encontrados = 0;

    srand(time(NULL));

    // Generar 6 indices aleatorios unicos
    while (indices_encontrados < 6) {
        indice_aleatorio = rand() % totalPalabras;
        bool repetido = false;

        for (int j = 0; j < indices_encontrados; j++) {
            if (in[j] == indice_aleatorio) {
                repetido = true;
            }
        }

        if (!repetido) {
            in[indices_encontrados] = indice_aleatorio;
            indices_encontrados++;
        }
    }

    int indice_global = 0;
    int palabras_cargadas_pila = 0;
    pnodo_palabra p;

    tpalabra palabras_a_apilar[6];

    for (int i = 0; i < MAX_CLAVES; i++) {
        p = dic[i].listado.inicio;
        while (p != NULL) {
            for (int j = 0; j < 6; j++) {
                if (in[j] == indice_global) {
                    palabras_a_apilar[palabras_cargadas_pila] = p->dato;
                    palabras_cargadas_pila++;
                }
            }
            indice_global++;
            p = p->sig;
        }
    }

    // Cargar palabras en la pila en orden LIFO
    for (int i = 0; i < 6; i++) {
        agregarpila(pila_juego, palabras_a_apilar[i]);
    }
}

// Muestra interfaz de adivinanza con puntajes y pistas
void mostrarMenuAdivinar(int puntaje, int intentos, tpistas pistas_usadas, tpalabra palabra_actual) {
    cout << "--- ADIVINA LA PALABRA ---" << endl;
    cout << "Puntaje Actual: " << puntaje << endl;
    cout << "Intentos Restantes: " << intentos << endl;

    cout << "\nPistas Usadas:" << endl;
    if (pistas_usadas[0]) cout << " - Longitud: " << palabra_actual.longitud << " caracteres" << endl;
    if (pistas_usadas[1]) cout << " - Primera Letra: " << palabra_actual.palabra[0] << endl;
    if (pistas_usadas[2]) cout << " - Definicion: " << palabra_actual.definicion << endl;
    if (pistas_usadas[3]) cout << " - Sinonimo: " << palabra_actual.sinonimo << endl;

    cout << "\nOpciones:" << endl;
    cout << " (A)divinar la palabra" << endl;
    cout << " (P)edir una pista" << endl;
    cout << "Opcion: ";
}

// Submenu de pistas
void mostrarMenuPistas() {
    cout << "\n--- PISTAS DISPONIBLES ---" << endl;
    cout << "1. Cantidad de Letras (Costo: 2 puntos)" << endl;
    cout << "2. Primera Letra (Costo: 3 puntos)" << endl;
    cout << "3. Definicion (Costo: 4 puntos)" << endl;
    cout << "4. Sinonimo (Costo: 5 puntos)" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Elige pista: ";
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
            leerCadenaValidada("Ingresa tu respuesta: ", intento_palabra, 1);

            if (strcmp(intento_palabra, palabra_actual.palabra) == 0) {
                adivinada = true;
            } else {
                intentos--;
                pausarPantalla();
            }
        }

        else if (opcion == 'p' || opcion == 'P') {
            mostrarMenuPistas();
            cin >> opcion;

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
    limpiarPantalla();
    cout << "--- INICIAR JUEGO ---" << endl;

    int total_jugadores = contar_jugadores(arbol_jugadores);
    int total_palabras = contar_palabras(dic);

    if (total_jugadores < 2) {
        cout << "No hay suficientes jugadores (minimo 2)." << endl;
    }
    if (total_palabras < 6) {
        cout << "No hay suficientes palabras (minimo 6)." << endl;
    }

    pjugador jugador_seleccionado = seleccionarJugador(arbol_jugadores);
    if (jugador_seleccionado == NULL) {
        cout << "Inicio cancelado." << endl;
        return;
    }

    cout << "Suerte, " << jugador_seleccionado->dato.alias << "!" << endl;
    pausarPantalla();

    tpila pila_juego;
    iniciarpila(pila_juego);
    seleccionarPalabrasAleatorias(dic, pila_juego, total_palabras);

    int puntaje_partida = 7;
    bool gano_partida = true;
    int palabras_adivinadas = 0;

    while (!pilavacia(pila_juego) && gano_partida) {
        tpalabra palabra_actual = quitarpila(pila_juego);
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
            gano_partida = false;
        }
    }

    limpiarPantalla();

    if (gano_partida) {
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
