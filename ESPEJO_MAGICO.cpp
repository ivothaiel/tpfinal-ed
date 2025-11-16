#include "modulos.hpp"
//PROGRAMA PRINCIPAL
int main(){
	char op;
    
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
    int c; 
    while ((c = getchar()) != '\n' && c != EOF);
    getchar(); // Espera al Enter

	do{
		limpiarPantalla();
		menu_principal(op); 
        
		switch(op){
		    case '1':
			    gestionarJugadores(arbol_jugadores); 
			    break;
		    case '2':
			    gestionarPalabras(diccionario_palabras); 
			    break;
		    case '3':
			    iniciarJuego(arbol_jugadores, diccionario_palabras, ranking_vencedores); 
			    break;
		    case '4':
			    mostrarVencedores(arbol_jugadores, ranking_vencedores); 
			    break;
		    case '5':
                limpiarPantalla();
                cout << "\nGuardando datos..." << endl;
                
                guardarjugadores(arbol_jugadores);
                guardarpalabras(diccionario_palabras);
                
                liberar(arbol_jugadores);
                liberar_diccionario(diccionario_palabras);
                liberarlista(ranking_vencedores);
                
			    cout << "\nQue los espiritus guardianes guien tu camino.\n";
			    cout << "Hasta pronto, viajero.\n\n";
			    break;
		    default:
			    cout << "OPCION INVALIDA" << endl;
		}
        if (op != '5') pausarPantalla();
        
	} while(op != '5');
	
	return 0;
}