/**
 * Copyright 2017 University of Southern California
 * Licensed under GPLv2 or any later version
 * Refer to the LICENSE file included.
 */
#include "io.h"
#include <string>
#include <vector>
#include "Sort.h"

int main(int argc, char * argv[]){
    int optc;
    unsigned int threads=1;
    std::string outfile("-");
    std::string corder,genome_assembly;
    std::string forder("chr1-chr2-pos1-pos2");
    std::string shape("upper triangle");
    std::vector<std::string> chromOrder,fieldOrder;
    
    while((optc = getopt(argc,argv,"o:c:f:g:s:t:")) != -1){
        switch (optc) {
            case 'o':
                outfile = optarg;
                break;
            case 'c':
                corder = optarg;
                chromOrder = split(corder,'-');
                break;
            case 'f':
                forder = optarg;
                break;
            case 'g':
                genome_assembly = optarg;
                break;
            case 's':
                if (optarg[0] == 'l') shape = "lower triangle";
                break;
            case 't':
                threads = std::stoi(optarg);
                break;
            case '?':
                exit(1);
            default:
            break;
        }
    }
    fieldOrder = split(forder,'-');
    
    // set default input from STDIN
    char* inputFile = (char*)"-";
    
    // if there is an operand other than sort
    if (optind < argc){
        inputFile = argv[optind++];
    }
    
    std::shared_ptr<std::istream> input = GetInput(inputFile);
    
    PairsFileHeader header;
    
    
    //using arguments to get chromosome order e.g. -c chr1-chr2-chr3-chr4-...
    //unspecified chromosome in order will be discared.
    header.set_chrom_order(chromOrder.data(),chromOrder.size());
    header.set_shape(shape);
    
    //process pairs file
    std::string line;
    for (;std::getline(*input,line) && line[0] == '#';){
        header.ParseHeader(line);
    }
    header.set_sorted(forder);
    if (!genome_assembly.empty()) header.set_genome_assembly(genome_assembly);
    
    //sorter must have a header to initialize.
    PairsFileSorter sorter(header);
    sorter.AddRecord(line);
    for (;std::getline(*input,line);){
        sorter.AddRecord(line);
    }
    
    std::vector<int>  order = header.get_field_order(fieldOrder.data(),fieldOrder.size());
//     for (auto it = order.begin(); it != order.end(); ++it) std::cerr << *it << ' ';
//     std::cerr << std::endl;
    
    sorter.Sort(order.data(),order.size(),threads);

    std::shared_ptr<std::ostream> output = GetOutput(outfile.c_str());
    sorter.PrintRecords(output);
    
}


