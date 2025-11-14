#include <iostream>
#include <stdio.h>    // Para gets(), fflush(stdin)
#include <stdlib.h>   // Para system("cls"), system("pause"), NULL
#include <string.h>   // Para strcmp(), strcpy() 

using namespace std;
const int MAX = 50; 
typedef char tcad[MAX];

typedef struct tjugador {
    tcad nombre;
    tcad apellido;
    tcad signo;
    tcad alias; 
    int juegos_ganados;
    int mejor_puntaje;
    int puntaje_acumulado;
};

typedef struct tinfo {
    tcad palabra;     
    tcad definicion;
    tcad sinonimo;
};

struct tinfo_ranking {
    tcad alias;
    int puntaje; 
};