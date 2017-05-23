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

    alab::ContactMatrix cm;
    
    cm.matrix.LoadCoo(Ai,Aj,Ax,4,8);
    cm.matrix.PopDiagonal();
    cm.matrix.EliminateZeros();
    
    alab::Genome g(assembly,chroms,origins,lengths);
    alab::Index ind = g.BinInfo(10000);
    
    cm.genome = g;
    cm.index = ind;
    cm.resolution = 10000;
    for (int i = 0; i<cm.matrix.size+1; i++){
        std::cout << cm.matrix.indptr[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<cm.matrix.nnz; i++){
        std::cout << cm.matrix.indices[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<cm.matrix.nnz; i++){
        std::cout << cm.matrix.data[i] << ' ';
    }
    std::cout << std::endl;
    
    for (int i = 0; i<cm.matrix.size; i++){
        std::cout << cm.matrix.diagonal[i] << ' ';
    }
    std::cout << std::endl;
    cm.save("t");

}
