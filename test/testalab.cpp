#include "alab.hpp"
#include <iostream>
#include <vector>
int main(){
    unsigned int Ai [] = {0,0,0,0,1,1,2,3};
    unsigned int Aj [] = {0,1,2,3,2,3,3,3};
    float Ax []={1,3,4,5,3,3,3,1};
    
    std::string assembly("mm10");
    std::vector<std::string> chroms= {"chr1","chr2","chr3"};
    std::vector<unsigned int> origins = {0,0,0};
    std::vector<unsigned int> lengths = {10000,20000,30000};
    alab::Matrix m;
    
    m.LoadCoo(Ai,Aj,Ax,4,8);
    m.PopDiagonal();
    m.EliminateZeros();
    
    alab::Genome g(assembly,chroms,origins,lengths);
    alab::Index ind = g.BinInfo(10000);
    
    alab::ContactMatrix cm;
    
    cm.matrix = m;
    cm.genome = g;
    cm.index = ind;
    cm.resolution = 10000;
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
    cm.save("t");

}
