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

// ------------------------------------------------------------
// SECCIÓN: SELECCIÓN DE JUGADOR
// ------------------------------------------------------------

void jugadores_disponibles(pjugador jugadores){
    limpiarPantalla();
    cout << "\n=============== LISTA DE JUGADORES ===============\n";
    mostrar_jugadores(jugadores);
}

void seleccion_jugador(pjugador jugadores, pjugador &seleccionado){
    tcad alias;
    bool salir = false;
    while(seleccionado == NULL && salir == false){
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
                cout << "\nEl alias '" << alias 
                     << "' no corresponde a ningun jugador." << endl;
                cout << "Intente nuevamente." << endl;
                pausarPantalla();
            }
        }
    }
}

// Devuelve true si el indice aleatorio ya existe
bool indice_repetido(indices ind, int encontrados, int aleatorio){
    bool repetido = false;
    int j = 0;
    while(j < encontrados && repetido == false){
        if(ind[j] == aleatorio){
            repetido = true;
        }
        j++;
    }
    return repetido;
}

void generar_indices_azar(int total, indices &in) {
    int usados = 0;
    int aleatorio;

    // Inicializar
    for (int i = 0; i < 7; i++) in[i] = -1;

    while (usados < 6) {
        aleatorio = rand() % total;

        bool repetido = false;
        for (int j = 0; j < usados; j++)
            if (in[j] == aleatorio)
                repetido = true;

        if (!repetido) {
            in[usados] = aleatorio;
            usados++;
        }
    }
}


bool obtener_palabra_por_indice(tdiccionario dic, int buscado, tpalabra &out) {
    int indice_actual = 0;
    bool encontrado = false;
    int i = 0;
    pnodo_palabra p;

    while (i < MAX_CLAVES && encontrado == false) {
        p = dic[i].listado.inicio;

        while (p != NULL && encontrado == false) {
            if (indice_actual == buscado) {
                out = p->dato;
                encontrado = true;
            } else {
                indice_actual++;
                p = p->sig;
            }
        }
        i++;
    }

    return encontrado;
}

void cargar_pila_desde_indices(tdiccionario dic, indices in, tpila &pila_juego) {
    tpalabra aux;

    for (int i = 0; i < 6; i++) {
        if (obtener_palabra_por_indice(dic, in[i], aux)) {
            agregar_pila(pila_juego, aux);
        }
    }
}

void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego) {
    indices in;
    int total = contar_palabras(dic);
    generar_indices_azar(total, in);
    cargar_pila_desde_indices(dic, in, pila_juego);
}



void mostrarMenuAdivinar(int puntaje, int intentos, int adivinadas, tpistas pistas_usadas, 
    tpalabra actual, char &op) {
    limpiarPantalla();
    cout << "\n    J O Y A  " << adivinadas + 1 << "  D E  6" << endl;
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
    limpiar_buffer(); 
}

// Submenu de pistas d
void mostrarMenuPistas(char &op) {
    limpiarPantalla();
    cout << "\n";
    cout << " +---------------------------------------+\n";
    cout << " |        * Pistas Disponibles * |\n";
    cout << " +---------------------------------------+\n\n";
    cout << "  1) Cantidad de Letras - 2 puntos" << endl;
    cout << "  2) Primer Letra - 3 puntos" << endl;
    cout << "  3) Definicion - 4 puntos" << endl;
    cout << "  4) Sinonimo - 5 puntos" << endl;
    cout << "\n> Opcion: ";
    cin >> op;
    limpiar_buffer(); 
}

bool palabra_adivinada(tcad actual, tcad intento){
    return strcmp(intento, actual) == 0;
}
    
void elegir_pistas(tpistas &pistas_usadas, int &puntaje, char op){
    costos costos_pistas = {2, 3, 4, 5};
    int indice = op - '1'; // Convierte '1' a 0, '2' a 1, etc.
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
        pausarPantalla(); // Pausa solo si entró a procesar algo válido
    }
    else {
        cout << "\nOPCION INVALIDA" << endl;
        pausarPantalla();
    }
}

// LÓGICA SIMPLIFICADA SIN IF VACIOS NI CHEQUEOS LARGOS
void jugar_palabra(tpalabra &actual, int &puntaje, bool &adivinada, int adivinadas) {
    tcad intento;
    int intentos = 3;
    char opcion;
    tpistas pistas_usadas = {false, false, false, false};

    while(intentos > 0 && adivinada == false){
        mostrarMenuAdivinar(puntaje, intentos, adivinadas, pistas_usadas, actual, opcion);

        if(opcion == '1'){
            limpiar_buffer(); 
            leerCadenaValidada("\nIngresa tu Respuesta: ", intento, 1);
            convertir_letra(intento[0]); // Capitalizar primera letra

            if(strcmp(intento, actual.palabra) == 0){
                adivinada = true;
            }else{
                cout << "\nNo ha adivinado la palabra." << endl;
                intentos--;
                pausarPantalla();
            }
        }
        else if(opcion == '2'){
            mostrarMenuPistas(opcion);
            elegir_pistas(pistas_usadas, puntaje, opcion);
        }
        else {
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
        
        if (!pila_vacia(pila_juego)) {
            int puntaje_partida = 7;
            bool victoria = true;
            int palabras_adivinadas = 0;
            
            while (!pila_vacia(pila_juego) && victoria) {
                tpalabra palabra_actual = quitar_pila(pila_juego);
                bool adivinada = false;
                jugar_palabra(palabra_actual, puntaje_partida, adivinada, palabras_adivinadas);
                
                if (adivinada) {
                    cout << "\n! C O R R E C T O ! La Palabra era: " << palabra_actual.palabra << endl;
                    cout << "\n! G A N A S T E  7  P U N T O S !" << endl;
                    puntaje_partida += 7;
                    palabras_adivinadas++;
                } else {
                    limpiarPantalla();
                    cout << "\n! H A S  F A L L A D O ! La Palabra Correcta era: " << palabra_actual.palabra << endl;
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
        else{
            cout << "\nERROR: No se pudieron cargar las palabras para el juego." << endl;
            pausarPantalla();
        }
    }
}


void construir_ranking(pjugador arbol, tlista_ranking &lista) {
    if (arbol != NULL) { // Reemplaza al return si es NULL
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
}

void mostrarVencedores(pjugador arbol_jugadores, tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- VENCEDORES (Ranking) ---" << endl;

    liberarlista(ranking);
    construir_ranking(arbol_jugadores, ranking);

    if (ranking.inicio == NULL) {
        cout << "\nNo hay vencedores registrados aun." << endl;
        cout << "Los vencedores son jugadores que han ganado al menos una partida." << endl;
        pausarPantalla();
    }
    else{
        char orden_op;
        cout << "\nVer ranking en orden:" << endl;
        cout << " 1) Decreciente (Mayor a Menor)" << endl;
        cout << " 2) Creciente (Menor a Mayor)" << endl;
        cout << "Opcion: ";
        cin >> orden_op;
        limpiar_buffer(); 


        bool creciente = (orden_op == '2');
        
        if (orden_op != '1' && orden_op != '2') {
            cout << "\nOPCION INVALIDA. Se mostrara en orden decreciente por defecto." << endl;
            creciente = false; // Por defecto decreciente
            pausarPantalla();
        }

        cout << "\n--- RANKING ---" << endl;
        mostrarlista(ranking, creciente);
    }

    liberarlista(ranking);
    cout << "\n(Ranking liberado.)" << endl;
}