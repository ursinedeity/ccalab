# pairs file tools
An example of tool handling pairs file using alab api

## Complie

use `make` to compile, 2 executable will be generated.

- sortpairs
- pairs2hcs


## Usage - sortpairs

Sort a pairs file.

```bash
$ sortpairs file.pairs > sorted.pairs
$ sortpairs file.pairs -o sorted.pairs
$ sortpairs file.pairs -c chr1-chr2-chr3-chr4-chr5-chr6-chr7-chr8-chr9-chr10-chr11-chr12-chr13-chr14-chr15-chr16-chr17-chr18-chr19-chrX > sorted.pairs
$ sortpairs file.pairs -f chr1-chr2-pos1-pos2 > sorted.pairs
$ sortpairs file.pairs -s lower > sorted.pairs

$ zcat file.pairs.gz | sortpairs > sorted.pairs
```
sortpairs <input file> < -o outfilename > < -c chrom_order > < -f field_order > < -s file_shape > < -t threads > < -g assembly >

### Parameters
-o  output filename
    default output to STDOUT

-c  chromosome order, seperated by '-'
    default sort by string comparison
    **if sepecified, chromosomes that are not in the list will be discared.**
    
-f  field order, seperated by '-'
    default sort by `chr1-chr2-pos1-pos2`

-s  file shape, output in `upper` triangle or `lower` triangle
    default is `upper` triangle

-t  thread used to sort

-g  genome assembly to be written to the file header


Note
    if input file is missing or '-', pipe will be used as input. 

## Usage - pairs2hcs

Take a sorted upper triangle pairs file and convert it to sparse skyline formated storage compactable with alabtools.

```bash
$ pairs2hcs sorted.pairs -c chr1-chr2-chr3-chr4-chr5-chr6-chr7-chr8-chr9-chr10-chr11-chr12-chr13-chr14-chr15-chr16-chr17-chr18-chr19-chrX -r 100000 -o 100kb.hcs -g mm10

$ zcat sorted.pairs.gz | sortpairs -c chr1-chr2-chr3-chr4-chr5-chr6-chr7-chr8-chr9-chr10-chr11-chr12-chr13-chr14-chr15-chr16-chr17-chr18-chr19-chrX -r 100000 -o 100kb.hcs -g mm10
```
sortpairs <input file> < -o outfilename > < -c chrom_order > < -g assembly >

### Parameters
-o  output filename

-c  chromosome order, seperated by '-'. Here it is defining the matrix ordering
    **if sepecified, chromosomes that are not in the list will be discared.**

-r  matrix resolution, default 100000

-g  genome assembly to be written


Note
    if input file is missing or '-', pipe will be used as input. 
