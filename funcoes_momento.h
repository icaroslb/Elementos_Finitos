#ifndef FUNCOES_MOMENTO_H
#define FUNCOES_MOMENTO_H

#define PI 3.14159;

#include "Barra.h"
#include <cmath>

float momentoMaximo (Barra &modelo);
float MomentoInercia (Barra &modelo);
float estresseMaximo (Barra &modelo);

#endif