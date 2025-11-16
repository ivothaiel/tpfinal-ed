#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

#include "TDAJugador.hpp"
#include "menus.hpp"
#include "TDA_Base.hpp"

void iniciar_estructuras(pjugador &jugadores);

int main(){
	pjugador jugadores;
	char op;
	
	iniciar_estructuras(jugadores);
	
	do{
		system("cls");
		menu_principal(op);
		switch(op){
		case '1':
			menu_jugadores(jugadores);
			break;
		case '2':
			menu_palabras();
			break;
		case '3':
			break;
		case '4':
			break;
		case '5':
			cout << "\n";
			cout << "Que los espiritus guardianes guien tu camino.\n";
			cout << "Hasta pronto, viajero.\n\n";
			break;
		default:
			cout << "OPCION INVALIDA" << endl;
		}
		system("pause");
	} while(op != '5');
	return 0;
}

// Modulo encargado de iniciar las diferentes estructuras utilizadas en el juego
void iniciar_estructuras(pjugador &jugadores){
	iniciar(jugadores);
}
