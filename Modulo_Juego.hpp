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
//  ABB (Busqueda de Nodos) 
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
			        
				// usa la funcion auxiliar para lectura de ingreso
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
	    // Arreglo estatico de indices para las 6 palabras a seleccionar.
		indices in; 
	    int indice_aleatorio;
	    int indices_encontrados = 0;
	    
		    // Generar 6 indices aleatorios unicos
		    srand(time(NULL)); 
			    
			    while (indices_encontrados < 6) { 
				        indice_aleatorio = rand() % totalPalabras;
				        bool repetido = false;
				        
					        // Verificar repeticion de indice
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
			    
					       // recorre el diccionario para buscar las palabras por indice
					       
					       int indice_global = 0;
			    int palabras_cargadas_pila = 0;
			    pnodo_palabra p;
			    
				    // Arreglo estatico para sostener las 6 palabras encontradas
				    tpalabra palabras_a_apilar[6]; 
					    
					    // Recorremos el diccionario (Arreglo de Listas)
					    for (int i = 0; i < MAX_CLAVES; i++) {
						        p = dic[i].listado.inicio;
						        while (p != NULL) { 
							            // Buscamos si el indice global coincide con uno de los 6 indices aleatorios
								            for (int j = 0; j < 6; j++) {
									                if (in[j] == indice_global) {
										                    // Si coincide, guardamos la palabra
											                    palabras_a_apilar[palabras_cargadas_pila] = p->dato;
										                    palabras_cargadas_pila++;
										                }
									            }
								            
									            indice_global++;
								            p = p->sig;
								        }
						    }
					    
						    // 3. Cargar las 6 palabras encontradas en la pila (para el orden LIFO del juego)
						    for (int i = 0; i < 6; i++) {
							        agregarpila(pila_juego, palabras_a_apilar[i]);
							    }
}

// Muestra la interfaz de adivinanza con puntajes y pistas.
void mostrarMenuAdivinar(int puntaje, int intentos, tpistas pistas_usadas, tpalabra palabra_actual) {
	    cout << "---  ADIVINA LA PALABRA  ---" << endl;
	    cout << "Puntaje Actual: " << puntaje << endl;
	    cout << "Intentos Restantes: " << intentos << endl;
	
	    cout << "\nPistas Usadas:" << endl;
	    if (pistas_usadas[0]) cout << " - Longitud: " << palabra_actual.longitud << " caracteres" << endl;
	    if (pistas_usadas[1]) cout << " - Primera Letra: " << palabra_actual.palabra[0] << endl;
	    if (pistas_usadas[2]) cout << " - Definicion: " << palabra_actual.definicion << endl;
	    if (pistas_usadas[3]) cout << " - Sinonimo: " << palabra_actual.sinonimo << endl;
	
	    cout << "\nOpciones:" << endl;
	    cout << "  (A)divinar la palabra" << endl;
	    cout << "  (P)edir una pista" << endl;
	    cout << "Opcion: ";
}

// Muestra el submenu de pistas y sus costos.
void mostrarMenuPistas() {
	    cout << "\n--- PISTAS DISPONIBLES ---" << endl;
	    cout << "1. Cantidad de Letras (Costo: 2 puntos)" << endl;
	    cout << "2. Primera Letra (Costo: 3 puntos)" << endl;
	    cout << "3. Definicion (Costo: 4 puntos)" << endl;
	    cout << "4. Sinonimo (Costo: 5 puntos)" << endl;
	    cout << "0. Cancelar" << endl;
	    cout << "Elige pista: ";
}

// Contiene la logica de interaccion para adivinar una sola palabra.
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
		        while ((c = getchar()) != '\n'); // Limpia buffer despues del cin >> opcion
		        
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
				// Arreglo nativo para costos (correcion de la asignacion ilegal de typedef)
				            costos costos_pistas = {2, 3, 4, 5}; 
							
				            if (idx >= 0 && idx < 4) {
					                int c = costos_pistas[idx];
					
					                if (!pistas_usadas[idx] && puntaje_partida >= c) {
						                    puntaje_partida -= c;
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

// Funcion principal que coordina el flujo de la partida completa.
void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking) {
	    limpiarPantalla();
	    cout << "--- INICIAR JUEGO ---" << endl;
	    
		    int total_jugadores = contar_jugadores(arbol_jugadores);
	    int total_palabras = contar_palabras(dic);
	
	    // Minimo 2 jugadores y 6 palabras
		    if (total_jugadores < 2) {
			        cout << "No hay suficientes jugadores registrados (minimo 2). Registra mas jugadores." << endl;
			    }
		    if (total_palabras < 6) {
			        cout << "No hay suficientes palabras registradas (minimo 6). Agrega mas palabras." << endl;
			    }
		    
				    pjugador jugador_seleccionado = seleccionarJugador(arbol_jugadores);
		    if (jugador_seleccionado == NULL) {
			        cout << "Inicio de juego cancelado." << endl;
			    }
		    
				    cout << "Suerte, " << jugador_seleccionado->dato.alias << "! La princesa Karym Su Yang cuenta contigo." << endl;
		    pausarPantalla();
		
		    tpila pila_juego;
		    iniciarpila(pila_juego);
		    seleccionarPalabrasAleatorias(dic, pila_juego, total_palabras);
		
		    int puntaje_partida = 7; // 7 puntos obsequiados al inicio
		    bool gano_partida = true;
		    int palabras_adivinadas = 0;
		
		    while (!pilavacia(pila_juego) && gano_partida == true) { 
			        tpalabra palabra_actual = quitarpila(pila_juego);
			        palabras_adivinadas++;
			        
				        cout << "\n--- Preparando Joya " << palabras_adivinadas << " de 6 ---" << endl;
			        pausarPantalla();
			
			        bool adivino_esta_palabra = jugarPalabra(palabra_actual, puntaje_partida);
			
			        if (adivino_esta_palabra) {
				            cout << "Correcto! La palabra era: " << palabra_actual.palabra << endl;
				            cout << "Has ganado 7 puntos." << endl;
				            puntaje_partida += 7; // 7 puntos por palabra
				        } else {
				            // Condicion de Game Over (Rompe el bucle con la bandera gano_partida = false)
					            cout << "HAS FALLADO! La palabra correcta era: " << palabra_actual.palabra << endl;
				            cout << "La guardiana del espejo te convierte en piedra..." << endl;
				            gano_partida = false;
				        }
			    }
		
		    limpiarPantalla();
		    if (gano_partida) { // VICTORIA
				        
				        jugador_seleccionado->dato.juegos_ganados++;
			        jugador_seleccionado->dato.puntaje_acumulado += puntaje_partida;
			// Verificar que el jugador se quede con el mayor puntaje (Mejor Puntaje)
			        if (puntaje_partida > jugador_seleccionado->dato.mejor_puntaje) {
				            jugador_seleccionado->dato.mejor_puntaje = puntaje_partida;
				        }
			    } else { // DERROTA
			        // Puntaje Final: 0 (No se actualizan ni se guardan puntajes)
				        cout << "*****************************************************" << endl;
			        cout << "                 GAME OVER" << endl;
			        cout << "Has sido convertido en piedra." << endl;
			        cout << "Puntaje Final: 0" << endl;
			        cout << "*****************************************************" << endl;
			    }
}

// Recorrido recursivo del ABB para construir la Lista de Ranking.
// ABB (Recorrido En-Orden 
void construir_ranking(pjugador arbol, tlista_ranking &lista) {
	    if (arbol == NULL) {
		        cout<<"vacio"; 
		    }
	    
			    construir_ranking(arbol->izq, lista);
	    
		    if (arbol->dato.juegos_ganados > 0) { // Solo si gano al menos un juego
			        tinfo_ranking info;
			        info.puntaje = arbol->dato.mejor_puntaje; 
				        strcpy(info.alias, arbol->dato.alias);
			        
				        pnodo_ranking nuevo;
			        crearnodo_ranking(nuevo, info); 
				        if (nuevo != NULL) {
					            agregar_ranking(lista, nuevo); // Agrega a la Lista Doble Circular de forma ordenada
					        }
				    }
		    
				    construir_ranking(arbol->der, lista);
}

// Funcion coordinadora para mostrar el ranking de vencedores.
//  Ranking (Coordinacion).
void mostrarVencedores(pjugador arbol_jugadores, tlista_ranking &ranking) {
	    limpiarPantalla();
	    cout << "---  VENCEDORES (Ranking por Mejor Puntaje)  ---" << endl;
	
	    liberarlista(ranking); // Libera la lista antes de construirla
	    construir_ranking(arbol_jugadores, ranking); 
	
	    char orden_op;
	    cout << "\nVer ranking en orden:" << endl;
	    cout << "  (D)ecreciente (Mejor primero)" << endl;
	    cout << "  (C)reciente (Peor primero)" << endl;
	    cout << "Opcion: ";
	    cin >> orden_op;
	    
		    bool creciente = (orden_op == 'c' || orden_op == 'C');
	
	    cout << "\n--- RANKING ---" << endl;
	    mostrarlista(ranking, creciente); 
		
		    liberarlista(ranking); // Libera la lista despues de mostrar 
	    cout << "\n(Ranking liberado de memoria.)" << endl;
}
