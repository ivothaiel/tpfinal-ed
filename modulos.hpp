#include "menus.hpp"


//pistas
const int MAX = 4;  
typedef bool tpistas[MAX];

// Prototipos
void altaJugador(pjugador &arbol_jugadores);
void bajaJugador(pjugador &arbol_jugadores);
void modificarJugador(pjugador arbol_jugadores);
void consultarJugador(pjugador arbol_jugadores);
void listarJugadores(pjugador arbol_jugadores);
void altaPalabra(tdiccionario &dic);
void bajaPalabra(tdiccionario &dic);
void modificarPalabra(tdiccionario &dic);
void consultarPalabra(tdiccionario &dic);
void listarPalabras(tdiccionario dic);
void construir_ranking_rec(pjugador arbol, tlista_ranking &lista);
void cargar_jugador(pjugador jugadores, tjugador &jugador);
void mostrar_jugador(pjugador jugador);


void mostrarMenuAdivinar(int puntaje, int intentos, bool pistas_usadas[], tpalabra palabra_actual);
void mostrarMenuPistas();


// Gestion de Cadenas
bool es_letra(char c);
bool verificar_letras(tcad palabra);
void convertir_letra(char &c);
void mostrar_cadena(tcad palabra);
void mostrar_palabra(pnodo_palabra palabra);

// MENU PARA LA GESTION DE JUGADORES
void gestionarJugadores(pjugador &arbol_jugadores) {
    int opc;
    bool salir = false;
    while (!salir) {
        limpiarPantalla(); 
		cout << "\n";
		cout << " +---------------------------------------+\n";
		cout << " |      * Gestion de Jugadores *         |\n";
		cout << " +---------------------------------------+\n\n";
		
		cout << "   1) Registrar Jugador" << endl;
		cout << "   2) Consultar Jugador" << endl;
		cout << "   3) Modificar Jugador" << endl;
		cout << "   4) Eliminar Jugador" << endl;
		cout << "   5) Listar Jugadores (Por Alias)" << endl;
		cout << "   0) Volver\n" << endl;
		
		cout << "> Opcion: ";
        cin >> opc;
		
        switch(opc) {
            case 1:
				cout << "\n* * Registrar Jugador * *\n" << endl;
				altaJugador(arbol_jugadores); 
				break;
            case 2: 
				cout << "\n* * Consultar Jugador * *" << endl;
				consultarJugador(arbol_jugadores); 
				break;
            case 3:
				cout << "\n* * Modificar Jugador * *\n" << endl;
				modificarJugador(arbol_jugadores); 
				break;
            case 4:
				cout << "\n* * Eliminar Jugador * *" << endl; 
				bajaJugador(arbol_jugadores); 
				break;
            case 5:
				cout << "\n* * Listado de Jugadores * *" << endl; 
				listarJugadores(arbol_jugadores); 
				break;
            case 0: 
                cout << "\nVolviendo al menu principal..." << endl; 
                salir = true;
                break;
            default: 
				cout << "\nOPCION INVALIDA" << endl; 
        }
    }
}

// Muestra los datos de un jugador
void mostrar_jugador(pjugador jugador){
	cout << "\n* * DATOS DEL JUGADOR * *" << endl;
	cout << "----------------------------------" << endl;
	cout << "Alias: " << jugador->dato.alias << endl;
	cout << "Nombre: " << jugador->dato.nombre << endl;
	cout << "Apellido: " << jugador->dato.apellido << endl;
	cout << "Signo Zodiacal: " << jugador->dato.signo << endl;
	cout << "Juegos Ganados: " << jugador->dato.juegos_ganados << endl;
	cout << "Mejor Puntaje: " << jugador->dato.mejor_puntaje << endl;
	cout << "Puntaje Acumulado: " << jugador->dato.puntaje_acumulado << endl;
}

// Permite la carga de datos de un nuevo jugador
void cargar_jugador(pjugador jugadores, tjugador &jugador){
	bool existe;
	int c;
	while((c = getchar()) != '\n' && c != EOF);
	
	do{
		leerCadenaValidada("Ingrese Alias: ", jugador.alias, 4);
		// Buscar el alias ingresado en el arbol de jugadores
		existe = (buscar_jugador(jugadores, jugador.alias) != NULL);
		if(existe)
			cout << "\nEl alias '" << jugador.alias << "' ya se encuentra en uso" << endl;
	} while(existe);
	
	leerCadenaValidada("Ingrese Nombre: ", jugador.nombre, 4);
	
	leerCadenaValidada("Ingrese Apellido: ", jugador.apellido, 4);
	
	leerCadenaValidada("Ingrese Signo Zodiacal: ", jugador.signo, 3);
	
	// Inicializar otros datos
	jugador.juegos_ganados = 0;
	jugador.mejor_puntaje = 0;
	jugador.puntaje_acumulado = 0;
}

// Agrega un nuevo jugador al arbol de jugadores
void altaJugador(pjugador &jugadores) {
    tjugador jugador;
    pjugador nuevo;
	
	cargar_jugador(jugadores, jugador);

    crear_jugador(nuevo, jugador);
    if (nuevo != NULL) {
        insertar_jugador(jugadores, nuevo);
        cout << "\nJugador '" << jugador.alias << "' registrado con exito" << endl;
    } else {
        cout << "\nERROR: No hay memoria para crear el jugador" << endl;
    }
	pausarPantalla();
}

// Elimina un jugador del arbol de jugadores
void bajaJugador(pjugador &arbol_jugadores) {
    tcad alias_buscado;
	pjugador eliminado;
    int c;
    while ((c = getchar()) != '\n');
    
    leerCadenaValidada("\nIngrese Alias del Jugador: ", alias_buscado, 1);
    if (buscar_jugador(arbol_jugadores, alias_buscado) == NULL) {
		cout << "\nEl alias '" << alias_buscado << "' no corresponde a ningun jugador" << endl;
    } else {
        eliminado = eliminar_jugador(arbol_jugadores, alias_buscado);
		cout << "\nJugador '" << eliminado->dato.alias << "' eliminado con exito" << endl;
		delete eliminado;
    }
	pausarPantalla();
}

// Edita el campo seleccionado del jugador
void editar_jugador(pjugador &jugador, char op){
	int c;
	while ((c = getchar()) != '\n');
	switch(op){
	case '1':
		leerCadenaValidada("Ingrese Nuevo Nombre: ", jugador->dato.nombre, 4);
		cout << "\nNombre actualizado correctamente" << endl;
		break;
	case '2':
		leerCadenaValidada("Ingrese Nuevo Apellido: ", jugador->dato.apellido, 4);
		cout << "\nApellido actualizado correctamente" << endl;
		break;
	case '3':
		leerCadenaValidada("Ingrese Nuevo Signo Zodiacal: ", jugador->dato.signo, 3);
		cout << "\nSigno Zodiacal actualizado correctamente" << endl;
		break;
	case '0': 
		cout << "\nVolviendo al menu principal..." << endl; 
		break;
	default: 
		cout << "\nOPCION INVALIDA" << endl; 
	}
}

// Modifica un jugador seleccionado por alias
void modificarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
	char op;
	
    int c;
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Alias del Jugador: ", alias_buscado, 1);
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);
    if (nodo_jugador == NULL) { 
		cout << "\nEl alias '" << alias_buscado << "' no corresponde a ningun jugador" << endl;
		pausarPantalla();
	} 
    else {
		do{
			limpiarPantalla();
			cout << "\nEdicion del Jugador: " << nodo_jugador->dato.alias << endl;
			submenu_modificar_jugador(op);
			editar_jugador(nodo_jugador, op);
			pausarPantalla();
		} while(op != '0');
    }
}

// Consulta un jugador del arbol de jugadores
void consultarJugador(pjugador arbol_jugadores) {
    tcad alias_buscado;
    int c;
    while ((c = getchar()) != '\n');

    leerCadenaValidada("\nIngrese Alias del Jugador: ", alias_buscado, 1);
    pjugador nodo_jugador = buscar_jugador(arbol_jugadores, alias_buscado);
    if (nodo_jugador == NULL) { 
		cout << "\nEl alias '" << alias_buscado << "' no corresponde a ningun jugador" << endl; 
	} 
    else {
        mostrar_jugador(nodo_jugador);
    }
	pausarPantalla();
}

// Lista todos los jugadores
void listarJugadores(pjugador arbol_jugadores) {
    if (arbol_jugadores == NULL) { 
		cout << "\nNo hay jugadores registrados" << endl; 
	} 
    else { 
		listar_jugadores(arbol_jugadores); 
	}
	pausarPantalla();
}


// GESTION DE PALABRAS
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
		
        switch(opc) {
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
        if (!salir) pausarPantalla();
    }
}

bool es_letra(char c){
	return (c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z');
}

// Valida que la palabra solo contenga letras
bool verificar_letras(tcad palabra){
	bool valido = true;
	int i;
	for(i = 0; i < (int)strlen(palabra) && valido == true; i++){
		char c = palabra[i];
		if(!es_letra(c))
			valido = false;
	}
	return valido;
}

// Convierte la primer letra de la palabra a mayuscula solo si es minuscula
void convertir_letra(char &c) {
	if (c >= 'a' && c <= 'z') {
		c = c - 32;  // convierte a may�scula
	}
}


//imprime una cadena de caracteres, letra por letra.
void mostrar_cadena(tcad palabra){
	int i;
	for(i = 0; i < (int)strlen(palabra); i++){
		char c = palabra[i];
		cout << c;
	}
}


//da de alta una palabra nueva en el diccionario
void altaPalabra(tdiccionario &dic) {
    tpalabra nueva_palabra;
    bool validar;
    int c;
    while ((c = getchar()) != '\n'); // Limpia el buffer del menu
    do{
        leerCadenaValidada("Ingrese Palabra: ", nueva_palabra.palabra, 5);
        mostrar_cadena(nueva_palabra.palabra);
        
        validar = verificar_letras(nueva_palabra.palabra);
        if(!validar)
            cout << "\nLa palabra solo debe contener letras" << endl;
    } while(!validar); // Repite si no es valido
    
    convertir_letra(nueva_palabra.palabra[0]);
    
    if (buscar_palabra_diccionario(dic, nueva_palabra.palabra) != NULL) 
        cout << "\nLa palabra '" << nueva_palabra.palabra << "' ya esta registrada" << endl;
    else{
        leerCadenaValidada("Ingrese Definicion: ", nueva_palabra.definicion, 1);
        leerCadenaValidada("Ingrese Sinonimo: ", nueva_palabra.sinonimo, 1);
        nueva_palabra.longitud = (int)strlen(nueva_palabra.palabra);
        agregar_palabra(dic, nueva_palabra);
        cout << "Palabra '" << nueva_palabra.palabra << "' registrada con exito." << endl;
    }
}



void bajaPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
	
    int c;
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Palabra a Eliminar: ", palabra_buscada, 1);
    if (quitar_palabra(dic, palabra_buscada)) {
        cout << "Palabra '" << palabra_buscada << "' eliminada con exito." << endl;
    } else {
        cout << "ERROR: Palabra no encontrada." << endl;
    }
}*/

void bajaPalabra(tdiccionario &dic){
	tcad palabra_buscada;
	pnodo_palabra eliminado;
	
	int c;
	while ((c = getchar()) != '\n');
	
	leerCadenaValidada("Ingrese Palabra a Eliminar: ", palabra_buscada, 1);
	convertir_letra(palabra_buscada[0]);
	pnodo_palabra palabra = buscar_palabra_diccionario(dic, palabra_buscada);
	// Buscar directamente si existe la palabra en el diccionario
	if(palabra != NULL){
		eliminado = eliminar_palabra(dic, palabra->dato.palabra);
		cout << "\n'" << eliminado->dato.palabra << "' se ha eliminado correctamente" << endl;
		delete eliminado;
	}else
		cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
}

void modificarPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
	
    int c;
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Palabra a Modificar: ", palabra_buscada, 1);
	convertir_letra(palabra_buscada[0]);
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);
    if (nodo_palabra == NULL) { 
		cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl;
	} 
    else {
		limpiarPantalla();
        cout << "\nEdicion de la Palabra: " << nodo_palabra->dato.palabra << endl;
        leerCadenaValidada("Ingrese Nueva Definicion: ", nodo_palabra->dato.definicion, 1);
        leerCadenaValidada("Ingrese Nuevo Sinonimo: ", nodo_palabra->dato.sinonimo, 1);
        cout << "Datos de la palabra '" << nodo_palabra->dato.palabra << "' actualizados" << endl;
    }
}

void mostrar_palabra(pnodo_palabra palabra){
	cout << "\n* * DATOS DE LA PALABRA * *" << endl;
	cout << "----------------------------------" << endl;
	cout << "Palabra: " << palabra->dato.palabra << endl;
	cout << "Longitud: " << palabra->dato.longitud << " caracteres"<< endl;
	cout << "Definicion: " << palabra->dato.definicion << endl;
	cout << "Sinonimo: " << palabra->dato.sinonimo << endl;
}

void consultarPalabra(tdiccionario &dic) {
    tcad palabra_buscada;
	
    int c;
    while ((c = getchar()) != '\n');

    leerCadenaValidada("Ingrese Palabra a Consultar: ", palabra_buscada, 1);
	convertir_letra(palabra_buscada[0]);
    pnodo_palabra nodo_palabra = buscar_palabra_diccionario(dic, palabra_buscada);
    if (nodo_palabra == NULL)
		cout << "\n'" << palabra_buscada << "' no existe en el diccionario" << endl; 
    else
		mostrar_palabra(nodo_palabra);
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
				cout << " - " << p->dato.palabra 
					<< "\n Definici�n: " << p->dato.definicion << "\n";
				p = p->sig;
            }
        }
    }
    if (!hayPalabras)
		cout << "\nNo hay palabras registradas en el diccionario" << endl;
}


// LOGICA COORDINADORA
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
    
    cout << "�Suerte, " << jugador_seleccionado->dato.alias << "! La princesa Karym Su Yang cuenta contigo." << endl;
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
            cout << "�Correcto! La palabra era: " << palabra_actual.palabra << endl;
            cout << "Has ganado 7 puntos." << endl;
            puntaje_partida += 7;
        } else {
            cout << "�HAS FALLADO! La palabra correcta era: " << palabra_actual.palabra << endl;
            cout << "La guardiana del espejo te convierte en piedra..." << endl;
            gano_partida = false;
        }
    }

    limpiarPantalla();
    if (gano_partida) {
        cout << "*****************************************************" << endl;
        cout << "�FELICIDADES, " << jugador_seleccionado->dato.alias << "!" << endl;
        cout << "�Has adivinado las 6 palabras y liberado a la princesa!" << endl;
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
