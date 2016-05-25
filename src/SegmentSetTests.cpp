#include <iostream>
#include <vector>
#include <string>

#include "ProcessTest.h"
#include "SegmentSet.h"

using namespace std;

int main(){
    vector<ProcessTest> tests;
    
    for(auto test : tests){
        SegmentSet testSet(test.testSegments);
        testSet.process();
        bool success = (testSet.getResults().compare(test.expectedResult) == 0);
        cout << "Sequencer não passou no teste " + test.name;
    }
    
    return 0;
}