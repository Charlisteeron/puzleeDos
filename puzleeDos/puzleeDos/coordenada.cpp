// Authors: Carlos Barona y Diego Flores

#include "coordenada.h"

bool operator == (tCoor c1, tCoor c2) {
	return (c1.F == c2.F) && (c1.C == c2.C);
}

bool operator != (tCoor c1, tCoor c2) {
	return !(c1 == c2);
}

tCoor operator + (tCoor c1, tCoor c2) {
	return {c1.F + c2.F, c1.C + c2.C};
}