#include <iostream>
#include "funcoes_momento.h"

int main () {
	std::vector <forca> forcas;

	forcas.push_back(forca(0, -8.9));
	forcas.push_back(forca(0.2, 8.9));
	forcas.push_back(forca(1.65, 8.9));
	forcas.push_back(forca(1.85, -8.9));

	Barra barra(1.85, 0.16, 0, 0, 0, forcas);

	std::cout << momentoMaximo(barra) << "\n";

	return 0;
}