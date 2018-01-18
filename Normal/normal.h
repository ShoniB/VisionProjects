/* Title: normal.h 
   Author: Shondell Baijoo
   Purpose: To calculate inverse of a matrix, surface normals, and albedo
  Date: 11/15/2017
*/ 

#ifndef NORMAL_H
#define NORMAL_H

#include "image.h"
#include <cstdio> 
using namespace std;

namespace ComputerVisionProjects {

/* This function computes the inverse of a 3*3 matrix. 
   Precondition: s1, s2, and s3 are all size 3 arrays, representing the three rows of the matrix. 
   Postcondition: inv is a size 3*3 array and contains the inverse of S. 
*/
void getInverse(double s1[], double s2[], double s3[], long double inv[][3]); 

/* This function computers the surface normals. 
   Precondition: Image one, two, three are input images, with three different lighting configurations
   		 output is a copy of one of the input images, used to draw needles to represent normals of the surface
 		 inv is the inverse of the light source directions matrix of Images one, two and three
		 Step is an int variable used to determine the size of the grid of pixels used to compute normals of surface
		 Threshold is an int variable that determines which pixels to compute the normals of, as we don't want to compute it for pixels that do not appear in all three images  
  Postcondition: Output now has 'needles' drawn on it that represent the surface normals */
void computeNormals(Image *one, Image *two, Image *three, Image *output, long double inv[][3], int step, int threshold);

/* This function computes the albedo for each pixel in the images. 
   Precondition: Image one, two and three are input images with three different lighting configurations
  		 output is a copy of one of the input images, used to display albedo of the pixels
                 inv is the inverse of the light source directions matrx of Images one, two and three
		 threshold is an int variable used to determine which pixels we display the albedo of. If the pixel appears above the threshold in all three images, we display albedo, if not, we color it black
  Postcondition: output is now an albedo image, scaled by 70 */
void computeAlbedo(Image *one, Image *two, Image *three, Image *output, long double inv[][3], int threshold); 

}
#endif
