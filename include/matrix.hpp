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

#ifndef __ALAB_MATRIX
#define __ALAB_MATRIX
#include "h5file.hpp"
#include <vector>
#include <iostream>

#define DATATYPE float

namespace alab{

class Matrix{
public:
    std::vector<unsigned int> indptr;
    std::vector<unsigned int> indices;
    std::vector<DATATYPE> data;
    std::vector<DATATYPE> diagonal;
    unsigned int size, nnz;
    
    void LoadCoo(const unsigned int *Ai, const unsigned int *Aj, const DATATYPE *Ax, unsigned int size, unsigned int nnz);
    void PopDiagonal();
    void SumDuplicates();
    void EliminateZeros();
    bool HasSortedIndices();
    void SortIndices();
    
    void prune(unsigned int new_nnz);
    Matrix(){
        size = 0; nnz = 0;
    }
    ~Matrix(){
//         delete [] indptr;
//         std::cout << "di" << std::endl;
//         delete [] indices;
//         std::cout << "di" << std::endl;
//         delete [] data;
//         std::cout << "di" << std::endl;
//         delete [] diagonal;
//         std::cout << "di" << std::endl;
    }
    
    void save(H5::H5File &loc, unsigned int compression = 6, unsigned int chunksize = 100000);
};
}; // namespace alab



#endif
