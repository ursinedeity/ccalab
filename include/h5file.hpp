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

#ifndef __ALAB_H5FILE
#define __ALAB_H5FILE

#include <string>
#include "H5Cpp.h"

void add_attribute(H5::H5Location &loc, const std::string &name, const std::string &attr);
void add_attribute(H5::H5Location &loc, const std::string &name, int attr);

void add_dataset1D(H5::Group &loc, const std::string &name, int *data, unsigned int length, unsigned int compression = 6, unsigned int chunksize = 100000);
void add_dataset1D(H5::Group &loc, const std::string &name, unsigned int *data, unsigned int length, unsigned int compression = 6, unsigned int chunksize = 100000);
void add_dataset1D(H5::Group &loc, const std::string &name, float *data, unsigned int length, unsigned int compression = 6, unsigned int chunksize = 100000);
void add_dataset1D(H5::Group &loc, const std::string &name, std::string *data, unsigned int length, unsigned int compression = 6, unsigned int chunksize = 100000);

void add_scalar(H5::Group &loc, const std::string &name, int data);
void add_scalar(H5::Group &loc, const std::string &name, float data);
void add_scalar(H5::Group &loc, const std::string &name, const std::string &data);

#endif
