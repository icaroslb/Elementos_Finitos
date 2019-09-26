#include <iostream>
#include <GL/freeglut.h>
#include "Eigen/Geometry"
#include "funcoes_momento.h"

#include "imgui-master/imgui.h"
#include "imgui-master/imgui_impl_glut.h"
#include "imgui-master/imgui_impl_opengl2.h"

#define FPS 60.0f

float posicaoForca = 0.0,
      magnitudeForca = 0.0,
	  estresseMax = 0.0;

Barra barraInsercao(0, 0, 0, -1, -1),
      barraResposta(0, 0, 0, -1, -1);

Eigen::Vector3d frente(0.0f, 0.0f, -1.0f),
                posi(0.0f, 0.0f, 0.0f),
				cima(0.0f, 1.0f, 0.0f),
				direita = cima.cross(frente),
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
void menu ();

int main (int argc, char *argv[]) {
    glutInit(&argc, argv);

	glutInitContextProfile(GLUT_COMPATIBILITY_PROFILE);

	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	
	glutInitWindowSize(600, 600);
	glutInitWindowPosition(100, 100);

	glutTimerFunc(1000.0/60.0, redesenharCena, 0);
	
	glutCreateWindow("modelagem");

	iniciar();

	glutMainLoop();

	// Cleanup
    ImGui_ImplOpenGL2_Shutdown();
    ImGui_ImplGLUT_Shutdown();
    ImGui::DestroyContext();

    return 0;
}

void iniciar () {
	glPolygonMode (GL_FRONT_AND_BACK, GL_LINE);

	// Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();
    //ImGui::StyleColorsClassic();

    // Setup Platform/Renderer bindings
    ImGui_ImplGLUT_Init();
    ImGui_ImplOpenGL2_Init();


	glutDisplayFunc(desenharCena);
	glutReshapeFunc(resize);
	glutKeyboardFunc(teclado);
	glutTimerFunc(1000/FPS, redesenharCena, 0);

    glutMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutPassiveMotionFunc(ImGui_ImplGLUT_MotionFunc);
    glutMouseFunc(ImGui_ImplGLUT_MouseFunc);
#ifdef __FREEGLUT_EXT_H__
    glutMouseWheelFunc(ImGui_ImplGLUT_MouseWheelFunc);
#endif
    glutKeyboardUpFunc(ImGui_ImplGLUT_KeyboardUpFunc);
    glutSpecialFunc(ImGui_ImplGLUT_SpecialFunc);
    glutSpecialUpFunc(ImGui_ImplGLUT_SpecialUpFunc);
}

void desenharCena () {
	// Start the Dear ImGui frame
    ImGui_ImplOpenGL2_NewFrame();
	ImGui_ImplGLUT_NewFrame();

	menu();

    // Rendering
    ImGui::Render();
    ImGuiIO& io = ImGui::GetIO();

	glClearColor(0.17, 0.17, 0.17, 1.00);

	glClear(GL_COLOR_BUFFER_BIT);
	glLoadIdentity();

	gluLookAt(posi.x(), posi.y(), posi.z(),
  		      lookAt.x(), lookAt.y(), lookAt.z(),
  		      cima.x(), cima.y(), cima.z());
	
	glColor3f(0.0, 0.80, 0.0);

	glBegin(GL_QUADS);
        glVertex3f(0.0, barraInsercao.altura/2, 0);
        glVertex3f(0.0, -barraInsercao.altura/2, 0);
        glVertex3f(barraInsercao.largura, -barraInsercao.altura/2, 0);
        glVertex3f(barraInsercao.largura, barraInsercao.altura/2, 0);
    glEnd();

	for (forca f : barraInsercao.forcas) {
		f.desenhar(barraInsercao.altura/2);
	}

	ImGui_ImplOpenGL2_RenderDrawData(ImGui::GetDrawData());
	glFlush();
	glutSwapBuffers();
	glutPostRedisplay();
}

void resize (int w, int h) {
	ImGui_ImplGLUT_ReshapeFunc(w, h);
	glViewport(0, 0, w, h);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(-10.0, 190.0, -100.0, 100.0, -1.0, 1.0);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}

void redesenharCena (int value) {
	glutTimerFunc(1000.0/FPS, redesenharCena, 0);
}

void teclado (unsigned char key, int x, int y) {
	ImGui_ImplGLUT_KeyboardFunc(key, x, y);
	switch (key) {
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

void menu () {
	ImGuiIO& io = ImGui::GetIO();

	ImGui::SetNextWindowPos(ImVec2(0.0f, io.DisplaySize.y), 0, ImVec2(0.0f, 1.0f));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x/2, 100));

	ImGui::Begin("entradasBarra", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::InputFloat("Largura", &barraInsercao.largura, 0.f, 1.0f, "%.3f");
		ImGui::InputFloat("Altura", &barraInsercao.altura, 0.f, 1.0f, "%.3f");
		ImGui::InputFloat("Profundidade", &barraInsercao.profundidade, 0.f, 1.0f, "%.3f");

		if(ImGui::Button("Calcular", ImVec2(65, 20))) {
			estresseMaximo(barraInsercao);
		}

		ImGui::Text("Estresse máximo: %0.3f", estresseMax);
	ImGui::End();

	ImGui::SetNextWindowPos(ImVec2(io.DisplaySize.x/2, io.DisplaySize.y), 0, ImVec2(0.0f, 1.0f));
	ImGui::SetNextWindowSize(ImVec2(io.DisplaySize.x/2, 100));

	ImGui::Begin("entradasForca", NULL, ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoBringToFrontOnFocus);
		ImGui::InputFloat("Posição", &posicaoForca, 0.f, 1.0f, "%.3f");
		ImGui::InputFloat("Magnitude", &magnitudeForca, 0.f, 1.0f, "%.3f");
		
		if(ImGui::Button("Criar", ImVec2(50, 20))) {
			barraInsercao.inserirForca(posicaoForca, magnitudeForca);
		}
	ImGui::End();
}