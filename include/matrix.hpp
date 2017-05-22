#ifndef __ALAB_MATRIX
#define __ALAB_MATRIX
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
        delete [] indptr;
        delete [] indices;
        delete [] data;
        delete [] diagonal;
    }
};
}; // namespace alab



#endif
