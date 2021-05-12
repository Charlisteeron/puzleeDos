// Authors: Carlos Barona y Diego Flores

#include "puzzle.h"

void mostrarHelp(); // Hace un cout de todos los comandos disponnibles
int acciones(string comando, int modo); // Devuelve un entero en funcion del comando introducido y del modo en el que este el jugador

void mainPuzzle(tPuzzle& jpm) {
	bool haGanado = jugar(jpm);

	if (haGanado) {
		cout << "\n\nLO CONSEGUISTE!!\n\n";
	}
	else {
		cout << "\n\nPerdiste :(\n\n";
	}

	// Carga de nuevo el puzzle
	cargar(jpm);
}

bool cargar(tPuzzle& jpm) {
	bool cargado = false;
	ifstream archivo;

	archivo.open(jpm.fichero);

	if (archivo.is_open()) {
		// Carga la imagen del jugador y a continuación la imagen objetivo
		if (!cargar(jpm.imagenJugador, archivo) || !cargar(jpm.imagenObjetivo, archivo)) {
			cargado = false;
		}
		else {
			archivo >> jpm.maxIntentos;
			archivo.ignore();
			cargado = true;
		}

		archivo.close();
	}
	else {
		cout << "\n\nNo se pudo abrir el archivo\n\n";
	}

	return cargado;
}

void mostrar(const tPuzzle& jpm) {
	// IMAGEN JUGADOR
	mostrar(jpm.imagenJugador);

	cout << "\n\n";

	// IMAGEN OBJETIVO
	mostrar(jpm.imagenObjetivo);

	cout << "\n";

	// Muestra los intentos
	cout << "INTENTOS" << endl;
	cout << "Máximos: " << jpm.maxIntentos << endl;
	cout << "Actuales: " << jpm.intentosActuales << endl;
	cout << "Restantes: " << jpm.maxIntentos - jpm.intentosActuales << endl;

	cout << "\n\n";
}

bool jugar(tPuzzle& jpm) {
	bool ganador = true;

	// Muestra el tablero antes de empezar
	mostrar(jpm);

	while (jpm.intentosActuales < jpm.maxIntentos && !(jpm.imagenJugador == jpm.imagenObjetivo)) {

		// Si la accion es valida cuenta un intento
		if (accion(jpm)) {
			jpm.intentosActuales++;
		}

		mostrar(jpm);
		pausa();
	}

	// Si al acabar de jugar la imagen es distinta o se ha pasado de intentos cuenta como perdido
	if (!(jpm.imagenJugador == jpm.imagenObjetivo)) {
		ganador = false;
	}
	else if (jpm.intentosActuales > jpm.maxIntentos) {
		ganador = false;
	}

	return ganador;
}

bool accion(tPuzzle& jpm) {
	string accion = "", comando, espacio = " ";
	int aux1 = -100, aux2 = -100, aux3 = -100, aux4 = -100;
	bool accionPermitida = true;

	// Pide la accion por pantalla
	cout << "Introduzca una accion: (HP para ayuda) ";
	cin >> accion;

	// acciones() devuelve el numero del case en funcion del comando y del modo
	int n = acciones(accion, jpm.tipo);

	// 2 switchs, 1 para cada modo, dentro de cada uno de ellos se lee los demas numeros auxiliares
	if (jpm.tipo == 0) {
		switch (n) {

		case 1:
			cin >> aux1 >> aux2;
			cin.ignore();

			if (!swapF(jpm.imagenJugador, aux1, aux2)) {
				accionPermitida = false;
			}
			break;

		case 2:
			cin >> aux1 >> aux2;
			cin.ignore();

			if (!swapC(jpm.imagenJugador, aux1, aux2)) {
				accionPermitida = false;
			}
			break;

		case 3:
			cin >> aux1;
			cin.ignore();

			if (!swapD(jpm.imagenJugador, aux1)) {
				accionPermitida = false;
			}
			break;

		case 4:
			cin >> aux1;
			cin.ignore();

			if (!voltearF(jpm.imagenJugador, aux1)) {
				accionPermitida = false;
			}
			break;

		case 5:
			cin >> aux1;
			cin.ignore();

			if (!voltearC(jpm.imagenJugador, aux1)) {
				accionPermitida = false;
			}
			break;

		case 6:
			cin >> aux1;
			cin.ignore();

			if (!voltearD(jpm.imagenJugador, aux1)) {
				accionPermitida = false;
			}
			break;

		case 7:
			mostrarHelp();
			accionPermitida = false;
			break;

		default:
			cout << "Comando no reconocido, help para mostrar comandos permitidos" << endl;
			accionPermitida = false;
			break;
		}
	}
	else  if (jpm.tipo == 1) {
		switch (n) {

		case 1:
			voltearV(jpm.imagenJugador);
			break;

		case 2:
			voltearH(jpm.imagenJugador);
			break;

		case 3:
			rotarD(jpm.imagenJugador);
			break;

		case 4:
			cin >> aux1 >> aux2 >> aux3 >> aux4;
			cin.ignore();

			if (!swapAdy(jpm.imagenJugador, { aux1, aux2 }, { aux3, aux4 })) {
				accionPermitida = false;
			}
			break;

		case 5:

			if (!voltearID(jpm.imagenJugador)) {
				accionPermitida = false;
			}
			break;

		case 6:
			mostrarHelp();
			accionPermitida = false;
			break;

		default:
			cout << "\n\nComando no reconocido, help para mostrar comandos permitidos\n\n";
			accionPermitida = false;
			break;
		}
	}
	else {
		cout << "Modo no reconocido" << endl;
	}

	if (!accionPermitida) {
		cout << "\n\nNo se pudo realizar la acción\n\n";
	}

	return accionPermitida;
}

bool operator<(const tPuzzle& p1, const tPuzzle& p2) {
	if (p1.maxIntentos == p2.maxIntentos) {
		return p1.nombre < p2.nombre;
	}

	return p1.maxIntentos < p2.maxIntentos;
}

bool operator>(const tPuzzle& p1, const tPuzzle& p2) {
	if (p1.maxIntentos == p2.maxIntentos) {
		return p1.nombre > p2.nombre;
	}

	return p1.maxIntentos > p2.maxIntentos;
}

void mostrarHelp() {
	cout << "\n\n";
	cout << "Comandos permitidos!!" << endl;
	cout << "MODO 1D" << endl;
	cout << "SF * + : Intercambiar las filas * y +" << endl;
	cout << "SC * + : Intercambiar las columnas * y +" << endl;
	cout << "SD * : Intercambia las diagonales * y -*" << endl;
	cout << "VF * : Voltea la fila *" << endl;
	cout << "VC * : Voltea la columna *" << endl;
	cout << "VD * : Voltea al diagonal *" << endl;
	cout << "\n";
	cout << "MODO 2D" << endl;
	cout << "VV : Voltear con respecto a la Vertical" << endl;
	cout << "VH : Voltear con respecto a la Horizontal" << endl;
	cout << "RD : Rotar en sentido horario" << endl;
	cout << "SA + * # ~ : Intercambia las posiciones de las vecinas de las coordenadas {+, *} y {#, ~}" << endl;
	cout << "VD : Voltear con respecto a la diagonal principal" << endl;
	cout << "\n\n";
}

int acciones(string comando, int modo) {
	int ind = -1;

	// Los .length() se usan para comprobar que la cadena no viene solo con el comando sin indicar los demas valores

	if (modo == 0) {
		if (comando == "SF") {
			ind = 1;
		}
		else if (comando == "SC") {
			ind = 2;
		}
		else if (comando == "SD") {
			ind = 3;
		}
		else if (comando == "VF") {
			ind = 4;
		}
		else if (comando == "VC") {
			ind = 5;
		}
		else if (comando == "VD") {
			ind = 6;
		}
		else if (comando == "HP") {
			ind = 7;
		}
	}

	else if (modo == 1) {
		if (comando == "VV") {
			ind = 1;
		}
		else if (comando == "VH") {
			ind = 2;
		}
		else if (comando == "RD") {
			ind = 3;
		}
		else if (comando == "SA") {
			ind = 4;
		}
		else if (comando == "VD") {
			ind = 5;
		}
		else if (comando == "HP") {
			ind = 6;
		}
	}

	return ind;
}