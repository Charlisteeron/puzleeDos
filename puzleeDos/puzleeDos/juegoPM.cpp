// Authors: Carlos Barona y Diego Flores

#include "juegoPM.h"

// Muestra los puzzles de una lista y su modo
void mostrarPuzzles(tListaPuzzles& lista, int modo);

void mainPuzzlesReunidos() {
	tPuzzlesReunidos puzzles;
	bool jugamos = true;
	int numOpc = 0, indicePuzzle = 0, modo = 0;
	string nombre, archivo;

	// Inicializamos los puzzles
	inicializar(puzzles);

	if (cargar(puzzles)) {

		while (jugamos) {
			numOpc = menu();
			numOpc--;

			switch (numOpc) {

			case 0:
				do {
					if (indicePuzzle == -1) {
						ordenarMayorAMenor(puzzles[numOpc]);
					}
					else if (indicePuzzle == -2) {
						ordenarMenorAMayor(puzzles[numOpc]);
					}

					indicePuzzle = elegirPuzzle(puzzles[numOpc]);

				} while (indicePuzzle > puzzles[numOpc].numPuzzles || indicePuzzle < 0);

				if (indicePuzzle != 0) {
					mainPuzzle(*puzzles[numOpc].puzzles[indicePuzzle - 1]);
				}

				break;
			
			case 1:
				do {
					if (indicePuzzle == -1) {
						ordenarMayorAMenor(puzzles[numOpc]);
					}
					else if (indicePuzzle == -2) {
						ordenarMenorAMayor(puzzles[numOpc]);
					}

					indicePuzzle = elegirPuzzle(puzzles[numOpc]);

				} while (indicePuzzle > puzzles[numOpc].numPuzzles || indicePuzzle < 0);

				if (indicePuzzle != 0) {
					mainPuzzle(*puzzles[numOpc].puzzles[indicePuzzle - 1]);
				}

				break;

			case 2:
			
				mostrarPuzzles(puzzles[0], 0);
				mostrarPuzzles(puzzles[1], 1);

				cout << "Escriba el nombre del puzzle : ";
				getline(cin, nombre);

				cout << "Escriba nombre del fichero en que se encuentra: ";
				cin >> archivo;

				cin.ignore();

				// Comprueba si el nombre del fichero es para el modo 1D o 2D
				if (archivo.substr(archivo.length() - 7, 7) == "_1D.txt") {
					modo = 1;
					
				}
				else {
					modo = 2;
				}

				// Creamos un puntero auxiliar y lo inicializamos en el heap
				tPunteroPuzzle aux;
				aux = new tPuzzle;

				aux->nombre = nombre;
				aux->fichero = archivo;
				aux->tipo = modo - 1;

				// Si lo puede cargar, comprueba si ya existe y muestra la lista y si no borra el puzzle del heap
				if (cargar(*aux)) {

					if (insertarOrdenado(puzzles[modo - 1], aux)) {
						cout << "\n\nEse puzzle ya exite\n\n";
					}

					if (modo == 1) {
						mostrarPuzzles(puzzles[0], 0);
					}
					else if (modo == 2) {
						mostrarPuzzles(puzzles[1], 1);
					}

					cout << "Fichero añadido correctamente =)" << endl;
				}
				else {
					delete aux;
					cout << "No se pudo añadir el archivo =(" << endl;
				}

				break;
			
			case -1:

				// Al salir guardamos en el fichero y dejamos de jugar
				guardar(puzzles);

				delete [] puzzles[0].puzzles;
				delete [] puzzles[1].puzzles;

				jugamos = false;
				break;
			}
		}
	}
	else {
		cout << "\n\nNo se pudo abrir el archivo fuente\n\n";
	}
}

int menu() {
	int opcion = 0;

	cout << "\n\n";
	cout << "1 <-> Resolver un puzzle 1D" << endl;
	cout << "2 <-> Resolver un puzzle 2D" << endl;
	cout << "3 <-> Añadir un puzzle al catálogo" << endl;
	cout << "0 <-> Salir" << endl;

	do {
		cout << "Elige una opción: ";
		cin >> opcion;
	} while (opcion > 3 || opcion < 0);
	cin.ignore();

	cout << "\n\n";

	return opcion;
}

void mostrarPuzzles(tListaPuzzles& lista, int modo) {
	if (modo == 0) {
		cout << "Juegos 1D" << endl;
	}
	else if (modo == 1) {
		cout << endl << "Juegos 2D" << endl;
	}

	for (int i = 0; i < lista.numPuzzles; i++) {
		cout << i + 1 << " <-> " << lista.puzzles[i]->nombre << " con un máximo de " << lista.puzzles[i]->maxIntentos << " intentos." << endl;
	}
}