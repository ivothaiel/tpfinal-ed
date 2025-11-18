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
    cout << "5)  Salir del Juego\n\n";
    cout << "> Ingresa tu opcion: ";
    cin >> op;
}

void submenu_modificar_jugador(char &op){
    cout << "\n";
    cout << " +---------------------------------------+\n";
    cout << " |        * Modificar Jugador * |\n";
    cout << " +---------------------------------------+\n\n";
    cout << "   1) Editar Nombre" << endl;
    cout << "   2) Editar Apellido" << endl;
    cout << "   3) Editar Signo Zodiacal" << endl;
    cout << "   0) Volver\n" << endl;
    cout << "> Opcion: ";
    cin >> op;
}