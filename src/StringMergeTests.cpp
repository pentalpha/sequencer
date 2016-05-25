#include <iostream>
#include <vector>
#include <string>

#include "StringMerge.h"

using namespace std;

struct MergeTest{
  string name;
  string a, b;
  bool forcemerge;
  string expectedResult;
};

vector<MergeTest> getTests();
void doTests();

int main(){
    doTests();
    return 0;
}

void doTests(){
    vector<MergeTest> tests;
    tests = getTests();
    
    for(auto test : tests){
        StringMerge merge(test.a, test.b, test.forcemerge);
        bool success = (merge.result.compare(test.expectedResult) == 0);
        if(!success){
            cout << "StringMerge não passou no teste " + test.name;
        } else {
            cout << "StringMerge passou no teste " + test.name;
        }
        cout << endl;
    }
}

vector<MergeTest> getTests(){
    vector<MergeTest> tests;
    
    MergeTest test1;
    test1.name = "Alfabeto";
    test1.a = "abcdfegh";
    test1.b = "feghjipr";
    test1.forcemerge = false;
    test1.expectedResult = "abcdfeghjipr";
    tests.push_back(test1);
    
    MergeTest test2;
    test2.name = "Nome";
    test2.a = "as Alves";
    test2.b = "Pitagoras";
    test2.forcemerge = false;
    test2.expectedResult = "Pitagoras Alves";
    tests.push_back(test2);
    
    return tests;
}