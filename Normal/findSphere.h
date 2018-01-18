/* Title: findSphere.h 
   Author: Shondell Baijoo
   Purpose: To locate the center of a sphere
  Date: 11/15/2017
*/ 

#ifndef FINDSPHERE_H_
#define FINDSPHERE_H_

#include "image.h"
#include <cstdio> 

namespace ComputerVisionProjects {

/* Binarize() goes through every pixel in the image and checks it against the given parameter threshold. 
   If the pixel value is is below the threshold, it will color that pixel black. Otherwise, the pixel will be white.
   Precondition: Greyscale image sent to function with loaded pixel values
   Postcondition: Image is now a binary image (black and white)  */
  void Binarize(int threshold, Image *input_image); 

/* Area() iterates through every pixel in the image in order to sum up the pixels for each (labeled) object
   Precondition: Image is labeled and binary, contains only one object
   Postcondition: Area of object will be calculated and returned */
  int Area(Image *input_image);


/* CalculateCenter() iterates through the entire image and sums up the x and y coordinates the object in the image.
   Once the sums are calculated it divides them by the area in order to find the center of mass.
   Precondition: Image is a labeled binary image and contains only one object, area has already been computed and sent into function
   Postcondition: xCenter and yCenter now contain the coordinate value for the centroid */ 
  void CalculateCenter(Image *input_image, int area, int &xCenter, int &yCenter); 

/* This function receives the center point of a known circle in a binary image and calculates that circle's diameter by counting the number of pixels on the y and x axis that goes through the center and taking the average of those two diameters. 
   Precondition: input_image is a binary image with a circle. x, y are the center points of that circle.
   Postcondition: returns the radius of the circle */
  int Radius(Image *input_image, int x, int y);

}

#endif
