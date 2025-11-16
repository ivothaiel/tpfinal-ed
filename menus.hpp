#include <iostream>
#include <stdlib.h>

// MENU PRINCIPAL DEL JUEGO
void menu_principal(char &op){
	cout << "\n\n";
	cout << "+-------------------------------------------------------+\n";
	cout << "|                                                       |\n";
	cout << "|              EL HECHIZO DEL ESPEJO                    |\n";
	cout << "|                                                       |\n";
	cout << "+-------------------------------------------------------+\n";
	cout << "\n";
	
	cout << "  -----------------------------------------------\n";
	cout << "   Hace mas de 500 años, una princesa fue\n";
	cout << "   atrapada en un espejo maldito. Solo quien\n";
	cout << "   descubra las 6 palabras magicas podra romper\n";
	cout << "   el hechizo y liberarla...\n";
	cout << "  -----------------------------------------------\n\n";
	
	cout << "* * * Elige una opcion para comenzar * * *\n\n";
	
	cout << "1)  Gestionar Jugadores\n";
	cout << "2)  Gestionar Palabras\n";
	cout << "3)  Iniciar Juego\n";
	cout << "4)  Vencedores\n";
	cout << "5)  Salir\n\n";
	
	cout << "> Ingresa tu opcion: ";
	cin >> op;
}
	
// MENU PARA LA GESTION DE JUGADORES
void menu_jugadores(){
	int op;
	do {
		system("cls");
		cout << "\n";
		cout << " +---------------------------------------+\n";
		cout << " |     * Gestion de Jugadores *          |\n";
		cout << " +---------------------------------------+\n\n";
		
		cout << "   1) Registrar Jugador" << endl;
		cout << "   2) Consultar Jugador" << endl;
		cout << "   3) Modificar Jugador" << endl;
		cout << "   4) Eliminar Jugador" << endl;
		cout << "   5) Listar Jugadores" << endl;
		cout << "   6) Volver\n" << endl;
		
		cout << "> Opcion: ";
		cin >> op;
		
		switch (op) {
		case 1: 
			cout << "* * Registrar Jugador * *" << endl; 
			break;
		case 2: 
			cout << "* * Consultar Jugador * *" << endl; 
			break;
		case 3: 
			cout << "* * Modificar Jugador * *" << endl; 
			break;
		case 4: 
			cout << "* * Eliminar Jugador * *" << endl; 
			break;
		case 5: 
			cout << "* * Listar Jugadores * *" << endl; 
			break;
		case 6: 
			cout << "Redirigiendo al menu principal..." << endl;
			break;
		default:
			cout << "OPCION INVALIDA" << endl;
		}
		system("pause");
	} while (op != 6);
}
	
// MENU PARA LA GESTION DE PALABRAS
void menu_palabras(){
	int op;
	do {
		system("cls");
		cout << "\n";
		cout << " +----------------------------------------------+\n";
		cout << " |     * Gestion de Palabras Magicas *          |\n";
		cout << " +----------------------------------------------+\n\n";
		
		cout << "   1) Almacenar Palabra" << endl;
		cout << "   2) Consultar Palabra" << endl;
		cout << "   3) Modificar Palabra" << endl;
		cout << "   4) Eliminar Palabra" << endl;
		cout << "   5) Listar Palabras" << endl;
		cout << "   6) Volver\n" << endl;
		
		cout << "> Opcion: ";
		cin >> op;
		
		switch (op) {
		case 1: 
			cout << "* * Almacenar Palabra * *" << endl; 
			break;
		case 2: 
			cout << "* * Consultar Palabra * *" << endl; 
			break;
		case 3: 
			cout << "* * Modificar Palabra * *" << endl; 
			break;
		case 4: 
			cout << "* * Eliminar Palabra * *" << endl; 
			break;
		case 5: 
			cout << "* * Listar Palabras * *" << endl; 
			break;
		case 6: 
			cout << "Redirigiendo al menu principal..." << endl;
			break;
		default:
			cout << "OPCION INVALIDA" << endl;
		}
		system("pause");
	} while (op != 6);
}
