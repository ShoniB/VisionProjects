/* Title: Project1.cc 
   Shondell Baijoo
   Purpose: Reads a grey scale image and outputs it as a binary image
  Date: 9/20/2017
*/ 

#include "imageMod.h"
#include <cstdio>
#include <iostream>
#include <fstream> 
#include <string>
#include <vector> 
#include <algorithm> 
#include <map> 
#include "DisjSets.h" 
#include "imageFunc.h"
#include <cmath> 

using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 threshold file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  string input_number = argv[2];
  int threshold = stoi(input_number); // This is the threshold used for making the image binary 
  const string output_file(argv[3]);
  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  Binarize(threshold, &an_image); // Make a binary image from the input2
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }

}

