// Authors: Carlos Barona y Diego Flores

#include <iostream>
#include "checkML.h"
#include "juegoPM.h"

int main() {
	// Llamamos a las funciones para mirar la memoria no liberada y la pagina de codigos activa
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	chcp1252();

	// Ejecutamos el programa
	mainPuzzlesReunidos();
	return 0;
}