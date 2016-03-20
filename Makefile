normal:
	g++ main.cpp -o main-normal -O3

parallel:
	g++ main.cpp -o main-parallel -fopenmp -O3