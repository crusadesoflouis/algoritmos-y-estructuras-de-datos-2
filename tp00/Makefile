all:
	g++ -g tests.cpp -o tests
	./tests
	rm -rf *o tests
valgrind:
	g++ -g tests.cpp -o tests
	valgrind --leak-check=full -v ./tests
	rm -rf *o tests
clear:
	clear
