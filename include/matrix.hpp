#ifndef __ALAB_MATRIX
#define __ALAB_MATRIX
#include "h5file.hpp"
#include <iostream>
namespace alab{

class Matrix{
public:
    unsigned int *indptr;
    unsigned int *indices;
    float *data;
    float *diagonal;
    unsigned int size, nnz;
    
    void LoadCoo(const unsigned int *Ai, const unsigned int *Aj, const float *Ax, unsigned int size, unsigned int nnz);
    void PopDiagonal();
    void EliminateZeros();
    bool HasSortedIndices();
    void SortIndices();
    Matrix(){
        indptr = nullptr; indices = nullptr; data = nullptr; diagonal = nullptr;
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
