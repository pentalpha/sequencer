normal:
	g++ main.cpp ProcessBucket.cpp StringPair.cpp -o main-normal -O3

parallel:
	g++ main.cpp ProcessBucket.cpp StringPair.cpp -o main-parallel -fopenmp -O3