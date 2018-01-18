/* Title: h3.cc 
   Shondell Baijoo
   Purpose: Reads a binary edge image and votes for potential lines in the image. Outputs a hough space image and file containing votes for voting array. 
  Date: 10/31/2017
*/ 
#include "image.h"
#include "hough.h"
#include <cstdio>
#include <iostream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=4) {
    printf("Usage: %s file1 file2 textfile3\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]);
  const string output_file(argv[2]);
  const string votingArray_file(argv[3]); 

  Image an_image;
  if (!ReadImage(input_file, &an_image)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  Image hImage;  // hough image
  Hough(&an_image, &hImage, votingArray_file);
  
  if (!WriteImage(output_file, hImage)){
    cout << "Can't write to file " << output_file << endl;
    return 0;
  }
}


