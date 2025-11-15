#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

using namespace std;

// Diferentes menus del juego
#include "menus.hpp"

int main(){
	char op;
	do{
		system("cls");
		menu_principal(op);
		switch(op){
		case '1':
			menu_jugadores();
			break;
		case '2':
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
