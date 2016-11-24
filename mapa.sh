clear
clear
g++ -c  -g -Wall Mapa.cpp -o mapa
g++ -g -Wall testMapa.cpp mapa -o tests

valgrind --leak-check=full ./tests

rm -rf *o tests
