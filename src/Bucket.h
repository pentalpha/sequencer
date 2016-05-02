#ifndef _BUCKET_
#define _BUCKET_

#include "StringPair.h"

using namespace std;

class Bucket{
public:
    string* segments;
    int nSegments;
    
    void process(bool forceMerge);
};

#endif