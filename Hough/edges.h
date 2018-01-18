/* Title: hough.cc 
   Author: Shondell Baijoo
   Purpose: Function declarations for using Sobel filter to create edge image and binarizing a greyscale image
  Date: 10/31/2017
*/ 

#ifndef EDGES_H
#define EDGES_H

#include "image.h" 

using namespace ComputerVisionProjects;

/* Find edges of image using squared gradient filter (Sobel) 
   PreCondition: inputImage is a valid greyscale pgm image 
   PostCondition: inputImage is edited to now be a greyscale edge image
*/ 
void Edges(Image *inputImage); 


/* Binarize() goes through every pixel in the image and checks it against the given parameter threshold. 
   If the pixel value is is below the threshold, it will color that pixel black. Otherwise, the pixel will be white.
   Precondition: Greyscale image sent to function with loaded pixel values
   Postcondition: Image is now a binary image (black and white)  */
void Binarize(int threshold, Image *input_image); 


#endif

