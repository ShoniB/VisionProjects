/* Title: s2.cc 
   Author: Shondell Baijoo
   Purpose: This program takes three images of the same object in different lighting and outputs the light source direction vector for each of those images. 
   Date: 11/24/2017
*/ 
#include "image.h"
#include "light.h"
#include <cstdio>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
using namespace ComputerVisionProjects;

int
main(int argc, char **argv){

  if (argc!=6) {
    printf("Usage: %s parametersTXT image1 image2 image3 outputTXT\n", argv[0]);
    return 0;
  }
  const string input_file(argv[1]); 
  const string image1(argv[2]);
  const string image2(argv[3]);
  const string image3(argv[4]);
  const string output_file(argv[5]);

  // open images 1, 2, 3
  Image image_1, image_2, image_3;
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
  // retrieve data from parameters file
  ifstream circleData(input_file.c_str()); 
  int xCenter, yCenter, radius; 
  circleData >> xCenter; 
  circleData >> yCenter; 
  circleData >> radius; 
  circleData.close(); 
  
  int x_1=0, y_1=0, intensity_1=0; // light source x,y, and intensity 
  int x_2=0, y_2=0, intensity_2=0;  
  int x_3=0, y_3=0, intensity_3=0; 
  getIntensity(&image_1, xCenter, yCenter, radius, x_1, y_1, intensity_1);
  getIntensity(&image_2, xCenter, yCenter, radius, x_2, y_2, intensity_2);
  getIntensity(&image_3, xCenter, yCenter, radius, x_3, y_3, intensity_3); 

// initialize vector variables 
  double s1X=0, s2X=0, s3X=0;
  double s1Y=0, s2Y=0, s3Y=0; 
  double s1Z=0, s2Z=0, s3Z=0;  

  lightNormal(x_1, y_1, intensity_1, xCenter, yCenter, radius, s1X, s1Y, s1Z);
  lightNormal(x_2, y_2, intensity_2, xCenter, yCenter, radius, s2X, s2Y, s2Z);
  lightNormal(x_3, y_3, intensity_3, xCenter, yCenter, radius, s3X, s3Y, s3Z);

  ofstream data(output_file.c_str()); 
  data << s1X << " " << s1Y << " " << s1Z << endl  
	<< s2X << " " << s2Y << " " << s2Z << endl
	<< s3X << " " << s3Y << " " << s3Z <<endl;
  data.close(); 
  
  return 0;
}

