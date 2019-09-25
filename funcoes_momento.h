#ifndef FUNCOES_MOMENTO_H
#define FUNCOES_MOMENTO_H

#include "Barra.h"
#include <cmath>

float momentoMaximo (Barra &modelo);
float MomentoInercia (Barra &modelo);
float estresseMaximo (Barra &modelo);

#endif