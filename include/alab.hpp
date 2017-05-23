 
#ifndef __ALAB
#define __ALAB

#include "utils.hpp"
#include "matrix.hpp"

namespace alab{

const std::string VERSION("0.0.4");

class ContactMatrix{
public:
    Genome genome;
    Index index;
    Matrix matrix;
    int resolution;
    
    unsigned int rowsum();
    
    
    void save(const std::string &filename, unsigned int compression = 6, unsigned int chunksize = 100000);
};

};
#endif
