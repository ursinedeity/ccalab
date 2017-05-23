#include "matrix.hpp"
#include <algorithm>

namespace alab{
    
/**
 * Build Matrix by talking an i,j,v list
 * 
 * Input Arguments:
 *   const unsigned int *Ai           - i
 *   const unsigned int *Aj           - j
 *   const float *Ax                  - value
 *   unsigned int size                - matrix size
 *   unsigned int nnz                 - number of non zeros nnz(A)
 * 
 * Note:
 *   This function is adpoted from scipy sparsetools
 *
 * Note: 
 *   Input:  row and column indices *are not* assumed to be ordered
 *           
 *   Note: duplicate entries are carried over to the CSR represention
 *
 *   Complexity: Linear.  Specifically O(nnz(A) + size)
 */
void Matrix::LoadCoo(const unsigned int *Ai, const unsigned int *Aj, const float *Ax, unsigned int size, unsigned int nnz){
    indptr = new unsigned int [size+1];
    indices = new unsigned int [nnz];
    data = new float [nnz];
    
    this->size = size;
    this->nnz = nnz;
    
    std::fill(indptr, indptr + size, 0);
    
    for (unsigned int i = 0; i < nnz; ++i)
        indptr[Ai[i]]++;
    
    for (unsigned int i = 0, cumsum = 0; i < size; ++i){
        unsigned int tmp = indptr[i];
        indptr[i] = cumsum;
        cumsum += tmp;
    }
    indptr[size] = nnz;
    
    for (unsigned int i = 0; i < nnz; ++i){
        unsigned int row = Ai[i];
        unsigned int dest = indptr[row];
        
        indices[dest] = Aj[i];
        data[dest] = Ax[i];
        
        indptr[row]++;
    }
    
    for (unsigned int i = 0, last = 0; i <= size; ++i){
        unsigned int tmp = indptr[i];
        indptr[i] = last;
        last = tmp;
    }
    
}




/*
 * Pop main diagonal of CSR matrix 
 *
 * Note:
 *   This function is adpoted from scipy sparsetools
 * 
 * Note:
 *   Diagonal entries will be cleared as zero.
 *    
 *   Duplicate entries will be summed, output will be stored in diagonal
 *
 *   Complexity: Linear.  Specifically O(nnz(A) + size)
 * 
 */
void Matrix::PopDiagonal(){
    diagonal = new float [size];
    
    for(unsigned int i = 0; i < size; i++){
        const unsigned int row_start = indptr[i];
        const unsigned int row_end   = indptr[i+1];

        float diag = 0;
        for(unsigned int jj = row_start; jj < row_end; jj++){
            if (indices[jj] == i){
                diag += data[jj];
                data[jj] = 0;
            }
        }

        diagonal[i] = diag;
    }
}




/**
 * Eliminate zero entries from csr matrix 
 *
 * Note:
 *   This function is adpoted from scipy sparsetools
 *   
 * Note:
 *   indptr, indices, and data will be modified *inplace*
 *
 */
void Matrix::EliminateZeros(){
    unsigned int new_nnz = 0;
    unsigned int row_end = 0;
    for(unsigned int i = 0; i < size; i++){
        unsigned int jj = row_end;
        row_end = indptr[i+1];
        while( jj < row_end ){
            unsigned int j = indices[jj];
            float x = data[jj];
            if(x != 0){
                indices[new_nnz] = j;
                data[new_nnz] = x;
                new_nnz++;
            }
            jj++;
        }
        indptr[i+1] = new_nnz;
    }
    
    this->nnz = new_nnz;

}




/**
 * Determine whether the CSR column indices are in sorted order.
 *
 * Returns:
 *   bool               - indicates has sorted indices or not
 */
bool Matrix::HasSortedIndices(){
  for(unsigned int i = 0; i < size; i++){
      for(unsigned int jj = indptr[i]; jj < indptr[i+1] - 1; jj++){
          if(indices[jj] > indices[jj+1]){
              return false;
          }
      }
  }
  return true;
}





template< class T1, class T2 >
bool kv_pair_less(const std::pair<T1,T2>& x, const std::pair<T1,T2>& y){
    return x.first < y.first;
}


/*
 * Sort CSR column indices inplace
 *
 * Note:
 *   This function is adpoted from scipy sparsetools
 *
 */
void Matrix::SortIndices(){
    std::vector< std::pair<unsigned int, float> > temp;

    for(unsigned int i = 0; i < size; i++){
        unsigned int row_start = indptr[i];
        unsigned int row_end   = indptr[i+1];

        temp.resize(row_end - row_start);
        for (unsigned int jj = row_start, n = 0; jj < row_end; jj++, n++){
            temp[n].first  = indices[jj];
            temp[n].second = data[jj];
        }

        std::sort(temp.begin(),temp.end(),kv_pair_less<unsigned int, float>);

        for(unsigned int jj = row_start, n = 0; jj < row_end; jj++, n++){
            indices[jj] = temp[n].first;
            data[jj] = temp[n].second;
        }
    }    
}




/**
 * Save matrix information into h5 file
 * 
 * Input Arguments:
 *   H5::H5File                                - output h5 group
 *   unsigned int compression                  - compression level, default 6
 *   unsigned int chunksize                    - compression chunk size default 100000
 * 
 * Note:
 *   This function will generate a group "matrix" and save 
 *      chrom_sizes: int32 []
 *      chrom: int32 []
 *      start: int32 []
 *      end: int32 []
 *      label: string []
 *      copy: int32 []
 * 
 */
void Matrix::save(H5::H5File &loc, unsigned int compression, unsigned int chunksize){
    H5::Group matrix(loc.createGroup("matrix"));
    
    add_dataset1D(matrix, "data", data, nnz, compression, chunksize);
    add_dataset1D(matrix, "indices", indices, nnz, compression, chunksize);
    add_dataset1D(matrix, "indptr", indptr, size+1, compression, chunksize);
    add_dataset1D(matrix, "diagonal", diagonal, size, compression, chunksize);
    
}

};
