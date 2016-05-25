#ifndef _BUCKET_
#define _BUCKET_

#include <vector>
#include <string>
#include <assert.h>
#include "StringPair.h"

using namespace std;

/**
    @brief  Conjunto de seguimentos de texto
    
    @author Pitágoras Alves
    @date   May 2016
*/
class SegmentSet{
public:
    vector<string> segments;
    
    /**
        Builds the class based in sequence of segments
        
        @param  newSegments segments of text to be copied
    */
    SegmentSet(vector<string> newSegments){
        assert(!newSegments.empty());
        
    	segments = newSegments;
    }
    
    /**
        Builds the class using a stream to request textual input.
        
        @param  inputStream A valid istream pointer.
    */
    SegmentSet(istream* inputStream);

    SegmentSet(){

    }

    inline int nSegments(){
    	return segments.size();
    }
    
    /**
       Trys to merge all the segments of text into only one.
       
       @return  If the algorithm resulted in only one final text
    */
    bool process();
    
    string getResults();
};



#endif