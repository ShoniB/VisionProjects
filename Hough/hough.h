/* Title: hough.h 
   Author: Shondell Baijoo
   Purpose: Function definitions for implementation of hough algorithm 
  Date: 10/31/2017
*/ 

#ifndef HOUGH_H
#define HOUGH_H

#include "image.h" 
#include <string>
using namespace std; 
using namespace ComputerVisionProjects;

/* Computes hough algorithm on image, creates a file containing the voting array, and modifies hImage to become a hough image
   The hough space resolution is for every half degree and every 2 rho values 
   Precondition: hImage is an empty Image, inputImage is a binary edge detected image, and arrayFile is a nonempty string
   Postcondition: arrayFile is created as a text file that holds votes for all theta, rho in the image space
   hImage is filled as a hough image where the higher intensity votes are a brighter white   */ 
void Hough(Image *inputImage, Image *hImage, const string arrayFile); 

#endif
