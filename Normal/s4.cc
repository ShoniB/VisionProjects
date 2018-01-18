/* Title: s4.cc 
   Author: Shondell Baijoo
   Purpose: This program takes a textfile containing light source vectors and computes the albedo of the visible pixels in the three images. It outputs an image that displays the scaled albedos of the pixels.
   Date: 11/24/2017
*/ 
#include "image.h"
#include "normal.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){
  
  if (argc!=7) {
    printf("Usage: %s directions image1 image2 image3 threshold outputImage \n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]); 
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
 
  string thres_str = argv[5];
  int threshold = stoi(thres_str); 
  const string output_image_name(argv[6]); 

  // open images 1, 2, 3, and outputimage(image 1) 
  Image image_1, image_2, image_3, outputImage;
  if (!ReadImage(image1, &image_1)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  if (!ReadImage(image2, &image_2)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  if (!ReadImage(image3, &image_3)) {
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }
  if (!ReadImage(image1, &outputImage)) { // output needles will be on image1 
    cout <<"Can't open file " << input_file << endl;
    return 0;
  }

  // put S into arrays 
  ifstream data(input_file.c_str());
  double s1[3]; 
  data >> s1[0]; data >> s1[1]; data >> s1[2]; 
  double s2[3]; 
  data >> s2[0]; data >> s2[1]; data >> s2[2]; 
  double s3[3]; 
  data >> s3[0]; data >> s3[1]; data >> s3[2]; 
 
  long double inverse[3][3]; // S-inverse

  getInverse(s1, s2, s3, inverse); // compute S-inverse
  
  computeAlbedo(&image_1, &image_2, &image_3, &outputImage, inverse, threshold); 

  if (!WriteImage(output_image_name, outputImage)){
    cout << "Can't write to file " << output_image_name << endl;
    return 0;
  }

   return 0; 
}

