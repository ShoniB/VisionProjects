/* Title: light.cc
   Author: Shondell Baijoo
   Purpose: Functions to calculate light source direction
  Date: 11/25/2017
*/ 
#include "light.h" 
#include<iostream> 
#include <cmath> 
using namespace std;
namespace ComputerVisionProjects {

void getIntensity(Image* input_image, int centerX, int centerY, int radius, int& x, int& y, int& intensity)
{
    intensity=-1;
    for(int i=centerX-radius; i<=(centerX+radius); i++) // iterate through square around sphere
    {
	for(int j=centerY-radius; j<=(centerY+radius); j++)
	{
	    if(intensity < input_image->GetPixel(i,j)) // set max light source and coordinates
	    {
		intensity = input_image->GetPixel(i,j);
		x=i; 
		y=j; 
	    }
	}
    } //end i 
}// end getIntenisty

void lightNormal(int lightX, int lightY, int intensity, int centerX, int centerY, int radius, double& xN, double& yN, double& zN)
{
    double x = lightX - centerX; // lightX, lightY is the light source point
    double y = lightY - centerY;
    double z = sqrt( (pow(radius, 2) - pow(x, 2) - pow(y, 2)) );  // Z1 - Z0 = R^2 - (X1-X0)^2 - (Y1-Y0)^2
    //normalize
    double normalize = sqrt(x*x + y*y + z*z); 
    x = x / normalize; 
    y = y / normalize; 
    z = z / normalize; 
    // scale by light intensity 
    xN = x * intensity; 
    yN = y * intensity; 
    zN = z * intensity;
} // end lightNormal

} // end compvisionprojects
