#include <iostream>
#include <GL/freeglut.h>
#include "Eigen/Geometry"

bool aramado = true;
int largura = 300, altura = 300;
double volume = 0;

Eigen::Vector3d frente(0.0f, 0.0f, 1.0f),
                posi(0.0f, 0.0f, 0.0f),
				cima(0.0f, 1.0f, 0.0f),
				direita = frente.cross(cima),
				lookAt = frente;
Eigen::Vector3f ambiente(0.25, 0.25, 0.25),
                difusa(1, 1, 1),
				especular(1, 1, 1),
				luzPosicao(100, 100, 0);

void iniciar ();
void desenharCena ();
void resize (int w, int h);
void redesenharCena (int value);
void teclado (unsigned char key, int x, int y);

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);

	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowSize(2*largura, 2*altura);
	glutInitWindowPosition(100, 100);

	glutTimerFunc(1000.0/60.0, redesenharCena, 0);
	
	glutCreateWindow("modelagem");
	
	glutDisplayFunc(desenharCena);
	glutReshapeFunc(resize);
	glutKeyboardFunc(teclado);

	iniciar();

	glutMainLoop();

    return 0;
}

void iniciar () {
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
}

void desenharCena () {
	glClearColor(0.17, 0.17, 0.17, 1.00);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(posi.x(), posi.y(), posi.z(),
  		      lookAt.x(), lookAt.y(), lookAt.z(),
  		      cima.x(), cima.y(), cima.z());
	
	glColor3f(0.0, 0.80, 0.0);

	glBegin(GL_QUADS);
        glVertex3f(-50, 50, 0);
        glVertex3f(-50, -50, 0);
        glVertex3f(50, -50, 0);
        glVertex3f(50, 50, 0);
    glEnd();

	glFlush();
}

void resize (int w, int h) {
	glViewport(0, 0, w, h);

	largura = w/2;
	altura = h/2;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-100.0, 100.0, -100.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void redesenharCena (int value) {
	glutSwapBuffers();
	glutPostRedisplay();
	glutTimerFunc(1000.0/60.0, redesenharCena, 0);
}

void teclado (unsigned char key, int x, int y) {
	switch (key) {
	case 32:
		if (aramado) {
			glPolygonMode (GL_FRONT_AND_BACK, GL_FILL);
			aramado = false;
		} else {
			glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);
			aramado = true;
		}
	break;

	case 'w':
		posi += frente;
		lookAt += frente;
	break;

	case 'a':
		posi -= direita;
		lookAt -= direita;
	break;

	case 's':
		posi -= frente;
		lookAt -= frente;
	break;

	case 'd':
		posi += direita;
		lookAt += direita;
	break;

	default:
	break;
	}
}
