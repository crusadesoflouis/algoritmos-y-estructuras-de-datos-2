clear
clear
g++ -c  -g -Wall Mapa.cpp -o mapapa
g++ -g -Wall testMapa.cpp mapapa -o tests

valgrind --leak-check=full ./tests

rm -rf *o tests
