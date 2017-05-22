#include "alab.hpp"
#include <iostream>
int main(){
    unsigned int Ai [] = {0,0,0,0,1,1,2,3};
    unsigned int Aj [] = {0,1,2,3,2,3,3,3};
    float Ax []={1,3,4,5,3,3,3,1};

    alab::Matrix m;
    
    m.LoadCoo(Ai,Aj,Ax,4,8);
    m.PopDiagonal();
    m.EliminateZeros();
    
    for (int i = 0; i<m.size+1; i++){
        std::cout << m.indptr[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<m.nnz; i++){
        std::cout << m.indices[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<m.nnz; i++){
        std::cout << m.data[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<m.size; i++){
        std::cout << m.diagonal[i] << ' ';
    }
    std::cout << std::endl;
}
