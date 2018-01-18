/* Title: s1.cc 
   Author: Shondell Baijoo
   Purpose: This program takes an image of a sphere and outputs a textfile that records that sphere's center point and radius. 
   Date: 11/15/2017
*/ 
#include "image.h"
#include "findSphere.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s image threshold txtFile\n", argv[0]);
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

  Binarize(threshold, &an_image);
  int area = Area(&an_image); 
  int x=0, y=0; 
  CalculateCenter(&an_image, area, x, y);
  int rad = Radius(&an_image, x, y);
  ofstream data(output_file.c_str()); 
  data << x << " " << y << " " << rad << endl;
  data.close(); 
  
  return 0;
}

