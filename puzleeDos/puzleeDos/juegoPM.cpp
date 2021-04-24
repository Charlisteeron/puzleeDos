#include "juegoPM.h"

void mostrarPuzzles(tListaPuzzles& lista, int modo);

void mainPuzzlesReunidos() {
	tPuzzlesReunidos puzzles;
	bool jugamos = true;
	int opcion = 0, indicePuzzle = 0, modo = 0;
	string nombre, archivo;


	inicializar(puzzles);

	if (cargar(puzzles)) {

		while (jugamos) {
			opcion = menu();

			switch (opcion) {

			case 1:
				do {
					if (indicePuzzle == -1) {
						ordenarMayorAMenor(puzzles[0]);
					}
					else if (indicePuzzle == -2) {
						ordenarMenorAMayor(puzzles[0]);
					}

					indicePuzzle = elegirPuzzle(puzzles[0]);

				} while (indicePuzzle > puzzles[0].numPuzzles || indicePuzzle < 0);

				if (indicePuzzle != 0) {
					mainPuzzle(*puzzles[0].puzzles[indicePuzzle - 1]);
				}

				break;
			
			case 2:
				do {
					if (indicePuzzle == -1) {
						ordenarMenorAMayor(puzzles[1]);
					}
					else if (indicePuzzle == -2) {
						ordenarMenorAMayor(puzzles[1]);
					}

					indicePuzzle = elegirPuzzle(puzzles[1]);

				} while (indicePuzzle > puzzles[1].numPuzzles || indicePuzzle < 0);

				if (indicePuzzle != 0) {
					mainPuzzle(*puzzles[1].puzzles[indicePuzzle - 1]);
				}

				break;

			case 3:
			
				mostrarPuzzles(puzzles[0], 0);
				mostrarPuzzles(puzzles[1], 1);

				cout << "Escriba el nombre del puzzle : ";
				getline(cin, nombre);

				cout << "Escriba nombre del fichero en que se encuentra: ";
				cin >> archivo;

				cout << "Introduzca el modo del puzzle: ";
				do {
					cin >> modo;
				} while (modo > 2 || modo < 1);

				cin.ignore();


				tPunteroPuzzle aux;
				aux = new tPuzzle;

				aux->nombre = nombre;
				aux->fichero = archivo;
				aux->tipo = modo - 1;


				if (cargar(*aux)) {

					if (!insertarOrdenado(puzzles[modo - 1], aux)) {
						cout << "\n\nEse puzzle ya exite\n\n";
					}

					if (modo == 1) {
						mostrarPuzzles(puzzles[0], 0);
					}
					else if (modo == 2) {
						mostrarPuzzles(puzzles[1], 1);
					}

					cout << "Fichero a�adido correctamente =)" << endl;
				}
				else {
					delete aux;
					cout << "No se pudo a�adir el archivo =(" << endl;
				}

				break;
			
			case 0:
				guardar(puzzles);
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
	cout << "3 <-> A�adir un puzzle al cat�logo" << endl;
	cout << "0 <-> Salir" << endl;

	do {
		cout << "Elige una opci�n: ";
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
		cout << i + 1 << " <-> " << lista.puzzles[i]->nombre << " con un m�ximo de " << lista.puzzles[i]->maxIntentos << " intentos." << endl;
	}
}