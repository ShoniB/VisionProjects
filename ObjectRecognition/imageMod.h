/* Title: Image.h 
   Modified by Shondell Baijoo
   Purpose: Class for representing a 2D gray-scale image,
     with support for reading/writing pgm images.
     To be used in Computer Vision class.
  Date: 9/20/2017
*/ 

#ifndef COMPUTER_VISION_IMAGEMOD_H_
#define COMPUTER_VISION_IMAGEMOD_H_

#include <cstdlib>
#include <string>
#include <vector> 
#include <map> 
#include <utility>

namespace ComputerVisionProjects {
 
// Class to store all of the needed data for an object in an Image
class Object 
{
  public: 
    Object() {area=0; a=0; b=0; c=0; centerX=0; centerY=0; theta=0; e=0;}
    ~Object(){}
//    int area(){return area;}
//  private: 
    int area;
    double a, b, c; // second moments used to calculate e
    int centerX, centerY; // center of mass points
    double theta; // angle of orientation
    double e; // minimum inertia
    double emax; // max inertia
    double roundness; // emin/emax
};

// Class for representing a gray-scale image.
// Sample usage:
//   Image one_image;
//   one_image.AllocateSpaceAndSetSize(100, 200);
//   one_image.SetNumberGrayLevels(255);
//   // Creates and image such that each pixel is 150.
//   for (int i = 0; i < 100; ++i)
//     for (int j = 0; j < 200; ++j)
//       one_image.SetPixel(i, j, 150);
//   WriteImage("output_file.pgm", an_image);
//   // See image_demo.cc for read/write image.
class Image {
 public:
  Image(): num_rows_{0}, num_columns_{0}, 
	   num_gray_levels_{0}, pixels_{nullptr}, pixel_label{nullptr} { }
  
  Image(const Image &an_image);
  Image& operator=(const Image &an_image) = delete;

  ~Image();

  // Sets the size of the image to the given
  // height (num_rows) and columns (num_columns).
  void AllocateSpaceAndSetSize(size_t num_rows, size_t num_columns);

  size_t num_rows() const { return num_rows_; }
  size_t num_columns() const { return num_columns_; }
  size_t num_gray_levels() const { return num_gray_levels_; }
  void SetNumberGrayLevels(size_t gray_levels) {
    num_gray_levels_ = gray_levels;
  }
 
  // Sets the pixel in the image at row i and column j
  // to a particular gray_level.
  void SetPixel(size_t i, size_t j, int gray_level) {
    if (i >= num_rows_ || j >= num_columns_) abort();
    pixels_[i][j] = gray_level;
  }

  int GetPixel(size_t i, size_t j) const {
    if (i >= num_rows_ || j >= num_columns_) abort();
    return pixels_[i][j];
  }
 
// This function gives a pixel a given label - this will be used for object distinction
  void SetPixelLabel(size_t i, size_t j, int label) 
  {
    if(i>=num_rows_ || j >= num_columns_) abort(); 
    pixel_label[i][j] = label; 
  }
// This function returns said label
  int GetPixelLabel(size_t i, size_t j) const 
  {
    if(i>=num_rows_ || j >= num_columns_) abort();
    return pixel_label[i][j]; 
  }
// Map to hold Objects in an image. The key is the label of the object
  std::map<int, Object> GetObjects() { return objects; }
// Gives a new object a label (key) 
  void SetObjects(int key) { objects[key]; }
// This function increments the area variable in the Object class by one
  void IncrementArea(int key) { objects[key].area++; }

/* This function removes all objects from the object map and pixel_label matrix in an image if the area
 	of the object is less than a certain threshold
  This verifies that noise in an image is not labeled as an objects
  The function is written in imageFunc.cc
  Parameter: threshold-  all objects with areas smaller than this int is relabeled as a non object 
  Precondition: image is labeled and the areas of the objects have already been computed 
  Postcondition: objects with area less than the threshold is taken out of the objects map
         and the label in the pixel_label matrix is set to -1   */
  void RemoveObjects(int threshold);

// These functions set values for objects in the object map
// Parameters: takes key (label) of object in object map and the value to set 
  void SetObjectCenter(int key, int x, int y) { objects[key].centerX = x; objects[key].centerY = y; }
  void SetObjectABC(int key, double a_p, double b_p, double c_p) { objects[key].a = a_p; objects[key].b = b_p; objects[key].c = c_p; } 
  void SetObjectTheta(int key, double theta_p) { objects[key].theta = theta_p; }
  void SetObjectE(int key, double e_p) { objects[key].e = e_p; }
  void SetObjectEMax(int key, double emax_p) {objects[key].emax = emax_p; }
  void SetObjectRoundess(int key, double round_p) { objects[key].roundness = round_p; }  
 private:
  void DeallocateSpace();
  size_t num_rows_; 
  size_t num_columns_; 
  size_t num_gray_levels_;  
  int **pixels_; 
  int **pixel_label; // matrix that holds every pixel's label
  std::map<int, Object> objects; // map storing Objects and object labels. Key is object label

};

// Reads a pgm image from file input_filename.
// an_image is the resulting image.
// Returns true if  everyhing is OK, false otherwise.
bool ReadImage(const std::string &input_filename, Image *an_image);

// Writes image an_iamge into the pgm file output_filename.
// Returns true if  everyhing is OK, false otherwise.
bool WriteImage(const std::string &output_filename, const Image &an_image);

//  Draws a line of given gray-level color from (x0,y0) to (x1,y1);
//  an_image is the output_image.
// IMPORTANT: (x0,y0) and (x1,y1) can lie outside the image 
//   boundaries, so SetPixel() should check the coordinates passed to it.
void DrawLine(int x0, int y0, int x1, int y1, int color,
	      Image *an_image);

}  // namespace ComputerVisionProjects

#endif  // COMPUTER_VISION_IMAGE_H_
