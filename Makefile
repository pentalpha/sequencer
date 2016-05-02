normal:
	g++ src/main.cpp src/Bucket.cpp src/CompareResult.cpp src/StringPair.cpp -o bin/main-normal -O3

parallel:
	g++ src/main.cpp src/Bucket.cpp src/CompareResult.cpp src/StringPair.cpp -o bin/main-parallel -fopenmp -O3