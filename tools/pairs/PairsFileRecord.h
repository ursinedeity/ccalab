/**
 * Copyright 2017 University of Southern California
 * Licensed under GPLv2 or any later version
 * Refer to the LICENSE file included.
 */

#ifndef _PAIRSFILERECORD
#define _PAIRSFILERECORD
#include <string>
#include <map>

struct PairsRecord{
    unsigned int pos[4];//chrom1 pos1 chrom2 pos2
    std::string readID;
    std::string *extrafields;
    PairsRecord(const std::string &readID, const unsigned int pos [], std::string *extrafields, const int shape);
    ~PairsRecord(){
        delete [] extrafields;
    }
    
    void SwapPos();
};

#endif
