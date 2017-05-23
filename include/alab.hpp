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
