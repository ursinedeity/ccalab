
#include "alab.hpp"
#include "h5file.hpp"
#include <iostream>
namespace alab{


/**
 * Save contact matrix into hdf5 file hcs
 * 
 * 
 * Input Arguments:
 *   const std::string & filename              - output filename extension = ".hcs"
 *   unsigned int compression                  - compression level, default 6
 *   unsigned int chunksize                    - compression chunk size default 100000
 * 
 */
void ContactMatrix::save(const std::string &filename, unsigned int compression, unsigned int chunksize){
    
    std::string name(filename);
    if ((name.length() < 4) || (name.substr(name.length() - 5, 4) != ".hcs"))
        name += ".hcs";
    
    H5::H5File h5f(name, H5F_ACC_TRUNC);
    
    int nbin = index.size;
    
    add_attribute(h5f,"version", VERSION);
    add_attribute(h5f,"resolution", resolution);
    add_attribute(h5f,"nbin", nbin);
    //std::cout << 'a' << std::endl;
    genome.save(h5f, compression, chunksize);
    //std::cout << 'g'<< std::endl;
    index. save(h5f, compression, chunksize);
    //std::cout << 'i'<< std::endl;
    matrix.save(h5f, compression, chunksize);
    //std::cout << 'm'<< std::endl;
}

};
