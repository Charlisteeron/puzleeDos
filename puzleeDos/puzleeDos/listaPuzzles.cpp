// Authors: Carlos Barona y Diego Flores

#include "listaPuzzles.h"

bool buscar(const tListaPuzzles& lista, tPunteroPuzzle puzzle, int& pos);

void inicializar(tPuzzlesReunidos& jr) {
	// Iniciamos las direcciones en NULL
	for (int i = 0; i < MAX_PUZZLES; i++) {
		jr[0].puzzles[i] = NULL;
		jr[1].puzzles[i] = NULL;
	}

	// Iniciamos los contadores
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
			jr[i].numPuzzles = numP;

			for (int x = 0; x < jr[i].numPuzzles; x++) {
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

bool insertarOrdenado(tListaPuzzles& l, tPunteroPuzzle p) { // *tPuzzle -> tPunteroPuzzle
	int indice = 0;
	bool existe = buscar(l, p, indice);

	if (!existe && l.numPuzzles < MAX_PUZZLES) {
		l.numPuzzles++;

		for (int i = l.numPuzzles - 1; i > indice; i--) {
			l.puzzles[i] = l.puzzles[i - 1];
		}

		cout << "hola" << endl;

		l.puzzles[indice] = p;

	}

	return existe;
}

bool buscar(const tListaPuzzles& lista, tPunteroPuzzle puzzle, int& pos) { // *tPuzzle -> tPunteroPuzzle
	//Te quiero <3 YO MAS

	bool existe = false;
	int inicio = 0, final = lista.numPuzzles - 1, mitad;

	while ((inicio <= final) && !existe) {
		mitad = (inicio + final) / 2;

		if (*puzzle < *lista.puzzles[mitad]) {
			final = mitad - 1;
		}
		else if (*lista.puzzles[mitad] < *puzzle) {
			inicio = mitad + 1;
		}
		else {
			existe = true;
		}
	}

	if (existe) {
		pos = mitad;
	}
	else {
		pos = inicio;
	}

	return existe;
}

void ordenarMayorAMenor(tListaPuzzles& lista) {
	for (int i = 0; i < lista.numPuzzles - 1; i++) {

		for (int x = lista.numPuzzles - 1; x > i; x--) {
			if (*lista.puzzles[x] > *lista.puzzles[x - 1]) {

				tPunteroPuzzle aux = lista.puzzles[x];
				lista.puzzles[x] = lista.puzzles[x - 1];
				lista.puzzles[x - 1] = aux;
			}
		}
	}
}

void ordenarMenorAMayor(tListaPuzzles& lista) {
	for (int i = 0; i < lista.numPuzzles - 1; i++) {

		for (int x = lista.numPuzzles - 1; x > i; x--) {
			if (*lista.puzzles[x] < *lista.puzzles[x - 1]) {
				
				tPunteroPuzzle aux = lista.puzzles[x];
				lista.puzzles[x] = lista.puzzles[x - 1];
				lista.puzzles[x - 1] = aux;
			}
		}
	}
}