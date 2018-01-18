/* Title: imageFunc.h 
   Author: Shondell Baijoo
   Purpose: Defines all functions to be used in Projects 1-4 that were created entirely by me.
  Date: 9/26/2017
*/ 

#ifndef IMAGEFUNC_H_
#define IMAGEFUNC_H_

#include "imageMod.h"
#include <cstdio>
#include <iostream>
#include <fstream> 
#include <string>
#include <vector> 
#include <algorithm> 
#include <map> 
#include "DisjSets.h" 
#include <cmath> 

namespace ComputerVisionProjects {

/* Binarize() goes through every pixel in the image and checks it against the given parameter threshold. 
   If the pixel value is is below the threshold, it will color that pixel black. Otherwise, the pixel will be white.
   Precondition: Greyscale image sent to function with loaded pixel values
   Postcondition: Image is now a binary image (black and white)  */
  void Binarize(int threshold, Image *input_image); 

/* Label() goes through every pixel in the image and assigns it a label using the sequential labeling algorithm. It checks the top, top-left, and left neighbor and assigns it the minimum label of those three. We set the pixel to the minimum label as an easy way to keep track of whether or not the pixel has been labeled. An equivalence table is kept as a disjoint set to keep track of multiple labels per object. If two neighbors are different labels representing the same object, they are unioned in the disjoint set. Once every pixel has a label, the function makes a second pass through all of the pixels and assign the labeled pixel their root label in the equivalence table. Finally, the objects map in the Image class is initialized with the labels as keys. 
  Precondition: Image is a binary image 
  Postcondition: Objects map in image is filled with labels as keys. Pixel_label matrix is filled with -1 for background and one label per object */
  void Label(Image *input_image);
  
/* CreateLabels() goes through a greyscale image with colored objects and relabels those objects into an objects map in order to keep track of various values of those objects. 
  Precondition: Image is a greyscale image with objects in the image colored uniquely one color 
  Postcondition: Fills objects map in Image with labels of those objects and sets the label in pixel_lables matrix */  
  void CreateLabels(Image *input_image);

/* Area() iterates through every pixel in the image in order to sum up the pixels for each (labeled) object
   Precondition: Image is labeled and binary
   Postcondition: Area of objects will be calculated 
		and small area objects will be removed from pixel_label matrix and objects map */
  void Area(Image *input_image);

/* ColorObjects() takes a labeled image and colors every object a different shade of grey. It uses the number of objects to decide how to evenly distribute the shades of grey and creates a map to hold those colors for each object. Then it iterates through the entire image and colors each object according to the object's label
   Precondition: Image is a labeled, binary image 
   Postcondition: Every object is colored a different shade of grey */
  void ColorObjects(Image *input_image);

/* CalculateCenter() iterates through the entire image and sums up the x and y coordinates for each object in the image.
   Once the sums are calculated it divides them by the area in order to find the center of mass for each object.
   Precondition: Image is a labeled binary image
   Postcondition: Objects map in Image now have centerX and centerY variables computed */ 
  void CalculateCenter(Image *input_image); 

/* CalcABC() iterates through the image and calculates the second moments for the objects in the image. It sums up x' and y' and uses those values to get a, b, and c. When these values are computed it stores them in the object map. 
   Precondition: Image is a labeled, binary image 
   Postcondition: Objects map in Image now have a, b, and c variables computed. */
  void CalcABC(Image *input_image); 

/* CalcTheta() uses a,b, and c in order to calculate the angle of orientation for each object. Theta is saved in degrees. 
   Precondition: a, b, and c have been computed and set in the objects map in the Image class  
   Postcondtion: Theta variable in the object map is now computed and saved in degrees. */
  void CalcTheta(Image *input_image);

/* CalcE() uses a, b, c, and theta to get the minimum and maximum moment of inertia. It also uses those values to calculate the roundness of the object. 
   Precondition: a, b, c, and theta variables have been calculated and set in the objects map in Image.
   Postcondition: e, emax, and roundness are now calculated and set in the objects map */
  void CalcE(Image *input_image);

/* DrawDot() takes a coordinate and sets the pixel and its 8 neighbors to the parameter 'color'.
   Precondition: Image is a greyscale image
   Postcondition: The pixel at (x,y) and its 8 neighbors are now colored 'color' */ 
  void DrawDot(Image *input_image, int x, int y, int color);

/* Database() creates textfile 'filename.txt' and writes to it information of all the objects in the Image. 
   The format is: "<label>  <centerX> <centerY> <minInertia> <thetaDegrees> <area> <roundness>
   Precondition: The variables for all of the objects have been computed (area, center of mass, inertia, theta, roundness)
   Postcondition: "filename.txt" is created */  
  void Database(Image *input_image, string filename); 

/* DrawOrientation() draws the orientation line for all of the objects in the image. It calls DrawDot() to draw a dot where the center of mass is, and uses theta to calculate another point on the orientation line. It then calls DrawLine() to draw the line of orientation.
   Precondition: theta and center of mass for all objects in the image have been computed
   Postcondition: Returns an image that contains a dot and line extending from it to show the center of mass and orientation of each object */
  void DrawOrientation(Image *input_image); 

/* Recognize() takes a labeled image with fully calculated objects and textfile containing the areas and roundness of other objects.
   It compares the area and roundness of the objects in Image and compares them to the numbers in the textfile. The object values will not be exact matches, as the pictures of the objects will be different. This will yield slightly different pixel values. We determine it a close match if their roundess values are the same within 2 decimal places of each other and if the areas are within 200 pixels of each other. If they are a close match, it takes those keys as recognized objects and calls DrawRecognized() to draw the orientation lines of recognized objects. 
   Precondition: Image is labeled with area and roundness of objects calculated. 
		 ifstream is a database containing the format "<area> <roundess>"
   Postcondition: An image is created with the orientation lines drawn for recognized images */ 
  void Recognize(Image *input_image, ifstream& db); 

/* DrawRecognized() is called by Recognize() and takes an Image and vector of ints. The vector<int> contains the labels for each object that has been recognized. Using the label, it accesses the objects map in Image to draw a dot for the center of mass and the line of orientation. 
   Precondition: Recognize() was called and filled a vector containing labels for recognized objects
   Postcondition: creates an image containing the orientation line for each recognized image */
  void DrawRecognized(Image* input_image, vector<int> recognized_objects); 

} // end ComputerVisionProjects


#endif  // COMPUTER_VISION_IMAGEFUNC_H_
