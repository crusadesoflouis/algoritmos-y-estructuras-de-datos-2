clear
clear

rm tests
rm Mapa.o

#g++ -c -g -Wall Mapa.cpp cord.o -o Mapa.o
g++ -g -Wall testTemplate.cpp cord.o  -o tests

#valgrind --leak-check=full ./tests
./tests


