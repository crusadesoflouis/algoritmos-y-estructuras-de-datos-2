clear
clear


g++ -c -g -Wall Mapa.cpp cord.o -o Mapa.o
g++ -g -Wall testMapa.cpp cord.o Mapa.o  -o tests

#valgrind --leak-check=full ./tests
./tests

rm tests
rm Mapa.o
