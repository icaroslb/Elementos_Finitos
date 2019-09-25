#ifndef BARRA_H
#define BARRA_H

#include <vector>
#include <algorithm> 

#define CIRCULO 0;
#define PARALEPIPEDO 1;

struct forca {
	float posicao, magnitude;

	forca (float posi, float mag) : posicao(posi), magnitude(mag) {}
};

inline bool compararForca (forca f1, forca f2) {return (f1.posicao < f2.posicao);}

class Barra {
public:
    float largura,
          altura,
          profundidade,
          material;
    int tipo;
    std::vector <forca> forcas;

	Barra(float nlargura, float naltura, float nprofundidade, float nmaterial, int ntipo, std::vector <forca> nforcas) :
	largura(nlargura), altura(naltura), profundidade(nprofundidade), material(nmaterial), tipo(ntipo), forcas(nforcas) {}
};

#endif