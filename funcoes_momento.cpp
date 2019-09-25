#include "funcoes_momento.h"

float momentoMaximo (Barra &modelo) {
	float momentoMax = 0,
	      somaForcas,
	      posicao;
	std::sort (modelo.forcas.begin(), modelo.forcas.end(), compararForca);

	for (auto dist = std::begin(modelo.forcas); dist < std::end(modelo.forcas); dist++) {
		posicao = dist->posicao;
		somaForcas = 0;
		
		for (auto f = std::begin(modelo.forcas); f < dist; f++) {
			somaForcas += f->magnitude * (posicao - f->posicao);
		}

		if (std::abs(somaForcas) > std::abs(momentoMax)) {
			momentoMax = somaForcas;
		}
	}

	return momentoMax;
}

float MomentoInercia (Barra &modelo) {

}

float estresseMaximo (Barra &modelo) {
	
}