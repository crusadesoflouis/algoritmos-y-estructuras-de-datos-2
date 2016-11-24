clear
clear
g++ -c -g -Wall MultiC.cpp -o multiC.o
g++ -g -Wall testTrie.cpp multiC.o -o tests

valgrind --leak-check=full ./tests

rm -rf *o tests
