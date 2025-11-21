#include <iostream>

using namespace std;

// MENU PRINCIPAL DEL JUEGO
void menu_principal(char &op){
    cout << "\n\n";
    cout << "+-------------------------------------------------------+\n";
    cout << "|                                                       |\n";
    cout << "|       E L  H E C H I Z O  D E L  E S P E J O          |\n";
    cout << "|                                                       |\n";
    cout << "+-------------------------------------------------------+\n";
    cout << "\n";
    cout << "  -----------------------------------------------\n";
    cout << "   En la antiguedad, una princesa fue\n"; 
    cout << "   atrapada en un espejo maldito. Solo quien\n";
    cout << "   descubra las 6 palabras magicas podra romper\n";
    cout << "   el hechizo y liberarla...\n";
    cout << "  -----------------------------------------------\n\n";
    cout << "* * * Elige una opcion para comenzar * * *\n\n";
    cout << "  1)  Gestionar Jugadores\n";
    cout << "  2)  Gestionar Palabras\n";
    cout << "  3)  Iniciar Juego\n";
    cout << "  4)  Vencedores\n";
    cout << "  0)  Salir del Juego\n\n";
    cout << "> Opcion: ";
    cin >> op;
}

void submenu_modificar_jugador(char &op){
    cout << "\n";
    cout << " +---------------------------------------+\n";
    cout << " |        * Modificar Jugador *          |\n";
    cout << " +---------------------------------------+\n\n";
    cout << "   1) Editar Nombre" << endl;
    cout << "   2) Editar Apellido" << endl;
    cout << "   3) Editar Signo Zodiacal" << endl;
    cout << "   0) Volver\n" << endl;
    cout << "> Opcion: ";
    cin >> op;
}
	
void cartel_inicio_juego(){
	limpiarPantalla();
	cout << "===============================================================\n";
	cout << "||                                                           ||\n";
	cout << "||          L A   P R I N C E S A   D E   F U E G O          ||\n";
	cout << "||                                                           ||\n";
	cout << "||   -----------------------------------------------------   ||\n";
	cout << "||        PRESIONA UNA TECLA PARA INICIAR LA AVENTURA        ||\n";
	cout << "||   -----------------------------------------------------   ||\n";
	cout << "||                                                           ||\n";
	cout << "===============================================================\n";
	pausarPantalla();
}

void juego_cancelado(){
	cout << endl;
	cout << "+---------------------------------------+\n";
	cout << "|    P A R T I D A  C A N C E L A D A   |\n"; 
	cout << "+---------------------------------------+\n";
}
	
void bienvenida(tcad alias){
	limpiarPantalla();
	cout << endl;
	cout << "------------------------------------------------------\n";
	cout << "|       ¡ B I E N V E N I D O  A L  J U E G O !      |\n";
	cout << "------------------------------------------------------\n";
	cout << " La aventura comienza, el destino de la princesa\n";
	cout << " Karym Su Yang esta en tus manos " << alias << "\n";
	cout << " \n ¡Que el fuego te acompañe!\n";
	pausarPantalla();
}
	
void cartel_victoria(){
	limpiarPantalla();
	cout << "\n";
	cout << "=====================================================\n";
	cout << "|                                                   |\n";
	cout << "|    ¡ H A S  R O T O  L A  M A L D I C I O N !     |\n";
	cout << "|                                                   |\n";
	cout << "|  	  Adivinaste las 6 palabras magicas y        |\n";
	cout << "|      el espejo ancestral se ha roto por fin       |\n";
	cout << "|                                                   |\n";
	cout << "|     La princesa Karym Su Yang ha sido liberada    |\n";
	cout << "|      del hechicero después de mas de 500 años     |\n";
	cout << "|                                                   |\n";
	cout << "|       El Reino de Fuego celebra tu valentia       |\n";
	cout << "|                                                   |\n";
	cout << "=====================================================\n";
	cout << "\n";
	pausarPantalla();
}
	
void cartel_derrota(){
	cout << "\n";
	cout << "=====================================================\n";
	cout << "|                                                   |\n";
	cout << "|            ¡ H A S  F A L L A D O !               |\n";
	cout << "|                                                   |\n";
	cout << "|   Las palabras magicas permaneceran ocultas       |\n";
	cout << "|     dentro de las joyas del espejo...             |\n";
	cout << "|                                                   |\n";
	cout << "|   Tu destino es convertirte en piedra para        |\n";
	cout << "|     toda la eternidad...                          |\n";
	cout << "|                                                   |\n";
	cout << "=====================================================\n";
	cout << "\n";
}
