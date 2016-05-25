normal:
	g++ --std=c++11 src/main.cpp src/SegmentSet.cpp src/StringMerge.cpp src/StringPair.cpp src/anyoption.cpp -o sequencer -O3

tests:
	g++ --std=c++11 src/SegmentSetTests.cpp src/SegmentSet.cpp src/StringMerge.cpp src/StringPair.cpp src/anyoption.cpp -o testSegmentSet -O3