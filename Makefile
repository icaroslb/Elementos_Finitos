CXX = g++
LIBS = -lGL -lGLU -lglut

all: main
main: main.cpp
	$(CXX) -o $@ $^ $(LIBS)