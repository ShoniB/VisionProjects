/* Title: findSphere.cc
   Author: Shondell Baijoo
   Purpose: To locate the center of a sphere
  Date: 11/15/2017
*/ 

#include "findSphere.h" 

using namespace std;
namespace ComputerVisionProjects
{

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


int Area(Image *input_image) 
{
  int area =0; 
  if(input_image==nullptr) abort(); 

    for(int i=0; i<input_image->num_rows(); i++) // iterate through image
    {
      for(int j=0; j<input_image->num_columns(); j++)
      {
	 if(input_image->GetPixel(i,j) == 255)
	    area++; // +1 to area of object
      }
    } // end i
    return area;
} // end Area()


void CalculateCenter(Image *input_image, int area, int &xCenter, int &yCenter)
{
  int x=0, y=0; 
  for(int i=0; i<input_image->num_rows(); i++) // sum up x's and y's 
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	if(input_image->GetPixel(i,j) == 255)
	{
	  x+=i;  
	  y+=j;  
	}
    }
  }  // end summation
  xCenter = x/area; 
  yCenter = y/area; 
} // end CalculateCenter

int Radius(Image *input_image, int x, int y)
{
  int leftr=0, rightr=0, topr=0, downr=0; // variables to count up radii
  int i = x, j = y; // center points
  while(i>=0 && input_image->GetPixel(i,j) == 255) // traverse left of center
  {
    leftr++; 
    i--; 
  }
  i=x+1; // we don't want to recount x,y
  while(i<input_image->num_columns() && input_image->GetPixel(i,j) == 255) //traverse right
  {
    rightr++; 
    i++;
  }
  i=x; j=y; // reset position
  while(j>=0 && input_image->GetPixel(i,j) == 255) // traverse up 
  {
     topr++;
     j--;
  }
  j=y+1; //don't want to recount x,y
  while(j<input_image->num_rows() && input_image->GetPixel(i,j) == 255) //traverse down
  {
    downr++;
    j++;
  }
  int diameter_vert = topr + downr; 
  int diameter_horiz = leftr + rightr; 
  int diameter = (diameter_vert + diameter_horiz) / 2; //avg of both diameters
  return diameter/2; //radius
}

}//computervisionprojects
