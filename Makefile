normal:
	g++ main.cpp -o main-normal

parallel:
	gcc -O3 -c main.cpp -fopenmp -o main.o
	gcc -O3 main.o -fopenmp -o main
