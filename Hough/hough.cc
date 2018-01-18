/* Title: hough.cc 
   Author: Shondell Baijoo
   Purpose: Function declarations for implementation of hough algorithm 
  Date: 10/31/2017
*/ 

#include "hough.h" 
#include "image.h" 
#include <iostream>
#include <fstream> 
#include <cmath> 

void Hough(Image *inputImage, Image *hImage, const string arrayFile)
{
  double half_degree = (0.0174533)/2.0; // .5 degree in radian 
  // rMax is the max rho value/2, computing for every two rhos
  int rMax = ((sqrt(pow(inputImage->num_rows(),2) + pow(inputImage->num_columns(),2)))/2)+1;
  int accum[361][rMax]; // accumulator array to hold votes
 
  for(int i=0; i<361; i++) // set accumulator array to 0
  {
      for(int j=0; j<rMax; j++)
	 accum[i][j] = 0; 
  } 

// Increment votes
  for(int i=0; i<inputImage->num_rows(); i++) // For every point
  {
    for(int j=0; j<inputImage->num_columns(); j++)
    {
	if(inputImage->GetPixel(i,j) == 255) // if it is an edge
	{
	  double angle = 0.0; 
	  for(int h=0; h<361; h++) // for every angle in out resolution 
	  { 
	    int r = i*cos(angle) + j*sin(angle); // detect possible line the point could belong to 
	    r = r/2; // divide rho by 2 (voting for every 2 rho) 
	    if(r<rMax) // if it is within the image space
	    {
	       accum[h][r]++; // vote 
	    }
	    angle+=half_degree; // increment and check next angle 
	  }// for h
	}// end if
    } // for j
  }//for i

  // Fill file and set points in hough image
  ofstream votes(arrayFile.c_str()); // vote array file
  hImage->AllocateSpaceAndSetSize(361, rMax); // set dimensions of hough image file
  hImage->SetNumberGrayLevels(255);

  for(int i=0; i<361; i++) // add values to file and image 
  {  
	votes << "T" <<i << " "; // T# marks a new theta 
	for(int j=0; j<rMax; j++) 
	{
	   votes << accum[i][j] << " "; // add votes to text 
	   int color = accum[i][j]; 
  	   if(color > 255)
		color = 255; // max color = white
           hImage->SetPixel(i, j, color);  // add color in hough image
	}
	votes << endl;
  } // end for i
  votes.close(); 
} //end Hough()
