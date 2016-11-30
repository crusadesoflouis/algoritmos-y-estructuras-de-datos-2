clear
clear



rm juego.o
rm tests

g++ -c -g -Wall Juego.cpp cord.o Mapa.o multi.o -o Juego.o
g++ -g -Wall testsJuego.cpp cord.o Mapa.o multi.o Juego.o -o tests

./tests
