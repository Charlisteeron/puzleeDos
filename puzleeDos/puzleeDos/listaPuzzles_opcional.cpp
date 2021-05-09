// Authors: Carlos Barona y Diego Flores

#include "listaPuzzles_opcional.h"

void aumentarMemoria(tListaPuzzles& p);
bool buscar(const tListaPuzzles& lista, tPunteroPuzzle puzzle, int& pos, int inicio, int final);

void inicializar(tPuzzlesReunidos& jr) {
	for (int i = 0; i < MAX_PUZZLES; i++) {
		jr[0].puzzles[i] = NULL;
		jr[1].puzzles[i] = NULL;
	}

	jr[0].numPuzzles = 0;
	jr[1].numPuzzles = 0;
}

bool cargar(tPuzzlesReunidos& jr) {
	bool cargado = false;
	ifstream archivo;

	int numP = 0;
	string nombre, fichero;

	archivo.open(FICHERO);

	if (archivo.is_open()) {
		// Realiza la lectura 2 veces (1D y 2D)
		for (int i = 0; i < MODOS; i++) {
			archivo >> numP;
			archivo.ignore();
			//jr[i].numPuzzles = numP;

			for (int x = 0; x < numP; x++) {

				if (jr[i].numPuzzles == jr[i].maxActual) {
					// Aumentamos memoria
					aumentarMemoria(jr[i]);
				}

				// Leemos nombre y fichero
				getline(archivo, nombre);
				getline(archivo, fichero);

				// Creamos un puzzle en el heap
				jr[i].puzzles[x] = new tPuzzle;

				// Actualizamos sus valores
				jr[i].puzzles[x]->nombre = nombre;
				jr[i].puzzles[x]->fichero = fichero;
				jr[i].puzzles[x]->tipo = i;


				if (!cargar(*jr[i].puzzles[x])) {
					cout << "\n\nNo se pudo cargar el puzzle numero " << x << "\n\n";
				}

				jr[i].numPuzzles++;
			}
		}

		cargado = true;

		archivo.close();
	}
	else {
		cout << "\n\nNo se pudo abrir el archivo AAAA\n\n";
	}


	return cargado;
}

void aumentarMemoria(tListaPuzzles& p) {
	p.maxActual++;
	
	int maximoActual = p.maxActual;
	int numP = p.numPuzzles;

	tPunteroAPunteroPuzzle puzzlesAux = new tPunteroPuzzle[maximoActual];


	for (int i = 0; i < maximoActual - 1; i++) {
		puzzlesAux[i] = p.puzzles[i];
	}

	puzzlesAux[maximoActual - 1] = NULL;

	delete[] p.puzzles;

	p.puzzles = new tPunteroPuzzle[maximoActual];

	for (int i = 0; i < p.maxActual - 1; i++) {
		p.puzzles[i] = puzzlesAux[i];
	}

	delete[] puzzlesAux;
}

void guardar(const tPuzzlesReunidos& listas) {
	ofstream archivo;

	archivo.open(FICHERO);

	if (archivo.is_open()) {
		for (int i = 0; i < 2; i++) {
			archivo << listas[i].numPuzzles << endl;
			for (int j = 0; j < listas[i].numPuzzles; j++) {
				archivo << listas[i].puzzles[j]->nombre << endl;
				archivo << listas[i].puzzles[j]->fichero << endl;

				delete listas[i].puzzles[j];

				// Guarda en el archivo y borra los elementos del heap
			}
		}
		archivo.close();
	}
	else {
		cout << "\n\nNo se pudo abrir el archivo\n\n";
	}
}

int elegirPuzzle(tListaPuzzles& lp) {
	int opcion = 0;

	for (int i = 0; i < lp.numPuzzles; i++) {
		cout << i + 1 << " <-> " << lp.puzzles[i]->nombre << " con un máximo de " << lp.puzzles[i]->maxIntentos << " intentos." << endl;
	}
	cout << "0 <-> Salir" << endl;
	cout << "-1 <-> Ordenar la lista de mayor a menor" << endl;
	cout << "-2 <-> Ordenar la lista de menor a mayor" << endl;

	cout << "Elige una opcion: ";
	cin >> opcion;

	cin.ignore();

	cout << endl;

	return opcion;
}

bool insertarOrdenado(tListaPuzzles& l, tPunteroPuzzle p) {
	int indice = 0;
	bool existe = buscar(l, p, indice, 0, l.numPuzzles);

	if (!existe) {
		aumentarMemoria(l);
		l.numPuzzles++;
		
		for (int i = l.numPuzzles - 1; i > indice; i--) {
			l.puzzles[i] = l.puzzles[i - 1];
		}

		l.puzzles[indice] = p;
	}

	return existe;
}

bool buscar(const tListaPuzzles& lista, tPunteroPuzzle puzzle, int& pos, int inicio, int final) {
	bool existe = false;
	
	if (inicio <= final) {
		int mitad = (inicio + final) / 2;

		if (*puzzle < *lista.puzzles[mitad]) {
			existe = buscar(lista, puzzle, pos, inicio, mitad - 1);
		}
		else if (*lista.puzzles[mitad] < *puzzle) {
			existe = buscar(lista, puzzle, pos, mitad + 1, final);
		}
		else {
			pos = mitad;
			existe = true;
		}
	}
	else {
		pos = inicio;
		existe = false;
	}

	return existe;
}

void mezclar(tListaPuzzles& lista, int inicio, int mitad, int final, int caso) {
	int numElementosIzq = mitad - inicio + 1;
	int numElementosDer = final - mitad;

	tListaPuzzles elementosIzq, elementosDer;

	for (int i = 0; i < numElementosIzq; i++) {

		if (elementosIzq.numPuzzles == elementosIzq.maxActual) {
			aumentarMemoria(elementosIzq);
		}

		elementosIzq.puzzles[i] = lista.puzzles[inicio + i];
		elementosIzq.numPuzzles++;
	}

	for (int i = 0; i < numElementosDer; i++) {

		if (elementosDer.numPuzzles == elementosDer.maxActual) {
			aumentarMemoria(elementosDer);
		}

		elementosDer.puzzles[i] = lista.puzzles[mitad + 1 + i];
		elementosDer.numPuzzles++;
	}

	int pos1 = 0, pos2 = 0;
	int aux = inicio;

	switch (caso){
	case 1: // Mayor a menor
		
		while (pos1 < numElementosIzq || pos2 < numElementosDer) {
			if (pos1 < numElementosIzq && pos2 < numElementosDer) {
				if (*elementosIzq.puzzles[pos1] > *elementosDer.puzzles[pos2]) {
					lista.puzzles[aux] = elementosIzq.puzzles[pos1];
					pos1++;
				}
				else {
					lista.puzzles[aux] = elementosDer.puzzles[pos2];
					pos2++;
				}
			}
			else if (pos1 >= numElementosIzq) {
				lista.puzzles[aux] = elementosDer.puzzles[pos2];
				pos2++;
			}
			else if (pos2 >= numElementosDer) {
				lista.puzzles[aux] = elementosIzq.puzzles[pos1];
				pos1++;
			}

			aux++;
		}
		
		break;

	case 2: // Menor a mayor
		
		while (pos1 < numElementosIzq || pos2 < numElementosDer) {
				
			if (pos1 < numElementosIzq && pos2 < numElementosDer) {
				if (*elementosIzq.puzzles[pos1] < *elementosDer.puzzles[pos2]) {
					lista.puzzles[aux] = elementosIzq.puzzles[pos1];
					pos1++;
				}
				else {
					lista.puzzles[aux] = elementosDer.puzzles[pos2];
					pos2++;
				}
			}
			else if (pos1 >= numElementosIzq) {
				lista.puzzles[aux] = elementosDer.puzzles[pos2];
				pos2++;
			}
			else if (pos2 >= numElementosDer) {
				lista.puzzles[aux] = elementosIzq.puzzles[pos1];
				pos1++;
			}

			aux++;
		}

		break;

	default:
		break;
	}
}

void ordenarMayorAMenor(tListaPuzzles& lista, int inicio, int final) {
	if (inicio < final) {
		int mitad = (inicio + final) / 2;
		ordenarMayorAMenor(lista, inicio, mitad);
		ordenarMayorAMenor(lista, mitad + 1, final);

		mezclar(lista, inicio, mitad, final, 1);
	}
}

void ordenarMayorAMenor(tListaPuzzles& lista) {
	ordenarMayorAMenor(lista, 0, lista.numPuzzles - 1);
}

void ordenarMenorAMayor(tListaPuzzles& lista, int inicio, int final) {
	if (inicio < final) {
		int mitad = (inicio + final) / 2;
		ordenarMenorAMayor(lista, inicio, mitad);
		ordenarMenorAMayor(lista, mitad + 1, final);

		mezclar(lista, inicio, mitad, final, 2);
	}
}

void ordenarMenorAMayor(tListaPuzzles& lista) {
	ordenarMenorAMayor(lista, 0, lista.numPuzzles - 1);
}