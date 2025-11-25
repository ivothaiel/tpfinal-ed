// --- DEFINICION TDA PILA ---
/*struct tpalabra_simple { // Estructura minima necesaria para la pila si no incluimos diccionario aun
    tcad palabra; 
    int longitud; 
    tcad definicion;
    tcad sinonimo;
};*/
// Nota: Usaremos tpalabra_simple aqui para mantener orden, 
// pero compatible con la del diccionario mas adelante.

const int MAXPILA = 6;  
typedef tpalabra tcontenedor[MAXPILA]; 

struct tpila {
    tcontenedor datos; 
    int cima;         
};

// --- IMPLEMENTACION TDA PILA ---
void iniciar_pila(tpila &p) {
    p.cima = -1;
}

bool pila_vacia(tpila p) {
    return p.cima == -1;
}

bool pila_llena(tpila p) {
    return p.cima == MAXPILA - 1;
}

void agregar_pila(tpila &p, tpalabra nuevo) {
    if (pila_llena(p) == true)
		cout << "ERROR: Pila Llena" << endl; 
    else { 
		p.cima++; 
		p.datos[p.cima] = nuevo; 
	}
}

tpalabra quitar_pila(tpila &p) {
    tpalabra extraido;
    if (pila_vacia(p) == true)
		strcpy(extraido.palabra, "ERROR_VACIA"); 
    else { 
		extraido = p.datos[p.cima]; 
		p.cima--; 
	}
    return extraido;
}
