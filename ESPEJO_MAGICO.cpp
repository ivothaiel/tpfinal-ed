#include <iostream>

using namespace std;

#include "comunes.hpp"
#include "menus_Textos.hpp"
#include "TDA_Pila.hpp"
#include "TDA_Ranking.hpp"
#include "TDA_Jugador.hpp"
#include "TDA_Diccionario.hpp"
#include "archivos.hpp"
#include "Modulo_Jugadores.hpp"
#include "Modulo_Palabras.hpp"
#include "Modulo_Juego.hpp"

// PROGRAMA PRINCIPAL
int main(){
    char op;
    tcad msg_menu = "\n> Opcion: "; 
	srand(time(NULL));
	
    // Declarar estructuras
    pjugador arbol_jugadores;
    tdiccionario diccionario_palabras;
    tlista_ranking ranking_vencedores; 

    // Inicializar estructuras
    iniciar(arbol_jugadores);                 
    creardic(diccionario_palabras);           
    
    iniciarlista(ranking_vencedores);        

    // Cargar datos desde archivos
    cargarjugadores(arbol_jugadores);
    cargarpalabras(diccionario_palabras);
    
    cout << "\nDatos cargados. Presione Enter para iniciar..." << endl;
    int c; // Limpieza manual del buffer
    while ((c = getchar()) != '\n');
    getchar(); // Espera al Enter

    do{
        limpiarPantalla(); 
        menu_principal(op); 
        op = leer_opcion_caracter(msg_menu, '0', '4');
        switch(op){
            case '1':
                gestionarJugadores(arbol_jugadores); 
                break;
            case '2':
                gestionarPalabras(diccionario_palabras); 
                break;
            case '3':
				if(contar_jugadores(arbol_jugadores) < 2)
					cout << "\nDebe registrar al menos 2 jugadores para iniciar el juego" << endl;
				else if(contar_palabras(diccionario_palabras) < 6)
					cout << "\nDebe registrar al menos 6 palabras para iniciar el juego" << endl;
				else
					iniciarJuego(arbol_jugadores, diccionario_palabras, ranking_vencedores); 
                break;
            case '4':
                mostrarVencedores(arbol_jugadores, ranking_vencedores); 
                break;
            case '0':
                cout << "\nGuardando datos..." << endl;
                
                guardarjugadores(arbol_jugadores);
                guardarpalabras(diccionario_palabras);
                
                liberar(arbol_jugadores);
                liberar_diccionario(diccionario_palabras);
                liberarlista(ranking_vencedores);
                
                cout << "\nQue los espiritus guardianes guien tu camino. �Hasta pronto viajero!" << endl;
                break;
            default:
                cout << "\nOPCION INVALIDA" << endl;
        }
        if (op != '0') pausarPantalla();
        
    } while(op != '0');
    
    return 0;
}
