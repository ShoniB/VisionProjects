/* Title: detectfinite.cc 
   Author: Shondell Baijoo
   Purpose: Function definitions for detecting finite lines using hough voting array 
  Date: 10/31/2017
*/ 

#include <iostream>
#include <vector> 
#include <utility> 
#include <string>
#include <map> 
#include <cmath>
#include "image.h" 
#include "DisjSets.h"
#include "detectfinite.h" 
using namespace std;

void DetectLines(Image *an_image, Image *bin_image, ifstream &votes, int threshold)
{
  string rho; 
  double angle = 0; 
  int rhoCount = 0; 
  vector<pair<double, int>> lines; // to store detected lines 
  vector<vector<pair<int,int>>> segment;  // pair: label, intensity 
  int counter =-1; // to iterate through segment

  while(votes >> rho) // get results from file
  {
    if((rho.size() != 0) && rho[0] == 'T') // new theta: 0 - 360 (.5 degree) 
    {
  	vector<pair<int,int>> temp; // add a new vector to segment
	segment.push_back(temp); 
	counter++; // set counter for that vector 
    }
    else
    {
	int rVal = stoi(rho);
	if(rVal > threshold) // if votes>threshold
	{
          pair<int, int> aPair = make_pair(-1, rVal); // store votes in segment
	  segment[counter].push_back(aPair);
	}
	else
	{
	   pair<int,int> aPair = make_pair(-1,-1); // add 'empty' value to segment (used for finding connected areas of high intensity)  
	   segment[counter].push_back(aPair);
	} //end else
    } // endelse
  } //endwhile

  GetAreas(segment, lines); // Get areas of brightness by labeling segment and return detected lines 
 
 // plot detected lines lines 
  for(int i=0; i<an_image->num_rows(); i++) // for every point
  {
    for(int j=0; j<an_image->num_columns(); j++)
    {
	for(int k=0; k<lines.size(); k++) // for every line
	{
	   if( lines[k].second == int(i*cos(lines[k].first) + j*sin(lines[k].first)) ) // if point lies on detected line, plot
	   {
		if(nearEdge(bin_image, i,j)) // if an edge
		    an_image->SetPixel(i,j,255); // color point on line white
	   }
	} //for k
    }//for j
  }// for i
}//end DetectLines

void GetAreas(vector<vector<pair<int,int>>>& segment, vector<pair<double, int>>& lines)
{
// segment: label, value
  int label=0; // start label counter at 0 
  DisjSets setTable; // equivalence table using union-find algorithm
  setTable.addElement(); // add label 0 to table

  if(segment[0][0].second > -1) // Look at first value
  { 
	segment[0][0].first = label; // label first pixel 0 if it is an object
  }
  for(int j=1; j<segment[0].size(); j++) // Check first row, only look at left neighbor
  {
    if(segment[0][j].second > -1) // if value has not been thresholded
    {
	if(segment[0][j-1].first != -1) // If neighbor is labeled 
	{
	   segment[0][j].first = segment[0][j-1].first;  // set label to neighbor's label
	}
	else
        {
	   segment[0][j].first = ++label; // Else give new label
	   setTable.addElement(); // add a new label to table 	
	}
    }
  } // end first row
  for(int i=1; i<segment.size(); i++) // Check first column, only look at top neighbor
  {
    if(segment[i][0].second > -1) // if object
    {
	if(segment[i-1][0].first != -1) // if top neighbor is labeled
	{
	  segment[i][0].first = segment[i-1][0].first;  // set label to neighbor's label
	}
	else 
	{
	   segment[i][0].first = ++label;  //Give new label 
	   setTable.addElement(); // add label to table
	} 
    }  
  } // end first column

  //rest of image - we are checking Assymetrical Above neighbors (top, top-left, and left)
  for(int i=1; i<segment.size(); i++)
  {
    for(int j=1; j<segment[i].size(); j++)
    {
	if(segment[i][j].second > -1)  //if area of brightness
	{
	  int min = 99999; // initialize minimum for comparison to neighbors 
	  if(segment[i][j-1].first != -1) // check if LEFT is labeled 	
	    min = segment[i][j-1].first; // set min to left label
	  if(segment[i-1][j].first != -1) // check TOP
	  {
	    if(min>segment[i-1][j].first) // set min to smallest label
		min = segment[i-1][j].first;  
	    if(segment[i][j-1].first != -1 && segment[i][j-1].first != segment[i-1][j].first)
	    // If top and left are labeled, and are not the same label 
	    {
		int x = setTable.find(segment[i][j-1].first); // find root of left label
		int y = setTable.find(segment[i-1][j].first); // find root of top label
		if(x!=y) // If the roots are not the same
	          setTable.unionSets(x, y); // Connect the roots
	    }
	  } //done checking top 
	  if(segment[i-1][j-1].first != -1) // check TOP-LEFT
	  {
	    if(min>segment[i-1][j-1].first) // set min to smallest label
		min= segment[i-1][j-1].first; 
	    if(segment[i][j-1].first != -1 && segment[i][j-1].first != segment[i-1][j-1].first)
	    { // if left is a label and top left and left labels are different
		int x = setTable.find(segment[i][j-1].first); // get roots of left and top left labels
		int y = setTable.find(segment[i-1][j-1].first); 
		if(x!=y) // If the roots are not the same
	          setTable.unionSets(x, y); // Connect the roots 
	    }
	    if(segment[i-1][j].first != -1 && segment[i-1][j].first != segment[i-1][j-1].first)
	    { // If top is a label and top left and top labels are different 
		int x = setTable.find(segment[i-1][j].first); // get roots of labels
		int y = setTable.find(segment[i-1][j-1].first); 
		if(x!=y) // If the roots are not the same
	       	 setTable.unionSets(x, y); // Connect the roots 
	    }
	  }// done checking topleft
	  if(min == 99999){ // If none of the neighbors were labeled
	 	segment[i][j].first = ++label; // add a new label
		setTable.addElement(); // add new label to table
	  }
	  else segment[i][j].first = min; // else set smallest label as label
	} // end if area of brightness
    }	// end for j
  } // end for i

  std::map<int, Area> areas; // To hold each area of brightness' values
  vector<int> roots = setTable.getRoots(); 
  for(int i=0; i<roots.size(); i++)
	areas[roots[i]]; // one area for each root

  double angle=0.0; // to store in areas
  for(int i=0; i<segment.size(); i++) // for each point in segment 
  {
    for(int j=0; j<segment[i].size(); j++)
    {
	if(segment[i][j].first != -1) // If pixel is labeled as an area of brightness
	{
            int key = setTable.find(segment[i][j].first); // find root
	    areas[key].theta.push_back(angle); 	// store angle, rho, and votes  
	    areas[key].rho.push_back(j); 
	    areas[key].intensities.push_back(segment[i][j].second); 
	} 
    }//for j
    angle += (0.00872665); // increment angle 
  } //for i

// calculate weighted average for each area to get the average intensity line 
  for(map<int, Area>::iterator it=areas.begin(); it!=areas.end(); it++)
  {
	int sum =0; int denom=0; 
	for(int i=0; i<((it->second).intensities).size(); i++)
	{
	     sum += i *  (it->second).intensities[i]; 
	     denom += (it->second).intensities[i]; 
	}
	int mean = sum/denom; 
        pair<double, int> aPair = make_pair((it->second).theta[mean], ((it->second).rho[mean])*2) ; 
	lines.push_back(aPair); 
  } // for it

} // end getAreas

bool nearEdge(Image* image, int i, int j) // for bonus question
{
   if(image->GetPixel(i,j) == 255) return true; 
   if(i > 1)
   {	if(image->GetPixel(i-1, j) == 255) return true;  }
   if(i < image->num_rows()-1) 
   {   if(image->GetPixel(i+1, j) == 255) return true; }  
   if(j > 1)
   { if(image->GetPixel(i, j-1) == 255) return true; }
   if(j< image->num_columns()-1)
   { if(image->GetPixel(i,j+1) == 255) return true; } 
   return false;
}

