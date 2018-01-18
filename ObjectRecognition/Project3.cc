/* Title: Project3.cc 
   Shondell Baijoo
   Purpose: Reads a labeled image (from Project2) and outputs a database and orientation image. Database is a text file that contains e and area.
  Date: 9/20/2017
*/ 

#include "imageMod.h"
#include "imageFunc.h"
#include <cstdio>
#include <iostream>
#include <fstream> 
#include <string>
#include "DisjSets.h" 


using namespace std;
using namespace ComputerVisionProjects;

int main(int argc, char **argv){

  if (argc!=4) {
    printf("Usage: %s file1 filedatabase file2\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);  
  const string database_file(argv[2]);
  const string output_file(argv[3]);
  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  
  CreateLabels(&an_image);
  Area(&an_image); 
  CalculateCenter(&an_image);
  CalcABC(&an_image); 
  CalcTheta(&an_image);
  CalcE(&an_image);
  Database(&an_image, database_file); 
  DrawOrientation(&an_image);
 
  if (!WriteImage(output_file, an_image)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}
