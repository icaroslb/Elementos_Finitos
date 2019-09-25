CXX = g++
EXE = main

SOURCES += $(wildcard imgui-master/*.cpp)
OBJ = objetos/
OBJS = $(addprefix $(OBJ), $(addsuffix .o, $(basename $(notdir $(SOURCES)))))
CXXFLAGS = -I im_gui_openGL/
CXXFLAGS += -g -Wall -Wformat
LIBS = -lGL -lGLU -lglut -lm

all: obj $(OBJS) funcoes_momento.o main
obj:
	if test ! -d objetos; then mkdir objetos; fi
$(OBJ)%.o: imgui-master/%.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<
funcoes_momento.o: funcoes_momento.cpp funcoes_momento.h
	g++ -g -c $< -o $@
$(EXE): $(OBJS) funcoes_momento.o main.cpp
	$(CXX) -o $@ $^ $(LIBS)

teste: obj teste.cpp funcoes_momento.o
	g++ -o $@ $^ -lm

clean:
	rm -f *.o