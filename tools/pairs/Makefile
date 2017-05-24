all:
	g++ -Wall -O3 -std=c++11 -I ../../include -L ../../lib sortpairs.cpp PairsFileHeader.cpp PairsFileRecord.cpp Sort.cpp -o sortpairs -lalab -lhdf5 -lhdf5_cpp
	g++ -Wall -O3 -std=c++11 -I ../../include -L ../../lib PairsFileHeader.cpp PairsFileRecord.cpp Builder.cpp pairs2hcs.cpp -o pairs2hcs -lalab -lhdf5 -lhdf5_cpp
