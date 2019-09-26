#ifndef BARRA_H
#define BARRA_H

#include <vector>
#include <algorithm> 
#include <GL/gl.h>

#define CIRCULO 0;
#define RETANGULO 1;

struct forca {
	float posicao, magnitude;

	forca (float posi, float mag) : posicao(posi), magnitude(mag) {}
    void desenhar (float altura) {
        if (magnitude < 0){
            glColor3f(1.0, 0.0, 0.0);
        } else {
            altura *= -1.0;
            glColor3f(0.0, 1.0, 0.0);
        }

        glBegin(GL_LINES);
            glVertex3f(posicao, altura, 0);
            glVertex3f(posicao, (altura - magnitude), 0);
        glEnd();
    }
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

	Barra(float nlargura, float naltura, float nprofundidade, float nmaterial, int ntipo) :
	largura(nlargura), altura(naltura), profundidade(nprofundidade), material(nmaterial), tipo(ntipo), forcas() {}

    bool inserirForca (float posicao, float magnitude) {
        if (posicao <= largura) {
            forcas.push_back(forca(posicao, magnitude));
            return true;
        }

        return false;
    }
};

#endif