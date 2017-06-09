// Copyright (C) 2017 University of Southern California and
//                          Nan Hua
// 
// Authors: Nan Hua
// 
// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//  
// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
// 
// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <http://www.gnu.org/licenses/>.

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
    if ((name.substr(name.length() - 4, 4) != ".hcs") || (name.length() <= 4))
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
