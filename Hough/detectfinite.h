/* Title: detectfinite.h 
   Author: Shondell Baijoo
   Purpose: Function declarations of detecting finite lines using hough voting array 
  Date: 10/31/2017
*/ 

#ifndef DETECTFINITE_H
#define DETECTFINITE_H
#include <fstream> 
#include <vector>
#include "image.h"
using namespace std; 
using namespace ComputerVisionProjects; 

class Area // Class used to store values of areas of brightness in order to find the mean line 
{
   public: 
	vector<int> rho;
	vector<double> theta;
	vector<int> intensities;
};

/* This function detects lines and plots them on an_image. Uses votes to plot the lines based on thresholds. 
   Parameters: greyscale image is copied and sent as bin_image: This is for detecting finite lines. 
   votes: a text file containing intensity values for the votes of rho, theta lines
   Threshold: for thresholding votes 
   Output: a greyscale image with detected lines colored in white. */
void DetectLines(Image *an_image, Image *bin_image, ifstream &votes, int threshold); 

/* Segments the different areas of brightness in order to get a single line for each cluster of votes. 
   Also calculates weighted average of each area to get the average intensity point.
   Parameters: segment: a vector of vectors to represent the votes txt file. This contains a pair of (label, intensity) post thresholding.
   lines: vector to hold each (theta,rho) line. After GetAreas() this vector will hold the average intensity line for each area of brightness. 
   Output: lines is now filled with detected lines  */
void GetAreas(vector<vector<pair<int,int>>>& segment, vector<pair<double, int>>& lines);

/* This function finds if there are edges one pixel away from the point on a detected line. If so, it counts towards the detected line 
   Called within DetectLines() 
   Parameters: image: a binary edge detected image. 
   i,j: point of the detected line 
   Output: True: If area around the point is an edge
   False: if area around the point is not an edge 
*/ 
bool nearEdge(Image* image, int i, int j); 


#endif
