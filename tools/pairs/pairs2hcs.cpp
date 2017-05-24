/**
 * Copyright 2017 University of Southern California
 * Licensed under GPLv2 or any later version
 * Refer to the LICENSE file included.
 */
#include "io.h"
#include "PairsFileHeader.h"
#include "Builder.h"
#include "alab.hpp"

int main(int argc, char * argv[]){
    int optc;
    int resolution = 100000;
    std::string outfile("output.hcs");
    std::string corder,genome_assembly;
    std::vector<std::string> chromOrder;
    
    while((optc = getopt(argc,argv,"o:c:g:r:")) != -1){
        switch (optc) {
            case 'o':
                outfile = optarg;
                break;
            case 'c':
                corder = optarg;
                chromOrder = split(corder,'-');
                break;
            case 'g':
                genome_assembly = optarg;
                break;
            case 'r':
                resolution = std::stoi(optarg);
                break;
            case '?':
                exit(1);
            default:
            break;
        }
    }
    // set default input from STDIN
    char* inputFile = (char*)"-";
    
    // if there is an operand other than sort
    if (optind < argc){
        inputFile = argv[optind++];
    }
    
    std::shared_ptr<std::istream> input = GetInput(inputFile);
    std::cerr << resolution << std::endl;
    PairsFileHeader header;
    
    //using arguments to get chromosome order e.g. -c chr1-chr2-chr3-chr4-...
    //unspecified chromosome in order will be discared.
    header.set_chrom_order(chromOrder.data(),chromOrder.size());
    //process pairs file
    std::string line;
    for (;std::getline(*input,line) && line[0] == '#';){
        header.ParseHeader(line);
    }
    if (!genome_assembly.empty()) header.set_genome_assembly(genome_assembly);
    
    
    alab::ContactMatrix m;
    m.genome = header.MakeGenome();
    
//     for (auto &c : genome.chroms)
//         std::cout << c << ' ';
    m.resolution = resolution;
    m.index = m.genome.BinInfo(resolution);
    
//     for (auto &b : index.offset)
//         std::cout << b << ' ';
//     
//     std::cout << std::endl;
    
    CooBuilder builder(m.genome, m.index, resolution);
    
    builder.AddPairsLine(line);
    for (;std::getline(*input,line);){
        builder.AddPairsLine(line);
    }
    
    //builder.PrintCoo();
    m.matrix.LoadCoo(builder.Ai.data(), builder.Aj.data(), builder.Ax.data(), m.index.size, builder.Ax.size());
    m.matrix.PopDiagonal();
    m.matrix.EliminateZeros();
    m.save(outfile);
}
