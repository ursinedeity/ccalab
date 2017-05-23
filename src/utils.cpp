#include "utils.hpp"

#include <cmath>
#include <iostream>
namespace alab{
    
/**
 * Constructor Genome
 * 
 * Initialize Genome object
 * 
 * Input Arguments:
 *   const std::string & assembly               - assembly name
 *   const std::vector<std::string> & chroms    - list of chroms in the genome
 *   const std::vector<unsigned int> & origins  - list of chromosome origin in the genome
 *   const std::vector<unsigned int> & lengths  - list of chromosome length
 * 
 */
Genome::Genome(const std::string &assembly, const std::vector<std::string> &chroms, const std::vector<unsigned int> &origins, const std::vector<unsigned int> &lengths){
    if (chroms.size() != lengths.size()){
        std::cerr << "Chroms and lengths sizes don't match!\n";
        exit(1);        
    }
    
    this->assembly = assembly;
    this->chroms = chroms;
    this->origins = origins;
    this->lengths = lengths;
    for (unsigned int i = 0; i < chroms.size(); ++i)
        chromMap[chroms[i]] = i;
}




/**
 * Constructor Genome
 * 
 * Initialize Genome object
 * 
 * Input Arguments:
 *   const std::string & assembly               - assembly name
 *   const std::vector<std::string> & chroms    - list of chroms in the genome
 *   const std::vector<unsigned int> & lengths  - list of chromosome length
 * 
 */
Genome::Genome(const std::string &assembly, const std::vector<std::string> &chroms, const std::vector<unsigned int> &lengths){
    this->assembly = assembly;
    this->chroms = chroms;
    this->lengths = lengths;
    
    for (unsigned int i = 0; i < chroms.size(); ++i){
        this->origins.push_back(0);
        chromMap[chroms[i]] = i;
    }
}


/**
 * Get a chromosome representation by index
 * 
 * Input Arguments:
 *   unsigned int c             - index in the range of chromosomes
 * 
 * Returns:
 *   std::string                - chromsome representation
 * 
 */
std::string Genome::get_chrom(unsigned int c){
    if (c < chroms.size())
        return chroms[c];
    else
        return "";
}



/**
 * Get a chromosome index by representation
 * 
 * Input Arguments:
 *   const std::string &chrom   - chromosome representation
 * 
 * Returns:
 *   int                        - chromosome index, -1 for undefined chromosome
 * 
 */
int Genome::get_chromnum(const std::string & chrom){
    auto it = chromMap.find(chrom);
    if (it != chromMap.end())
        return it->second;
    else
        return -1;
}




/**
 * Build Binned Index by Resolution
 * 
 * Input Arguments:
 *   unsigned int resolution    - matrix resolution
 * 
 * Returns:
 *   Index                      - matrix Index object
 * 
 */
Index Genome::BinInfo(unsigned int resolution){
    std::vector<unsigned int> binSize, chromList, binLabel, startList, endList;
    
    for (auto &l : lengths)
        binSize.push_back( l/resolution + ( l%resolution != 0) );
    
    for (unsigned int i = 0; i < chroms.size(); ++i){
        for (unsigned int j = 0; j < binSize[i]; ++j){
            chromList.push_back(i);
            binLabel.push_back(j + origins[i]/resolution);
        }
    }
    
    
    for (unsigned int &label : binLabel){
        startList.push_back (label*resolution );
        endList.push_back( (label+1)*resolution );
    }
    
    return Index(chromList, startList, endList, binSize);
}




/**
 * Save genome information into h5 file
 * 
 * Input Arguments:
 *   H5::File                                  - output h5 group
 *   unsigned int compression                  - compression level, default 6
 *   unsigned int chunksize                    - compression chunk size default 100000
 * 
 * Note:
 *   This function will generate a group "genome" and save 
 *      assembly: string
 *      chroms: string []
 *      origins: int32 []
 *      lengths: int32 []
 * 
 */
void Genome::save(H5::H5File &loc, unsigned int compression, unsigned int chunksize){
    H5::Group genome(loc.createGroup("genome"));
    
    add_scalar(genome, "assembly", assembly);
    add_dataset1D(genome, "chroms", chroms.data(), chroms.size(), compression, chunksize);
    add_dataset1D(genome, "origins", origins.data(), origins.size(), compression, chunksize);
    add_dataset1D(genome, "lengths", lengths.data(), lengths.size(), compression, chunksize);
    
}

//==========================================================



/**
 * Index instance constructor
 * 
 * Input Arguments:
 *   const std::vector<unsigned int> &chromList
 *   const std::vector<unsigned int> &startList
 *   const std::vector<unsigned int> &endList
 *   const std::vector<unsigned int> &chrom_sizes
 * 
 */
Index::Index(const std::vector<unsigned int> &chromList, 
             const std::vector<unsigned int> &startList, 
             const std::vector<unsigned int> &endList, 
             const std::vector<unsigned int> &chrom_sizes){
    this->chrom = chromList;
    this->start = startList;
    this->end = endList;
    num_chrom = chrom_sizes.size();
    
    for (unsigned int i = 0; i < chromList.size(); ++i){
        copy.push_back(0);
        label.push_back("");
    }
    
    this->chrom_sizes = chrom_sizes;
    offset.push_back(0);
    for (unsigned int i = 0, sum = 0; i < chrom_sizes.size(); ++i){
        sum += chrom_sizes[i];
        offset.push_back(sum);
        size = sum;
    }    
}

// IndexItem Index::operator[](int i){
//   return IndexItem(chrom[i], copy[i], start[i], end[i], label[i]);
// }





/**
 * Save index information into h5 file
 * 
 * Input Arguments:
 *   H5::H5File                                 - output h5 group
 *   unsigned int compression                  - compression level, default 6
 *   unsigned int chunksize                    - compression chunk size default 100000
 * 
 * Note:
 *   This function will generate a group "index" and save 
 *      chrom_sizes: int32 []
 *      chrom: int32 []
 *      start: int32 []
 *      end: int32 []
 *      label: string []
 *      copy: int32 []
 * 
 */
void Index::save(H5::H5File &loc, unsigned int compression, unsigned int chunksize){
    H5::Group index(loc.createGroup("index"));
    
    add_dataset1D(index, "chrom_sizes", chrom_sizes.data(), chrom_sizes.size(), compression, chunksize);
    add_dataset1D(index, "chrom", chrom.data(), chrom.size(), compression, chunksize);
    add_dataset1D(index, "start", start.data(), start.size(), compression, chunksize);
    add_dataset1D(index, "end", end.data(), end.size(), compression, chunksize);
    add_dataset1D(index, "label", label.data(), label.size(), compression, chunksize);
    add_dataset1D(index, "copy", copy.data(), copy.size(), compression, chunksize);
    
}
};
