all: compile link

compile:
	g++ -Isrc/include -c *.cpp

link:
	g++ main.o -o main window.o tile.o snake.o -Lsrc/lib -lsfml-graphics -lsfml-window -lsfml-system