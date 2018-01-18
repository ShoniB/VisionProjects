/* Title: normal.cc
   Author: Shondell Baijoo
   Purpose: Functions to compute the inverse of a matrix and the normals and albedos of pixels for three images. 
  Date: 11/25/2017
*/ 

#include "normal.h" 
#include<iostream>
#include <cmath> 
using namespace std;
namespace ComputerVisionProjects {

void getInverse(double s1[], double s2[], double s3[], long double inv[][3])
{
  // compute matrix of cofactors
  double minors[3][3]; 
  minors[0][0] = s2[1]*s3[2] - s2[2]*s3[1];
  double det1 = minors[0][0]; // save minor determinant in order to be used to compute matrix determinant later 
  minors[0][1] = (s2[0]*s3[2] - s2[2]*s3[0]) * -1.0;
  double det2 = minors[0][1] * -1.0; 
  minors[0][2] = s2[0]*s3[1] - s2[1]*s3[0];
  double det3 = minors[0][2]; 
  minors[1][0] = (s1[1]*s3[2] - s1[2]*s3[1]) * -1.0; 
  minors[1][1] = s1[0]*s3[2] - s1[2]*s3[0]; 
  minors[1][2] = (s1[0]*s3[1] - s1[1]*s3[0]) * -1.0; 
  minors[2][0] = s1[1]*s2[2] - s1[2]*s2[1]; 
  minors[2][1] = (s1[0]*s2[2] - s1[2]*s2[0]) * -1.0; 
  minors[2][2] = s1[0]*s2[1] - s1[1]*s2[0]; 
  // transpose to create adjoint matrix 
  double temp = minors[0][1]; 
  minors[0][1] = minors[1][0]; 
  minors[1][0] = temp; 
  temp = minors[0][2];
  minors[0][2] = minors[2][0]; 
  minors[2][0] = temp; 
  temp = minors[1][2]; 
  minors[1][2] = minors[2][1]; 
  minors[2][1] = temp; 
  //get determinant of S 
  long double det = s1[0] * det1 - 
	       s1[1] * det2 +
	       s1[2] * det3;
  // divide adj(s) by determinant and save in inv[][]
  for(int i=0; i<3; i++)
  {
    for(int j=0; j<3; j++)
    {
	inv[i][j] = minors[i][j] / det; 
    }
  }  
}// end getInverse


void computeNormals(Image *one, Image *two, Image *three, Image *output, long double inv[][3], int step, int threshold)
{
  for(int i=0; i<one->num_rows(); i+=step)
  {
     for(int j=0; j<one->num_columns(); j+=step)
     {
       int mid = step/2;
       if(i+mid < one->num_rows() && j+mid < one->num_columns()) // check boundaries
       { 
         int i1 = one->GetPixel(i+mid, j+mid);
         int i2 = two->GetPixel(i+mid, j+mid); 
	 int i3 = three->GetPixel(i+mid, j+mid); 
 	 if(i1 > threshold && i2 > threshold && i3 > threshold) // compute normal
	 {
	   double n1=0, n2=0, n3=0; 
	   n1 = (inv[0][0] * i1) + (inv[0][1] * i2) + (inv[0][2] * i3); 
	   n2 = (inv[1][0] * i1) + (inv[1][1] *i2) + (inv[1][2] * i3); 
	   n3 = (inv[2][0] * i1) + (inv[2][1] *i2) + (inv[2][2] * i3); 
	   double length = sqrt(n1*n1 + n2*n2 + n3*n3); 
	   double nX, nY, nZ;
           if(length!=0.0) // don't divide by zero 
	   {
	     nX = n1/length; 
	     nY = n2/length; 
	   } 
	   double nXScaled = nX * 10; // scale values to get line  
	   double nYScaled = nY * 10;
           int pointX = nXScaled + (i+mid); // add value to (x,y)
	   int pointY = nYScaled + (j+mid); 
	   if(pointX < output->num_rows() && pointY < output->num_columns()) // check boundaries 
	   	DrawLine(i+mid, j+mid, pointX, pointY, 255, output);
	   output->SetPixel(i+mid, j+mid, 0); // set a dot  
	}//end if
       }// end if check boundaries
     }//end j
  }//end i

} //end ComputeNormals


void computeAlbedo(Image *one, Image *two, Image *three, Image *output, long double inv[][3], int threshold)
{
  for(int i=0; i<one->num_rows(); i++)
  {
     for(int j=0; j<one->num_columns(); j++)
     {
         int i1 = one->GetPixel(i, j); // get pixel values for all three images 
         int i2 = two->GetPixel(i, j); 
	 int i3 = three->GetPixel(i, j); 
 	 if(i1 > threshold && i2 > threshold && i3 > threshold) // compute albedo
	 {
	   double n1=0.0, n2=0.0, n3=0.0; // compute n 
	   n1 = (inv[0][0] * i1) + (inv[0][1] * i2) + (inv[0][2] * i3); 
	   n2 = (inv[1][0] * i1) + (inv[1][1] *i2) + (inv[1][2] * i3); 
	   n3 = (inv[2][0] * i1) + (inv[2][1] *i2) + (inv[2][2] * i3); 
	   double length = sqrt(n1*n1 + n2*n2 + n3*n3); // get |N|, or albedo 
	   int albedo = length*80; // scale albedo 
           if(albedo < 0) albedo=0; 
	   if(albedo > 255) albedo=255;
           output->SetPixel(i,j,albedo);
	}//end if
	else // if pixel < threshold, make that pixel black 
	   output->SetPixel(i,j,0); 
     }//end j
  }//end i

} //end computealbedo

} // end CVP


