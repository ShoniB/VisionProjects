/* Title: h4.cc 
   Shondell Baijoo
   Purpose: Reads a txt file containing hough votes. Using this it detects lines within the image and outputs a greyscale image with lines drawn over top of it. This draws finite lines. (bonus question) 
  Date: 10/31/2017
*/ 
#include "image.h"
#include "detectfinite.h"
#include "edges.h"
#include <cstdio>
#include <iostream>
#include <string>
#include <fstream>

using namespace std;
using namespace ComputerVisionProjects;

void Binarize(int threshold, Image *input_image);

int
main(int argc, char **argv){
  
  if (argc!=5) {
    printf("Usage: %s file1 txtfile2 threshold file4\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string votingArray_file(argv[2]);
  string input_num(argv[3]); 
  const string output_file(argv[4]);
  int threshold = stoi(input_num); // get threshold from input

  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  Image copy; // copy image in order to create binarized version (for Finite lines only) 
  if (!ReadImage(input_file, &copy)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
 // Get edges and binarize them with a low threshold: for finding finite lines
  Edges(&copy);
  Binarize(50, &copy); 

  ifstream votes(votingArray_file.c_str()); 

  DetectLines(&an_image, &copy, votes, threshold);  // detect lines and modify an_image to have detected lines drawn on them 
  
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}

