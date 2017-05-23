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

#ifndef __ALAB_UTILS
#define __ALAB_UTILS
#include <vector>
#include <string>
#include <map>
#include "h5file.hpp"

namespace alab{
// A container of references, just in case one wants
// to use operator [] on index.
struct IndexItem{
    int& chrom;  // chromosome id
    int& copy;   // chromosome copy
    int& start;  // starting base pair
    int& end;    // ending base pair
    std::string& label;  // label for gap, domains, etc.
    IndexItem(int& ch, int& cp, int& st, int& en, std::string& lb):
        chrom(ch), copy(cp), start(st), end(en), label(lb) {};
};

// Keep the index. All the variables are public since this is supposed 
// to be a mere container, and to keep syntax simple.
// I'm not considering weird cases where records are inserted in a 
// non-consecutive way.
class Index{
public:
    Index(){}
    Index(const std::vector<int> &chromList, 
          const std::vector<int> &startList, 
          const std::vector<int> &endList,
          const std::vector<int> &chrom_sizes
         );

    std::vector<int> chrom;  // chromosome ids
    std::vector<int> copy;   // chromosome copies
    std::vector<int> start;  // starting basepairs
    std::vector<int> end;    // ending basepairs
    std::vector<std::string> label; // labels

    unsigned int num_chrom,size;  // number of chromosomes
    std::vector<int> chrom_sizes;  // sizes of chromosomes
    std::vector<int> offset;  // start position for each chromosome
    
    // returns an IndexItem, a container of references
    // to the values. Keep in mind this could break
    // badly if IndexItem is used after Index goes out of 
    // scope, for example.
    //IndexItem operator[](int i);
    
    // pushes back a record
    void push_back(int chrom, int copy, int start, int end, 
                   const std::string& label = "");

    // update num_chrom and the chrom_* vectors. Call if the data
    // vectors have been directly modified. 
    void rebuild_internal_index();
    
    void save(H5::H5File &loc, unsigned int compression = 6, unsigned int chunksize = 100000);

}; // class Index


class Genome{
public:
    Genome(){}
    std::string assembly;
    std::vector<std::string> chroms;
    std::vector<int> origins;
    std::vector<int> lengths; 
    Genome(const std::string &assembly, 
           const std::vector<std::string> &chroms, 
           const std::vector<int> &origins, 
           const std::vector<int> &lengths);
    Genome(const std::string &assembly, 
           const std::vector<std::string> &chroms, 
           const std::vector<int> &lengths);
    std::string get_chrom(unsigned int c);
    int get_chromnum(const std::string & chrom);
    Index BinInfo(unsigned int resolution);
    
    void save(H5::H5File &loc, unsigned int compression = 6, unsigned int chunksize = 10000);
private:
    std::map<std::string, int> chromMap;
    
}; // struct genome

};
#endif
