// Authors: Carlos Barona y Diego Flores

#pragma once

#include <iostream>

#include "puzzle.h"

using namespace std;

const int MAX_PUZZLES = 3;
const int MODOS = 2;
const int AUMENTAR_MEMORIA_EN = 1;

const string FICHERO = "datosPuzzles.txt";

typedef tPuzzle* tPunteroPuzzle;
typedef tPunteroPuzzle* tPunteroAPunteroPuzzle;

struct tListaPuzzles {
	tPunteroAPunteroPuzzle puzzles = new tPunteroPuzzle[MAX_PUZZLES];
	int numPuzzles = 0;
	int maxActual = MAX_PUZZLES;
};

typedef tListaPuzzles tPuzzlesReunidos[MODOS];

// Inicializa las dos listas de puzzles
void inicializar(tPuzzlesReunidos& jr);

// Carga los datos contenidos en el fichero datosPuzzles.txt. Los datos se encuentran ordenados en el fichero en el mismo orden en que deben estar en la lista, en orden creciente del número de intentos máximo para realizar el puzzle y a igualdad de intentos por orden alfabético del nombre del puzzle.
bool cargar(tPuzzlesReunidos& jr);

// Guarda en el fichero datosPuzzles.txt la lista de puzzles 1D y 2D con el mismo formato del fichero de entrada, y ordenados según están en las listas.
void guardar(const tPuzzlesReunidos& listas);

// Muestra la lista de puzzles y permite al usuario elegir uno de ellos. Debe dar la opción de mostrar la lista de mayor a menor número de movimientos o a la inversa.
int elegirPuzzle(tListaPuzzles& lp);

// Inserta ordenado en la lista de puzzles un nuevo puzzle
bool insertarOrdenado(tListaPuzzles& l, tPunteroPuzzle p);

// Ordena una lista de menor a mayor
void ordenarMayorAMenor(tListaPuzzles& lista);

// Ordena una lista de menor a mayor
void ordenarMenorAMayor(tListaPuzzles& lista);

// Muestra los puzzles de una lista y su modo
void mostrarPuzzles(tListaPuzzles& lista, int modo);

// Llama a mainPuzzle()
void jugarPuzzle(tListaPuzzles& lista, int puzzle);