#include <iostream>
#include <string.h>
#include <stdio.h>

using namespace std;

// --- DEFINICION JUGADOR ---
struct tjugador {
    tcad nombre;
    tcad apellido;
    tcad signo;
    tcad alias;

    // Campo clave para el ABB
    int juegos_ganados;
    int mejor_puntaje;
    int puntaje_acumulado;
};

// Define el puntero al nodo, segun convencion TDA/PE
typedef struct tnodo_jugador *pjugador;

struct tnodo_jugador {
    tjugador dato;
    pjugador izq;
    pjugador der;
};

// --- IMPLEMENTACION ---

// Inicializa el puntero raiz del arbol a NULL
// Criterio: TDA ABB (Inicializacion)
void iniciar(pjugador &arbol) {
    arbol = NULL;
}

// Reserva memoria para un nuevo nodo del jugador y asigna datos
// Criterio: TDA ABB (Crear Nodo)
void crear_jugador(pjugador &nuevo, tjugador dato_jugador) {
    nuevo = new tnodo_jugador;
    
    if (nuevo != NULL) {
        nuevo->dato = dato_jugador;
        nuevo->izq = NULL;
        nuevo->der = NULL;
    }
}

// Agrega un nuevo jugador en el arbol segun el alias (criterio de orden)
// Criterio: TDA ABB (Insercion Recursiva)
void insertar_jugador(pjugador &arbol, pjugador nuevo) {
    if (arbol == NULL) {
        arbol = nuevo;
    }
    else {
        // Usa strcmp para decidir si va a la izquierda (< 0) o derecha (>= 0)
        if (strcmp(nuevo->dato.alias, arbol->dato.alias) < 0)
            insertar_jugador(arbol->izq, nuevo);
        else
            insertar_jugador(arbol->der, nuevo);
    }
}

// Busca un jugador por alias de forma recursiva
// Criterio: TDA ABB (Busqueda Eficiente Recursiva).
pjugador buscar_jugador(pjugador arbol, tcad alias_buscado) {
    if (arbol == NULL) {
        return NULL;
    }
    else {
        int comparacion = strcmp(alias_buscado, arbol->dato.alias);
		
        if (comparacion == 0) {
            return arbol;
        }
        else if (comparacion < 0) {
            return buscar_jugador(arbol->izq, alias_buscado);
        }
        else {
            return buscar_jugador(arbol->der, alias_buscado);
        }
    }
}

// Muestra todos los jugadores ordenados alfabeticamente por alias
// Criterio: TDA ABB (Recorrido En-Orden: Izquierda-Raiz-Derecha)
void listar_jugadores(pjugador arbol) {
    if (arbol != NULL) {
        listar_jugadores(arbol->izq); // Recorre Izquierda
		
        cout << "-----------------------------" << endl;
        cout << "Alias: " << arbol->dato.alias << endl;
        cout << "Nombre: " << arbol->dato.nombre << endl;
        cout << "Apellido: " << arbol->dato.apellido << endl;
        cout << "Signo: " << arbol->dato.signo << endl;
        cout << "Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
        cout << "Mejor Puntaje: " << arbol->dato.mejor_puntaje << endl;
        cout << "Puntaje Acumulado: " << arbol->dato.puntaje_acumulado << endl;
		
        listar_jugadores(arbol->der); // Recorre Derecha
    }
}

// Muestra los jugadores para poder elegirlos una vez iniciado el juego
// Solo muestra los datos mas relevantes 
void mostrar_jugadores(pjugador arbol){
	if(arbol != NULL){
		mostrar_jugadores(arbol->izq);
		
		//cout << "-----------------------------" << endl;
		cout << "  Alias: " << arbol->dato.alias << endl;
		cout << "  Juegos Ganados: " << arbol->dato.juegos_ganados << endl;
		cout << "  Mejor Puntaje: " << arbol->dato.mejor_puntaje << endl;
		cout << "-----------------------------" << endl;
		
		mostrar_jugadores(arbol->der);
	}
}

// Cuenta la cantidad de nodos (jugadores) en el arbol de forma recursiva
// Criterio: ABB (Contar Nodos Recursivo)
int contar_jugadores(pjugador arbol) {
    if (arbol == NULL) {
        return 0;
    }

    return 1 + contar_jugadores(arbol->izq) + contar_jugadores(arbol->der);
}

// Intercambia los datos de dos nodos (usado en la eliminacion)
void cambio(tjugador &a, tjugador &b) {
    tjugador aux = a; 
    a = b;
    b = aux;
}

// Busca el menor nodo en el subarbol derecho (el sucesor in-order) para sustituir
// Criterio: ABB (Menor de los Mayores / Sustitucion Recursiva)
pjugador menor_mayores(pjugador elegido, pjugador &menor) {
    pjugador aux;

    if (menor->izq != NULL) {
        aux = menor_mayores(elegido, menor->izq);
    }
    else {
        // Cuando se encuentra el menor, se intercambian los datos con el 'elegido'
        cambio(elegido->dato, menor->dato);
		
        aux = menor;
		
        // El puntero 'menor' (pasado por referencia) se actualiza a su subarbol derecho
        menor = menor->der;
    }

    return aux;
}

// Elimina un jugador por alias, aplicando el criterio de Menor de los Mayores para 2 hijos
// Criterio: ABB (Eliminacion Recursiva)
pjugador eliminar_jugador(pjugador &arbol, tcad alias_buscado) {
    pjugador aux;

    if (arbol == NULL) {
        aux = NULL;
    }
    else {
        int comparacion = strcmp(alias_buscado, arbol->dato.alias);
		
        if (comparacion < 0) {
            aux = eliminar_jugador(arbol->izq, alias_buscado);
        }
        else if (comparacion > 0) {
            aux = eliminar_jugador(arbol->der, alias_buscado);
        }
        else { // Nodo encontrado
            aux = arbol;
			
            if (arbol->izq == NULL && arbol->der == NULL) { 
                // Caso 1: Nodo Hoja
                arbol = NULL;
            }
            else if (arbol->izq == NULL) { 
                // Caso 2a: 1 Hijo Derecho
                arbol = arbol->der;
            }
            else if (arbol->der == NULL) { 
                // Caso 2b: 1 Hijo Izquierdo
                arbol = arbol->izq;
            }
            else { 
                // Caso 3: 2 Hijos
                aux = menor_mayores(arbol, arbol->der);
            }
        }
    }

    return aux;
}

// Libera toda la memoria dinamica del arbol de forma recursiva (Post-orden)
// Criterio: Liberacion Recursiva de TDA
void liberar(pjugador &arbol) {
    if (arbol != NULL) {
        liberar(arbol->izq);  // Libera Izquierda
        liberar(arbol->der);  // Libera Derecha
        delete arbol;         // Libera Raiz
        arbol = NULL;
    }
}
