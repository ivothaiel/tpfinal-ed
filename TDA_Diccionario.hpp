// --- DEFINICION ---
// Reutilizamos tpalabra_simple definiendo tpalabra como alias para mantener compatibilidad
typedef tpalabra_simple tpalabra;

typedef struct tnodo_palabra *pnodo_palabra;

struct tnodo_palabra {
    tpalabra dato;          
    pnodo_palabra ant;     
    pnodo_palabra sig;     
};

struct tlista_palabras {
    pnodo_palabra inicio;
    pnodo_palabra fin;
};

const int MAX_CLAVES = 26; 

struct tclave {
    char clave;                 
    tlista_palabras listado;    
};

typedef tclave tdiccionario[MAX_CLAVES];

// --- IMPLEMENTACION ---
void iniciarlista_palabras(tlista_palabras &lis) {
    lis.inicio = NULL;
    lis.fin = NULL;
}

void creardic(tdiccionario &dic) {
    int i;
    char letra = 'A';
    for (i = 0; i < MAX_CLAVES; i++) {
        dic[i].clave = letra;
        iniciarlista_palabras(dic[i].listado); 
        letra++; 
    }
}

void crearnodo_palabra(pnodo_palabra &nuevo, tpalabra datos) { 
    nuevo = new tnodo_palabra;
    if (nuevo != NULL) { 
        nuevo->dato = datos; 
        nuevo->sig = NULL; 
        nuevo->ant = NULL; 
    }
    else
        cout<<"\nMemoria Llena"<<endl; 
}

void insertar_ordenado_palabras(tlista_palabras &lis, pnodo_palabra nuevo) {
    pnodo_palabra p;
    if (lis.inicio == NULL) { 
        lis.inicio = nuevo; 
        lis.fin = nuevo; 
    } else if (strcmp(nuevo->dato.palabra, lis.inicio->dato.palabra) < 0) { 
        nuevo->sig = lis.inicio; 
        lis.inicio->ant = nuevo; 
        lis.inicio = nuevo;
    } else if (strcmp(nuevo->dato.palabra, lis.fin->dato.palabra) > 0) { 
        lis.fin->sig = nuevo; 
        nuevo->ant = lis.fin; 
        lis.fin = nuevo;
    } else { 
        p = lis.inicio->sig;
        while (strcmp(nuevo->dato.palabra, p->dato.palabra) > 0) { 
            p = p->sig; 
        }
        nuevo->ant = p->ant; 
        nuevo->sig = p;
        p->ant->sig = nuevo; 
        p->ant = nuevo;
    }
}

int obtener_indice(tdiccionario dic, char clave){
    int i = 0;
    bool encontrado = false;
    while (i < MAX_CLAVES && encontrado == false) {
        if (clave == dic[i].clave)
            encontrado = true;
        else
            i++;
    }
    return i;
}

void agregar_palabra(tdiccionario &dic, tpalabra datos) { 
    pnodo_palabra nuevo;
    int indice = obtener_indice(dic, datos.palabra[0]);
    crearnodo_palabra(nuevo, datos); 
    insertar_ordenado_palabras(dic[indice].listado, nuevo); 
}

pnodo_palabra buscar_palabra_diccionario(tdiccionario &dic, tcad palabra_buscada) {
    int indice = obtener_indice(dic, palabra_buscada[0]);
    pnodo_palabra p;
    
    p = dic[indice].listado.inicio;
    while (p != NULL && strcmp(p->dato.palabra, palabra_buscada) != 0) {
        if (strcmp(p->dato.palabra, palabra_buscada) > 0) 
            p = NULL; 
        else
            p = p->sig; 
    }
    return p;
}

pnodo_palabra quitar_palabra(tlista_palabras &lista, tcad buscado){
    pnodo_palabra extraido, i;
    if(strcmp(lista.inicio->dato.palabra, buscado) == 0){
        if(lista.inicio == lista.fin){
            extraido = lista.inicio;
            lista.inicio = NULL;
            lista.fin = NULL;
        }else{
            extraido = lista.inicio;
            lista.inicio = lista.inicio->sig;
            lista.inicio->ant = NULL;
            extraido->sig = NULL;
        }
    }else{
        if(strcmp(lista.fin->dato.palabra, buscado) == 0){
            extraido = lista.fin;
            lista.fin = lista.fin->ant;
            lista.fin->sig = NULL;
            extraido->ant = NULL;
        }else{
            for(i = lista.inicio->sig; i != lista.fin && 
                strcmp(i->dato.palabra, buscado) != 0; i = i->sig);
            extraido = i;
            (i->ant)->sig = extraido->sig;
            (i->sig)->ant = extraido->ant;
            extraido->sig = NULL;
            extraido->ant = NULL;
        }
    }
    return extraido;
}

pnodo_palabra eliminar_palabra(tdiccionario &dic, tcad buscado){
    int indice = obtener_indice(dic, buscado[0]);
    pnodo_palabra quitado = quitar_palabra(dic[indice].listado, buscado);
    return quitado;
}

void liberar_lista_palabras(pnodo_palabra &lis) {
    pnodo_palabra aux;
    while (lis != NULL){ 
        aux = lis; 
        lis = lis->sig; 
        delete aux;
    }
}

void liberar_diccionario(tdiccionario &dic) {
    for (int i = 0; i < MAX_CLAVES; i++) {
        liberar_lista_palabras(dic[i].listado.inicio);
        dic[i].listado.inicio = NULL; 
        dic[i].listado.fin = NULL;
    }
}

int contar_palabras(tdiccionario dic) {
    int contador = 0;
    pnodo_palabra p;
    for (int i = 0; i < MAX_CLAVES; i++) {
        p = dic[i].listado.inicio;
        while (p != NULL) {
            contador++;
            p = p->sig;
        }
    }
    return contador;
}