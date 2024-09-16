compiler= gcc
gameName= jogo


all: main
	./$(gameName)

main: main.c
	$(compiler) main.c -lGL -lglut -lGLU -lm -o $(gameName)

clear:
	rm $(gameName)