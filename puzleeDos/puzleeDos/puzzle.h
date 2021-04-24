// Authors: Carlos Barona y Diego Flores

#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <iomanip>

#include "matriz.h"
#include "UtilidadesSYS.h"

using namespace std;

struct tPuzzle {
	string nombre;
	string fichero;
	int tipo = 0;
	int maxIntentos = 0;
	int intentosActuales = 0;
	tMatrizChar imagenJugador;
	tMatrizChar imagenObjetivo;
};

// Funcion principal para ejecutar un puzzle
void mainPuzzle(tPuzzle& jpm);

// Trata de cargar la situacion inicial del juego y devuelve true si lo ha hecho correctamente
bool cargar(tPuzzle& jpm);

// Muestra la situacion actual del juego
void mostrar(const tPuzzle& jpm);

// La funcion principal que ejecuta las acciones y muestra la situacion actual y comprueba si ha ganado el jugador o ha perdido (true or false)
bool jugar(tPuzzle& jpm);

// Pide una accion por teclado y comprueba si se ha podido ejecutar correctamente
bool accion(tPuzzle& jpm);

// Operador menor entre 2 puzzles
bool operator<(const tPuzzle& p1, const tPuzzle& p2);

// Operador mayor entre 2 puzzles
bool operator>(const tPuzzle& p1, const tPuzzle& p2);