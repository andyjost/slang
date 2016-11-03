#!/usr/bin/zsh

# Edit $indir to point to the top directory.  A consolidated .hpp file for each
# direct subdirectory will be created.

indir='boost'
outprefix='output-'
mkdir -p $outprefix$indir
find $indir/* -maxdepth 0 -type d | parallel -j+2 --eta \
    '
    setopt noclobber
    in={}
    out='$outprefix'$in.hpp
    { time consolidate_directory_functions.py $in || rm $out } > $out
    '
