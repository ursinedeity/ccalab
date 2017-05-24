/**
 * Copyright 2017 University of Southern California
 * Licensed under GPLv2 or any later version
 * Refer to the LICENSE file included.
 */

#ifndef _BUILDER
#define _BUILDER
#include <string>
#include "alab.hpp"
class CooBuilder{
public:
    CooBuilder(alab::Genome &genome, alab::Index &index, int resolution){
        this->genome = genome;
        this->index = index;
        this->resolution = resolution;
        ci = 0; cj = 0; cv = 0;
    }
    
    std::vector<int> Ai,Aj;
    std::vector<float> Ax;
    alab::Genome genome;
    alab::Index index;
    int resolution, ci, cj;
    float cv;
    bool AddPairsLine(const std::string &line);
    void PrintCoo();
};

#endif
