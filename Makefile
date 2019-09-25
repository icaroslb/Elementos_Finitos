CXX = g++
LIBS = -lGL -lGLU -lglut

all: main
main: main.cpp
	$(CXX) -o $@ $^ $(LIBS)

teste: funcoes_momento.o teste
funcoes_momento.o: funcoes_momento.cpp funcoes_momento.h
	g++ -g -c $< -o $@
teste: teste.cpp funcoes_momento.o
	g++ -o $@ $^ -lm

clean:
	rm -f *.o