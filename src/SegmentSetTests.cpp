#include <iostream>
#include <vector>
#include <string>

#include "SegmentSet.h"

using namespace std;

struct ProcessTest{
    vector<string> testSegments;
    string expectedResult;
    string name;
};

vector<ProcessTest> getTests();
void doTests();

int main(){
    doTests();
    return 0;
}

void doTests(){
    vector<ProcessTest> tests;
    tests = getTests();
    
    for(auto test : tests){
        SegmentSet testSet(test.testSegments);
        testSet.process();
        bool success = (testSet.getResults().compare(test.expectedResult) == 0);
        if(!success){
            cout << "SegmentSet não passou no teste " + test.name;
        } else {
            cout << "SegmentSet passou no teste " + test.name;
        }
        cout << endl;
    }
}

vector<ProcessTest> getTests(){
    vector<ProcessTest> tests;
    
    ProcessTest test1;
    test1.name = "Simple test";
    test1.testSegments.push_back("asdf");
    test1.testSegments.push_back("dfghjk");
    test1.testSegments.push_back("jklzxc");
    test1.testSegments.push_back("qweas");
    
    test1.expectedResult = "qweasdfghjklzxc";
    
    ProcessTest test2;
    test2.name = "Case A";
    test2.testSegments.push_back("fragmentation and sequencing. Computer programs then use the overlapping ends of different reads to assemble them into a continuous sequence. Shotgun sequencing was one of the precursor technologies that was responsible for enabling full genome sequencing.");
    test2.testSegments.push_back("sequenced using the chain termination method to obtain reads. Multiple overlapping reads for the target DNA are obtained by performing several rounds of this fragmentation and sequencing. Computer programs then use the overlapping ends of different reads to assemble");
    test2.testSegments.push_back("methods are used for this: primer walking (or \"chromosome walking\") which progresses through the entire strand piece by piece, and shotgun sequencing which is a faster but more complex process that uses random fragments. In shotgun sequencing, DNA is broken up randomly into numerous small segments, which are sequenced using the chain termination method to obtain reads. Multiple");
    test2.testSegments.push_back("quasi-random firing pattern of a shotgun. The chain termination method of DNA sequencing (or \"Sanger sequencing\" for its developer Frederick Sanger) can only be used for fairly short strands of 100 to 1000 base pairs. Longer sequences are subdivided into smaller fragments that can be sequenced separately, and subsequently they are re-assembled to give the overall sequence. Two principal methods are used for this: primer");
    test2.testSegments.push_back("In genetics, shotgun sequencing, also known as shotgun cloning, is a method used for sequencing long DNA strands. It is named by analogy with the rapidly expanding, quasi-random firing pattern of a shotgun. The chain termination method of DNA sequencing (or \"Sanger sequencing\" for its developer");
    
    test2.expectedResult = "In genetics, shotgun sequencing, also known as shotgun cloning, is a method used for sequencing long DNA strands. It is named by analogy with the rapidly expanding, quasi-random firing pattern of a shotgun. The chain termination method of DNA sequencing (or \"Sanger sequencing\" for its developer Frederick Sanger) can only be used for fairly short strands of 100 to 1000 base pairs. Longer sequences are subdivided into smaller fragments that can be sequenced separately, and subsequently they are re-assembled to give the overall sequence. Two principal methods are used for this: primer walking (or \"chromosome walking\") which progresses through the entire strand piece by piece, and shotgun sequencing which is a faster but more complex process that uses random fragments. In shotgun sequencing, DNA is broken up randomly into numerous small segments, which are sequenced using the chain termination method to obtain reads. Multiple overlapping reads for the target DNA are obtained by performing several rounds of this fragmentation and sequencing. Computer programs then use the overlapping ends of different reads to assemble them into a continuous sequence. Shotgun sequencing was one of the precursor technologies that was responsible for enabling full genome sequencing.";
    
    tests.push_back(test1);
    tests.push_back(test2);
    
    return tests;
}