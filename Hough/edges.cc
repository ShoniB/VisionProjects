/* Title: hough.cc 
   Author: Shondell Baijoo
   Purpose: Function definitions for using Sobel filter to create edge image and binarizing a greyscale image
  Date: 10/31/2017
*/

#include "edges.h" 
#include "image.h"
#include <cmath> 
#include <iostream> 
#include <vector>
using namespace std;

using namespace ComputerVisionProjects;

void Edges(Image *inputImage)
{
  vector<vector<int>> delta1; // to store filter output of delta1 
  vector<vector<int>> delta2; // delta2, with respect x 

  int filter1[3][3] = {{-1,0,1}, {-2,0,2}, {-1,0,1}}; // delta1 filter: y axis 
  int filter2[3][3] = {{1,2,1}, {0,0,0}, {-1,-2,-1}}; // delta2 filter: x axis 

  for(int i=0; i<inputImage->num_rows(); i++) // for all points in image
  {
    vector<int> temp, temp2; // pushback vectors into delta1 and 2
    delta1.push_back(temp); 
    delta2.push_back(temp2); 
    for(int j=0; j<inputImage->num_columns(); j++) 
    {
	int value=0, value2=0; 
	for(int n = 0; n<3; n++) // Iterate through filter 
        {                         // Calculate both filter 1 and 2 since they are the same size
	  if(!(i-n<0)) // if we are not out of the image boundary  
	  {  
	    for(int m=0; m<3; m++)
	    {
	     if(!(j-m<0))
	     {
		value = value + (filter1[n][m] * inputImage->GetPixel(i-n,j-m)); // calculate value for filter1
		value2 = value2 + (filter2[n][m] * inputImage->GetPixel(i-n,j-m)); // value for filter2
	     }
	    }// end for m
	  } // end if
	} // end for n
        delta1[i].push_back(value); // add to deltas
	delta2[i].push_back(value2);
    } // end for j 
  } // end for i
  
// write image
  for(int i=0; i<inputImage->num_rows(); i++)
  {
    for(int j=0; j<inputImage->num_columns(); j++)
    {
        int pixel_value = sqrt(pow(delta1[i][j],2) + pow(delta2[i][j],2)); // get squared gradient
	if(pixel_value < 0) // threshold colors to be between 0 and 255
	   pixel_value = 0; 
        if(pixel_value > 255)
	   pixel_value = 255;
        inputImage->SetPixel(i,j, pixel_value); // set pixel in edge image 
    }
  }
} // end Edges()


void Binarize(int threshold, Image *input_image) 
{
  if (input_image == nullptr) abort();
  for(int i=0; i<input_image->num_rows(); i++) // traverse rows
  {
    for(int j=0; j<input_image->num_columns(); j++) // traverse columns
    {
	if(input_image->GetPixel(i,j) < threshold) // check pixel value against threshold
	    input_image->SetPixel(i,j,0); // set pixel to black
	else
	    input_image->SetPixel(i,j,255); // set pixel to white
    }
  } //end i 
} // end Binarize
