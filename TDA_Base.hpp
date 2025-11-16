#ifndef TDA_BASE_HPP
#define TDA_BASE_HPP

#include <iostream>
#include <stdio.h>    
#include <stdlib.h>   
#include <string.h>  

using namespace std;

//const int MAX = 50; 
typedef char tcad[30];

typedef struct tjugador{
	tcad nombre;
	tcad apellido;
	tcad signo;
	tcad alias; 
	int juegos_ganados;
	int mejor_puntaje;
	int puntaje_acumulado;
};

typedef struct tpalabra {
    tcad palabra; 
	int longitud; 
    tcad definicion;
    tcad sinonimo;
};

typedef struct tinfo_ranking {
    tcad alias;
    int puntaje; 
};

#endif 
