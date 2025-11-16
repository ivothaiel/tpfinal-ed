#include "menus.hpp"


void altaJugador(pjugador &arbol_jugadores);
void bajaJugador(pjugador &arbol_jugadores);
void modificarJugador(pjugador arbol_jugadores);
void consultarJugador(pjugador arbol_jugadores);
void listarJugadores_alfabeticamente(pjugador arbol_jugadores);
void altaPalabra(tdiccionario &dic);
void bajaPalabra(tdiccionario &dic);
void modificarPalabra(tdiccionario &dic);
void consultarPalabra(tdiccionario &dic);
void listarPalabras(tdiccionario dic);
void construir_ranking_rec(pjugador arbol, tlista_ranking &lista);




void gestionarJugadores(pjugador &arbol_jugadores) {
    int opc;
    bool salir = false;
    while (!salir) {
        limpiarPantalla(); 
        cout << "--- GESTION DE JUGADORES ---" << endl;
        cout << "1. Registrar Jugador" << endl;
        cout << "2. Consultar Jugador" << endl;
        cout << "3. Modificar Jugador" << endl;
        cout << "4. Eliminar Jugador" << endl;
        cout << "5. Listar Jugadores (Por Alias)" << endl;
        cout << "0. Volver al Menu Principal" << endl;
        cout << "Ingrese opcion: ";
        cin >> opc;

        switch(opc) {
            case 1: altaJugador(arbol_jugadores); break;
            case 2: consultarJugador(arbol_jugadores); break;
            case 3: modificarJugador(arbol_jugadores); break;
            case 4: bajaJugador(arbol_jugadores); break;
            case 5: listarJugadores_alfabeticamente(arbol_jugadores); break;
            case 0: 
                cout << "Volviendo al menu principal..." << endl; 
                salir = true;
                break;
            default: 
                cout << "Opcion incorrecta." << endl; 
                break;
        }
        if (!salir) pausarPantalla(); 
    }
}

void altaJugador(pjugador &arbol_jugadores) {
    tjugador nuevo_jugador;
    pjugador nuevo_nodo;
    limpiarPantalla();
    cout << "--- ALTA DE JUGADOR ---" << endl;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    leerCadenaValidada("Ingrese Alias (min 4 caracteres): ", nuevo_jugador.alias, 4);
    if (buscar_jugador(arbol_jugadores, nuevo_jugador.alias) != NULL) {
        cout << "ERROR: El alias '" << nuevo_jugador.alias << "' ya existe." << endl;
        return;
    }

    leerCadenaValidada("Ingrese Nombre (min 4 caracteres): ", nuevo_jugador.nombre, 4);
    leerCadenaValidada("Ingrese Apellido (min 4 caracteres): ", nuevo_jugador.apellido, 4);
    leerCadenaValidada("Ingrese Signo Zodiacal: ", nuevo_jugador.signo, 1);
    
    nuevo_jugador.juegos_ganados = 0;
    nuevo_jugador.mejor_puntaje = 0;
    nuevo_jugador.puntaje_acumulado = 0;

    crear_jugador(nuevo_nodo, nuevo_jugador);
    if (nuevo_nodo != NULL) {
        insertar_jugador(arbol_jugadores, nuevo_nodo);
        cout << "Jugador '" << nuevo_jugador.alias << "' registrado con exito." << endl;
    } else {
        cout << "ERROR: No hay memoria para crear el jugador." << endl;
    }
}

void bajaJugador(pjugador &arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- BAJA DE JUGADOR ---" << endl;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
    
    leerCadenaValidada("Ingrese el alias del jugador a eliminar: ", alias_buscado, 1);
    if (buscar_jugador(arbol_jugadores, alias_buscado) == NULL) {
        cout << "ERROR: No se encontro al jugador con alias '" << alias_buscado << "'." << endl;
    } else {
        eliminarjugador(arbol_jugadores, alias_buscado);
        cout << "Jugador '" << alias_buscado << "' eliminado con exito." << endl;
    }
}

void modificarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- MODIFICAR JUGADOR ---" << endl;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    leerCadenaValidada("Ingrese el alias del jugador a modificar: ", alias_buscado, 1);
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);
    if (nodo_jugador == NULL) { cout << "Jugador no encontrado." << endl; } 
    else {
        cout << "Jugador encontrado. Ingrese nuevos datos:" << endl;
        cout << "Alias: " << nodo_jugador->dato.alias << " (No modificable)" << endl;
        leerCadenaValidada("Ingrese nuevo Nombre (min 4): ", nodo_jugador->dato.nombre, 4);
        leerCadenaValidada("Ingrese nuevo Apellido (min 4): ", nodo_jugador->dato.apellido, 4);
        leerCadenaValidada("Ingrese nuevo Signo Zodiacal: ", nodo_jugador->dato.signo, 1);
        cout << "\nDatos del jugador '" << nodo_jugador->dato.alias << "' actualizados." << endl;
    }
}

void consultarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    limpiarPantalla();
    cout << "--- CONSULTAR JUGADOR ---" << endl;
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    leerCadenaValidada("Ingrese el alias del jugador a consultar: ", alias_buscado, 1);
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);
    if (nodo_jugador == NULL) { cout << "Jugador no encontrado." << endl; } 
    else {
        cout << "--- DATOS DEL JUGADOR ---" << endl;
        cout << "Alias: " << nodo_jugador->dato.alias << endl;
        cout << "Nombre: " << nodo_jugador->dato.nombre << " " << nodo_jugador->dato.apellido << endl;
        cout << "Signo: " << nodo_jugador->dato.signo << endl;
        cout << "Juegos Ganados: " << nodo_jugador->dato.juegos_ganados << endl;
        cout << "Mejor Puntaje: " << nodo_jugador->dato.mejor_puntaje << endl;
        cout << "Puntaje Acumulado: " << nodo_jugador->dato.puntaje_acumulado << endl;
    }
}

void listarJugadores_alfabeticamente(pjugador arbol_jugadores) {
    limpiarPantalla();
    cout << "--- LISTADO DE JUGADORES (Orden Alfabetico por Alias) ---" << endl;
    if (arbol_jugadores == NULL) { cout << "\nNo hay jugadores registrados." << endl; } 
    else { listar_jugadores(arbol_jugadores); }
}


// GESTIÓN DE PALABRAS

void gestionarPalabras(tdiccionario &dic) {
    int opc;
    bool salir = false;
    while (!salir) {
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
            case 0: cout << "Volviendo al menu principal..." << endl; salir = true; break;
            default: cout << "Opcion incorrecta." << endl; break;
        }
        if (!salir) pausarPantalla();
    }
}

void altaPalabra(tdiccionario &dic) {
    tpalabra nueva_palabra;
    limpiarPantalla();
    cout << "--- ALTA DE PALABRA ---" << endl;
    
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    leerCadenaValidada("Ingrese la palabra a modificar: ", palabra_buscada, 1);
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);
    if (nodo_palabra == NULL) { cout << "Palabra no encontrada." << endl; } 
    else {
        cout << "Palabra encontrada. Ingrese nuevos datos:" << endl;
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
    int c;
    while ((c = getchar()) != '\n' && c != EOF);

    leerCadenaValidada("Ingrese la palabra a consultar: ", palabra_buscada, 1);
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);
    if (nodo_palabra == NULL) { cout << "Palabra no encontrada." << endl; } 
    else {
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
    bool hayPalabras = false;
    for (int i = 0; i < MAX_CLAVES; i++) {
        if (dic[i].listado.inicio != NULL) {
            hayPalabras = true;
            cout << "\n--- Palabras con '" << dic[i].clave << "' ---" << endl;
            pnodo_palabra p = dic[i].listado.inicio;
            while (p != NULL) {
                cout << "  - " << p->dato.palabra << " (" << p->dato.definicion << ")" << endl;
                p = p->sig;
            }
        }
    }
    if (!hayPalabras) { cout << "\nNo hay palabras registradas en el diccionario." << endl; }
}


// LÓGICA COORDINADORA

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
        int c;
        while ((c = getchar()) != '\n' && c != EOF);
        
        fgets(alias_buscado, MAX, stdin);
        int len = strlen(alias_buscado);
        if (len > 0 && alias_buscado[len - 1] == '\n') {
            alias_buscado[len - 1] = '\0'; 
        }

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

void seleccionarPalabrasAleatorias(tdiccionario dic, tpila &pila_juego, int totalPalabras) {
    tpalabra palabras_seleccionadas[6];
    int palabras_encontradas = 0;
    
    tpalabra* todas_las_palabras = new tpalabra[totalPalabras];
    int k = 0;
    pnodo_palabra p;
    for (int i = 0; i < MAX_CLAVES; i++) {
        p = dic[i].listado.inicio;
        while (p != NULL) {
            todas_las_palabras[k] = p->dato;
            k++;
            p = p->sig;
        }
    }
    
    srand(time(NULL)); 
    int indice_aleatorio;
    bool repetida;
    
    while (palabras_encontradas < 6) {
        indice_aleatorio = rand() % totalPalabras;
        repetida = false;
        for (int j = 0; j < palabras_encontradas; j++) {
            if (strcmp(palabras_seleccionadas[j].palabra, todas_las_palabras[indice_aleatorio].palabra) == 0) {
                repetida = true;
            }
        }
        
        if (!repetida) {
            palabras_seleccionadas[palabras_encontradas] = todas_las_palabras[indice_aleatorio];
            palabras_encontradas++;
        }
    }
    
    for (int i = 0; i < 6; i++) {
        agregarpila(pila_juego, palabras_seleccionadas[i]);
    }
    
    delete[] todas_las_palabras;
}

bool jugarPalabra(tpalabra &palabra_actual, int &puntaje_partida) {
    tcad intento_palabra;
    int intentos = 3;
    bool adivinada = false;
    bool pistas_usadas[4] = {false, false, false, false};
    char op_pista;

    while (intentos > 0 && !adivinada) {
        limpiarPantalla();
        cout << "--- 💎 ADIVINA LA PALABRA 💎 ---" << endl;
        cout << "Puntaje Actual: " << puntaje_partida << endl;
        cout << "Intentos Restantes: " << intentos << endl;
        cout << "\nPistas Usadas:" << endl;
        if (pistas_usadas[0]) cout << " - Longitud: " << palabra_actual.longitud << " caracteres" << endl;
        if (pistas_usadas[1]) cout << " - Primera Letra: " << palabra_actual.palabra[0] << endl;
        if (pistas_usadas[2]) cout << " - Definicion: " << palabra_actual.definicion << endl;
        if (pistas_usadas[3]) cout << " - Sinonimo: " << palabra_actual.sinonimo << endl;

        cout << "\nOpciones:" << endl;
        cout << "  (A)divinar la palabra" << endl;
        cout << "  (P)edir una pista" << endl;
        cout << "Opcion: ";
        cin >> op_pista;

        if (op_pista == 'a' || op_pista == 'A') {
            int c;
            while ((c = getchar()) != '\n' && c != EOF);
            leerCadenaValidada("Ingresa tu respuesta: ", intento_palabra, 1);
            if (strcmp(intento_palabra, palabra_actual.palabra) == 0) {
                adivinada = true;
            } else {
                cout << "¡Incorrecto!" << endl;
                intentos--;
                pausarPantalla();
            }
        } 
        else if (op_pista == 'p' || op_pista == 'P') {
            cout << "\n--- PISTAS DISPONIBLES ---" << endl;
            cout << "1. Cantidad de Letras (Costo: 2 puntos)" << endl;
            cout << "2. Primera Letra (Costo: 3 puntos)" << endl;
            cout << "3. Definicion (Costo: 4 puntos)" << endl;
            cout << "4. Sinonimo (Costo: 5 puntos)" << endl;
            cout << "0. Cancelar" << endl;
            cout << "Elige pista: ";
            cin >> op_pista;
            
            int costo = 0;
            switch(op_pista) {
                case '1': costo = 2; if (!pistas_usadas[0] && puntaje_partida >= costo) { pistas_usadas[0] = true; puntaje_partida -= costo; } break;
                case '2': costo = 3; if (!pistas_usadas[1] && puntaje_partida >= costo) { pistas_usadas[1] = true; puntaje_partida -= costo; } break;
                case '3': costo = 4; if (!pistas_usadas[2] && puntaje_partida >= costo) { pistas_usadas[2] = true; puntaje_partida -= costo; } break;
                case '4': costo = 5; if (!pistas_usadas[3] && puntaje_partida >= costo) { pistas_usadas[3] = true; puntaje_partida -= costo; } break;
                default: break;
            }
            if (costo > 0 && puntaje_partida < 0) { 
                cout << "¡No tienes puntos suficientes para esta pista!" << endl;
                puntaje_partida += costo; 
                pistas_usadas[op_pista - '1'] = false; 
                pausarPantalla();
            }
        }
    }
    return adivinada;
}

void iniciarJuego(pjugador arbol_jugadores, tdiccionario dic, tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- INICIAR JUEGO ---" << endl;
    
    int total_jugadores = contar_jugadores(arbol_jugadores);
    int total_palabras = contar_palabras(dic);

    if (total_jugadores < 2) {
        cout << "No hay suficientes jugadores registrados (minimo 2). Registra mas jugadores." << endl;
        return;
    }
    if (total_palabras < 6) {
        cout << "No hay suficientes palabras registradas (minimo 6). Agrega mas palabras." << endl;
        return;
    }
    
    pjugador jugador_seleccionado = seleccionarJugador(arbol_jugadores);
    if (jugador_seleccionado == NULL) {
        cout << "Inicio de juego cancelado." << endl;
        return;
    }
    
    cout << "¡Suerte, " << jugador_seleccionado->dato.alias << "! La princesa Karym Su Yang cuenta contigo." << endl;
    pausarPantalla();

    tpila pila_juego;
    iniciarpila(pila_juego);
    seleccionarPalabrasAleatorias(dic, pila_juego, total_palabras);

    int puntaje_partida = 7; 
    bool gano_partida = true;
    int palabras_adivinadas = 0;

    while (!pilavacia(pila_juego) && gano_partida == true) {
        tpalabra palabra_actual = quitarpila(pila_juego);
        palabras_adivinadas++;
        
        cout << "\n--- Preparando Joya " << palabras_adivinadas << " de 6 ---" << endl;
        pausarPantalla();

        bool adivino_esta_palabra = jugarPalabra(palabra_actual, puntaje_partida);

        if (adivino_esta_palabra) {
            cout << "¡Correcto! La palabra era: " << palabra_actual.palabra << endl;
            cout << "Has ganado 7 puntos." << endl;
            puntaje_partida += 7;
        } else {
            cout << "¡HAS FALLADO! La palabra correcta era: " << palabra_actual.palabra << endl;
            cout << "La guardiana del espejo te convierte en piedra..." << endl;
            gano_partida = false;
        }
    }

    limpiarPantalla();
    if (gano_partida) {
        cout << "*****************************************************" << endl;
        cout << "¡FELICIDADES, " << jugador_seleccionado->dato.alias << "!" << endl;
        cout << "¡Has adivinado las 6 palabras y liberado a la princesa!" << endl;
        cout << "Puntaje Final de la partida: " << puntaje_partida << endl;
        cout << "*****************************************************" << endl;
        
        jugador_seleccionado->dato.juegos_ganados++;
        jugador_seleccionado->dato.puntaje_acumulado += puntaje_partida;
        if (puntaje_partida > jugador_seleccionado->dato.mejor_puntaje) {
            jugador_seleccionado->dato.mejor_puntaje = puntaje_partida;
        }
    } else {
        cout << "*****************************************************" << endl;
        cout << "                 GAME OVER" << endl;
        cout << "Has sido convertido en piedra." << endl;
        cout << "Puntaje Final: 0" << endl;
        cout << "*****************************************************" << endl;
    }
}


void construir_ranking_rec(pjugador arbol, tlista_ranking &lista) {
    if (arbol == NULL) {
        return;
    }
    
    construir_ranking_rec(arbol->izq, lista);
    
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
    
    construir_ranking_rec(arbol->der, lista);
}

void mostrarVencedores(pjugador arbol_jugadores, tlista_ranking &ranking) {
    limpiarPantalla();
    cout << "--- 🏆 VENCEDORES (Ranking por Mejor Puntaje) 🏆 ---" << endl;

    liberarlista(ranking); 
    construir_ranking_rec(arbol_jugadores, ranking);

    char orden_op;
    cout << "\nVer ranking en orden:" << endl;
    cout << "  (D)ecreciente (Mejor primero)" << endl;
    cout << "  (C)reciente (Peor primero)" << endl;
    cout << "Opcion: ";
    cin >> orden_op;
    
    bool creciente = (orden_op == 'c' || orden_op == 'C');

    cout << "\n--- RANKING ---" << endl;
    mostrarlista(ranking, creciente); 

    liberarlista(ranking);
    cout << "\n(Ranking liberado de memoria.)" << endl;
}