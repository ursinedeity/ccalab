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

#include "h5file.hpp"

/**
 * Add attribute to and H5 H5Location overload string version
 * 
 * Input Arguments:
 *   H5::H5Location & loc         - Target to add attribute, can be group or file
 *   const std::string & name     - Attribute name
 *   const std::string & attr     - string Attribute
 * 
 */
void add_attribute(H5::H5Location &loc, const std::string &name, const std::string &attr){
    // Create new dataspace for attribute
    H5::DataSpace attr_dataspace = H5::DataSpace(H5S_SCALAR);
    
    // Create new string datatype for attribute
    H5::StrType strdatatype(H5::PredType::C_S1, H5T_VARIABLE);
    
    // Create attribute and write to it
    H5::Attribute att_in = loc.createAttribute(name, strdatatype, attr_dataspace);
    att_in.write(strdatatype, attr);
    
}



/**
 * Add attribute to and H5 H5Location overloaded int verion
 * 
 * Input Arguments:
 *   H5::H5Location & loc         - Target to add attribute, can be group or file
 *   const std::string & name     - Attribute name
 *   int attr                   - int Attribute
 * 
 */
void add_attribute(H5::H5Location &loc, const std::string &name, int attr){
    // Create new dataspace for attribute
    H5::DataSpace attr_dataspace = H5::DataSpace(H5S_SCALAR);
    
    // Create attribute and write to it
    H5::Attribute att_in = loc.createAttribute(name, H5::PredType::NATIVE_INT, attr_dataspace);
    att_in.write(H5::PredType::NATIVE_INT, &attr);
    
}



/**
 * Add 1D-dataset to H5::Group overloaded int verion
 * 
 * Input Arguments:
 *   H5::Group & loc              - Target to add dataset, can be group or file
 *   const std::string & name     - dataset name
 *   int *data                    - int array pointer
 *   unsigned int length          - array length
 *   unsigned int compression     - compression level, default 6
 *   unsigned int chunksize       - chunk size, default 100000
 * 
 */
void add_dataset1D(H5::Group &loc, const std::string &name, int *data, unsigned int length, unsigned int compression, unsigned int chunksize){
    hsize_t dims[1] = {length};
    if (chunksize > length)
        chunksize = length;
    hsize_t cdims[1] = {chunksize};
    // create new dspace
    H5::DataSpace dataspace(1, dims);
    
    // create dataset creation prop list
    H5::DSetCreatPropList ds_creatplist;
    ds_creatplist.setChunk( 1, cdims );
    // then modify it for compression
    ds_creatplist.setDeflate( compression );
    
    
    //Create the dataset.
    H5::DataSet dataset = loc.createDataSet(name, H5::PredType::NATIVE_INT, dataspace, ds_creatplist);
    dataset.write(data, H5::PredType::NATIVE_INT);
}




/**
 * Add 1D-dataset to H5::Group overloaded unsigned int verion
 * 
 * Input Arguments:
 *   unsigned int *data                    - int array pointer
 * 
 */
void add_dataset1D(H5::Group &loc, const std::string &name, unsigned int *data, unsigned int length, unsigned int compression, unsigned int chunksize){
    hsize_t dims[1] = {length};
    if (chunksize > length)
        chunksize = length;
    hsize_t cdims[1] = {chunksize};
    // create new dspace
    H5::DataSpace dataspace(1, dims);
    
    // create dataset creation prop list
    H5::DSetCreatPropList ds_creatplist;
    ds_creatplist.setChunk( 1, cdims );
    // then modify it for compression
    ds_creatplist.setDeflate( compression );
    
    
    //Create the dataset.
    H5::DataSet dataset = loc.createDataSet(name, H5::PredType::NATIVE_UINT, dataspace, ds_creatplist);
    dataset.write(data, H5::PredType::NATIVE_UINT);
}



/**
 * Add 1D-dataset to H5::Group overloaded float verion
 * 
 * Input Arguments:
 *   float *data                    - float array pointer
 * 
 */
void add_dataset1D(H5::Group &loc, const std::string &name, float *data, unsigned int length, unsigned int compression, unsigned int chunksize){
    hsize_t dims[1] = {length};
    if (chunksize > length)
        chunksize = length;
    hsize_t cdims[1] = {chunksize};
    // create new dspace
    H5::DataSpace dataspace(1, dims);
    
    // create dataset creation prop list
    H5::DSetCreatPropList ds_creatplist;
    ds_creatplist.setChunk( 1, cdims );
    // then modify it for compression
    ds_creatplist.setDeflate( compression );
    
    
    //Create the dataset.
    H5::DataSet dataset = loc.createDataSet(name, H5::PredType::NATIVE_FLOAT, dataspace, ds_creatplist);
    dataset.write(data, H5::PredType::NATIVE_FLOAT);
}




/**
 * Add 1D-dataset to H5::Group overloaded string verion
 * 
 * Input Arguments:
 *   std::string *data                 - string array pointer
 * 
 */
void add_dataset1D(H5::Group &loc, const std::string &name, std::string *data, unsigned int length, unsigned int compression, unsigned int chunksize){
    hsize_t dims[1] = {length};
    if (chunksize > length)
        chunksize = length;
    hsize_t cdims[1] = {chunksize};
    // create new dspace
    H5::DataSpace dataspace(1, dims);
    
    // create dataset creation prop list
    H5::DSetCreatPropList ds_creatplist;
    ds_creatplist.setChunk( 1, cdims );
    // then modify it for compression
    ds_creatplist.setDeflate( compression );
    
    H5::StrType strdatatype(H5::PredType::C_S1, H5T_VARIABLE);
    //Create the dataset.
    H5::DataSet dataset = loc.createDataSet(name, strdatatype, dataspace, ds_creatplist);
    dataset.write(data, strdatatype);
}



/**
 * Add scalar-dataset to H5::Group
 * 
 * Input Arguments:
 *   H5::Group & loc              - Target to add dataset, can be group or file
 *   const std::string & name     - dataset name
 *   int data                     - int data
 * 
 */
void add_scalar(H5::Group &loc, const std::string &name, int data){
    // Create new dataspace
    H5::DataSpace scalar_dataspace = H5::DataSpace(H5S_SCALAR);
    
    // Create dataset and write to it
    H5::DataSet scalar_in = loc.createDataSet(name, H5::PredType::NATIVE_INT, scalar_dataspace);
    scalar_in.write(&data, H5::PredType::NATIVE_INT);
}



/**
 * Add scalar-dataset to H5::Group overloed float version
 * 
 * Input Arguments:
 *   float data                   - float data
 * 
 */
void add_scalar(H5::Group &loc, const std::string &name, float data){
    // Create new dataspace
    H5::DataSpace scalar_dataspace = H5::DataSpace(H5S_SCALAR);
    
    // Create dataset and write to it
    H5::DataSet scalar_in = loc.createDataSet(name, H5::PredType::NATIVE_FLOAT, scalar_dataspace);
    scalar_in.write(&data, H5::PredType::NATIVE_FLOAT);
}




/**
 * Add scalar-dataset to H5::Group overloed string version
 * 
 * Input Arguments:
 *   std::string data                   - string data
 * 
 */
void add_scalar(H5::Group &loc, const std::string &name, const std::string &data){
    // Create new dataspace
    H5::DataSpace scalar_dataspace = H5::DataSpace(H5S_SCALAR);
    
    // Create new string datatype
    H5::StrType strdatatype(H5::PredType::C_S1, H5T_VARIABLE);
    
    // Create dataset and write to it
    H5::DataSet scalar_in = loc.createDataSet(name, strdatatype, scalar_dataspace);
    scalar_in.write(data, strdatatype);
}
