compile:
	g++ -Wall -g -o main main.cpp
run:
	./main
valgrind:
	valgrind --leak-check="full" ./main
