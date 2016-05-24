#ifndef _BUCKET_
#define _BUCKET_

#include <vector>
#include <string>
#include "StringPair.h"

using namespace std;

class SegmentSet{
public:
    vector<string> segments;

    SegmentSet(vector<string> newSegments){
    	segments = newSegments;
    }
    
    SegmentSet(istream* inputStream);

    SegmentSet(){

    }

    inline int nSegments(){
    	return segments.size();
    }
    
    bool process();
    
    string getResults();
};



#endif