clear
clear

rm tests

g++ -g -Wall testsJuego.cpp Juego.cpp Coordenada.cpp Mapa.cpp MultiC.cpp -o tests

./tests
#valgrind --leak-check=full ./tests
