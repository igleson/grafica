all:
	g++ ex1.cpp -lX11 -lGL -lGLU -lglut -g -Wall -O2 -o ex1
	./ex1
