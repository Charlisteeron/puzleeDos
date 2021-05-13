// Authors: Carlos Barona y Diego Flores

#pragma once

#include <iostream>

#include "puzzle.h"

using namespace std;

const int MAX_PUZZLES = 100;
const int MODOS = 2;

const string FICHERO = "datosPuzzles.txt";

typedef tPuzzle* tPunteroPuzzle;

struct tListaPuzzles {
	tPunteroPuzzle puzzles[MAX_PUZZLES];
	int numPuzzles = 0;
};

typedef tListaPuzzles tPuzzlesReunidos[MODOS];

//inicializa las dos listas de puzzles
void inicializar(tPuzzlesReunidos & jr);

//carga los datos contenidos en el fichero datosPuzzles.txt. Los datos se encuentran ordenados en el fichero en el mismo orden en que deben estar en la lista, en orden creciente del n�mero de intentos m�ximo para realizar el puzzle y a igualdad de intentos por orden alfab�tico del nombre del puzzle.
bool cargar(tPuzzlesReunidos & jr);

// guarda en el fichero datosPuzzles.txt la lista de puzzles 1D y 2D con el mismo formato del fichero de entrada, y ordenados seg�n est�n en las listas.
void guardar(const tPuzzlesReunidos & listas);

//muestra la lista de puzzles y permite al usuario elegir uno de ellos. Debe dar la opci�n de mostrar la lista de mayor a menor n�mero de movimientos o a la inversa.
int elegirPuzzle(tListaPuzzles & lp);

//Inserta ordenado en la lista de puzzles un nuevo puzzle
bool insertarOrdenado(tListaPuzzles & l, tPunteroPuzzle p);

// Ordena una lista de menor a mayor
void ordenarMayorAMenor(tListaPuzzles& lista);

// Ordena una lista de menor a mayor
void ordenarMenorAMayor(tListaPuzzles& lista);

// Muestra los puzzles de una lista y su modo
void mostrarPuzzles(tListaPuzzles& lista, int modo);