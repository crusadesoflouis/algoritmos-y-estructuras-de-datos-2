clear
clear



rm juego.o
rm tests

g++ -c -g -Wall Juego.cpp cord.o mapa.o multi.o -o juego.o
g++ -g -Wall testsJuego.cpp cord.o mapa.o multi.o juego.o -o tests

./tests
