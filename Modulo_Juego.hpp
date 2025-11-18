const int PISTAS = 4;  
typedef bool tpistas[PISTAS];

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

void mostrarMenuAdivinar(int puntaje, int intentos, tpistas pistas_usadas, tpalabra palabra_actual) {
    cout << "---  ADIVINA LA PALABRA  ---" << endl;
    cout << "Puntaje Actual: " << puntaje << endl;
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
}

void mostrarMenuPistas() {
    cout << "\n--- PISTAS DISPONIBLES ---" << endl;
    cout << "1. Cantidad de Letras (Costo: 2 puntos)" << endl;
    cout << "2. Primera Letra (Costo: 3 puntos)" << endl;
    cout << "3. Definicion (Costo: 4 puntos)" << endl;
    cout << "4. Sinonimo (Costo: 5 puntos)" << endl;
    cout << "0. Cancelar" << endl;
    cout << "Elige pista: ";
}

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

        if (opcion == 'a' || opcion == 'A') {
            int c;
            while ((c = getchar()) != '\n');
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
            int costos[] = {2, 3, 4, 5};

            if (idx >= 0 && idx < 4) {
                int costo = costos[idx];

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
    
    cout << "Suerte, " << jugador_seleccionado->dato.alias << "! La princesa Karym Su Yang cuenta contigo." << endl;
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
            cout << "Correcto! La palabra era: " << palabra_actual.palabra << endl;
            cout << "Has ganado 7 puntos." << endl;
            puntaje_partida += 7;
        } else {
            cout << "HAS FALLADO! La palabra correcta era: " << palabra_actual.palabra << endl;
            cout << "La guardiana del espejo te convierte en piedra..." << endl;
            gano_partida = false;
        }
    }

    limpiarPantalla();
    if (gano_partida) {
        cout << "*****************************************************" << endl;
        cout << "FELICIDADES, " << jugador_seleccionado->dato.alias << "!" << endl;
        cout << "Has adivinado las 6 palabras y liberado a la princesa!" << endl;
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
    cout << "---  VENCEDORES (Ranking por Mejor Puntaje)  ---" << endl;

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