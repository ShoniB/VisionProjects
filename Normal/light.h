/* Title: light.h 
   Author: Shondell Baijoo
   Purpose: To calculate light source direction
  Date: 11/25/2017
*/ 

#ifndef LIGHT_H
#define LIGHT_H

#include "image.h"
#include <cstdio> 

namespace ComputerVisionProjects {

/* This function finds the brightest pixel on the sphere and returns it in variables x, y as well as the value of that pixel in variable intensity. 
   Precondition: centerX, centerY, and radius indicates the center and radius of the sphere
   Postcondition: x, y contains point of brightest pixel and intensity is the value of that pixel */
void getIntensity(Image* input_image, int centerX, int centerY, int radius, int& x, int& y, int& intensity);

/* This function returns the vector of the light source normal (s * n) in variables xN, yN, and zN 
   Precondition: center pixel(centerX, centerY), radius, light source pixel(lightX, lightY), and light source pixel value(intensity) have been found and sent in as parameters 
   Postcondition: xN, yN, and zN contain values for light source normal vector */
void lightNormal(int lightX, int lightY, int intensity, int centerX, int centerY, int radius, double& xN, double& yN, double& zN);

} 

#endif
