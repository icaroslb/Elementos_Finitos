#include <vector>

struct forca {
	float posicao, magnitude;
};

#define CIRCULO 0;
#define PARALEPIPEDO 1;

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
