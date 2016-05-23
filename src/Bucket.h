#ifndef _BUCKET_
#define _BUCKET_

#include <vector>
#include <string>
#include "StringPair.h"

using namespace std;

class Bucket{
public:
    vector<string> segments;

    Bucket(vector<string> newSegments){
    	segments = newSegments;
    }

    Bucket(){

    }

    inline int nSegments(){
    	return segments.size();
    }
    
    void process(bool forceMerge);
    
    
};



#endif