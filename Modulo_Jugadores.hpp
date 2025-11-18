#include <iostream>
using namespace std;
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

void cargar_jugador(pjugador jugadores, tjugador &jugador){
    bool existe;
    int c;
    while((c = getchar()) != '\n' && c != EOF);
    
    do{
        leerCadenaValidada("Ingrese Alias: ", jugador.alias, 4);
        existe = (buscar_jugador(jugadores, jugador.alias) != NULL);
        if(existe)
            cout << "\nEl alias '" << jugador.alias << "' ya se encuentra en uso" << endl;
    } while(existe);
    
    leerCadenaValidada("Ingrese Nombre: ", jugador.nombre, 4);
    leerCadenaValidada("Ingrese Apellido: ", jugador.apellido, 4);
    leerCadenaValidada("Ingrese Signo Zodiacal: ", jugador.signo, 3);
    
    jugador.juegos_ganados = 0;
    jugador.mejor_puntaje = 0;
    jugador.puntaje_acumulado = 0;
}

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

void listarJugadores(pjugador arbol_jugadores) {
    if (arbol_jugadores == NULL) { 
        cout << "\nNo hay jugadores registrados" << endl; 
    } 
    else { 
        listar_jugadores(arbol_jugadores); 
    }
    pausarPantalla();
}

void gestionarJugadores(pjugador &arbol_jugadores) {
    int opc;
    bool salir = false;
    while (!salir) {
        limpiarPantalla(); 
        cout << "\n";
        cout << " +---------------------------------------+\n";
        cout << " |      * Gestion de Jugadores * |\n";
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