
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
