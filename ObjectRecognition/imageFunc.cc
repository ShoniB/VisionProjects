/* Title: imageFunc.cc
   Shondell Baijoo
   Purpose: Implementations of all functions declared in imageFunc.h
  Date: 9/25/2017
*/ 

#include "imageFunc.h"
#include "imageMod.h"
#include "DisjSets.h" 
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <string>

using namespace std;

namespace ComputerVisionProjects {

void Image::RemoveObjects(int threshold)
{
  for(std::map<int, Object>::iterator it= objects.begin(); it!=objects.end(); ++it) // iterate through object map
  {
     if((it->second).area < threshold)
     {
	for(int i=0; i<num_rows(); i++) // change label in pixel_label matrix to -1 (labeled as background) 
	{
	  for(int j=0; j<num_columns(); j++)
 	  {
	     if(GetPixelLabel(i,j) == it->first)
		SetPixelLabel(i,j, -1); 
	  }
	}// end for i
	objects.erase(it); // remove object from objects map
     }
    }
} // end RemoveObjects

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


void Label(Image *input_image) 
{
  if(input_image == nullptr) abort(); 

  int label=0; // start label counter at 0 
  int white = 255; 
  DisjSets setTable; // equivalence table using union-find algorithm
  setTable.addElement(); // add label 0 to table

  if(input_image->GetPixel(0,0) == white) // Look at first pixel
  { 
	input_image->SetPixelLabel(0,0, label); // label first pixel 0 if it is an object
  }
  for(int j=1; j<input_image->num_columns(); j++) // Check first row, only look at left neighbor
  {
    if(input_image->GetPixel(0,j) == white) 
    {
	if(input_image->GetPixelLabel(0,j-1) != -1) // If neighbor is labeled 
	{
	   input_image->SetPixelLabel(0,j,input_image->GetPixelLabel(0, j-1));  // set label to neighbor's label
	}
	else
        {
	   input_image->SetPixelLabel(0,j, label++); // Else give new label
	   setTable.addElement(); // add a new label to table 	
	}
    }
  } // end first row
  for(int i=1; i<input_image->num_rows(); i++) // Check first column, only look at top neighbor
  {
    if(input_image->GetPixel(i,0) == white) // if object
    {
	if(input_image->GetPixelLabel(i-1, 0) != -1) // if top neighbor is labeled
	{
	   input_image->SetPixelLabel(i, 0, input_image->GetPixelLabel(i-1, 0)); // set label to neighbor's label
	}
	else 
	{
	   input_image->SetPixelLabel(i,0,label++); //Give new label 
	   setTable.addElement(); // add label to table
	} 
    }  
  } // end first column

  //rest of image - we are checking Assymetrical Above neighbors (top, top-left, and left)
  for(int i=1; i<input_image->num_rows(); i++)
  {
    for(int j=1; j<input_image->num_columns(); j++)
    {
	if(input_image->GetPixel(i,j) == white)  
	{
	  int min = 99999; // initialize minimum for comparison to neighbors 
	  if(input_image->GetPixelLabel(i, j-1) != -1) // check if LEFT is labeled 	
	    min = input_image->GetPixelLabel(i, j-1); // set min to left label
	  if(input_image->GetPixelLabel(i-1,j) != -1) // check TOP
	  {
	    if(min>input_image->GetPixelLabel(i-1,j)) // set min to smallest label
		min = input_image->GetPixelLabel(i-1,j);  
	    if(input_image->GetPixelLabel(i, j-1) != -1 && input_image->GetPixelLabel(i, j-1) != input_image->GetPixelLabel(i-1,j))
	    // If top and left are labeled, and are not the same label 
	    {
		int x = setTable.find(input_image->GetPixelLabel(i,j-1)); // find root of left label
		int y = setTable.find(input_image->GetPixelLabel(i-1,j)); // find root of top label
		if(x!=y) // If the roots are not the same
	          setTable.unionSets(x, y); // Connect the roots
	    }
	  } //done checking top 
	  if(input_image->GetPixelLabel(i-1,j-1) != -1) // check TOP-LEFT
	  {
	    if(min>input_image->GetPixelLabel(i-1,j-1)) // set min to smallest label
		min= input_image->GetPixelLabel(i-1, j-1); 
	    if(input_image->GetPixelLabel(i,j-1)!= -1 && input_image->GetPixelLabel(i,j-1) != input_image->GetPixelLabel(i-1,j-1))
	    { // if left is a label and top left and left labels are different
		int x = setTable.find(input_image->GetPixelLabel(i,j-1)); // get roots of left and top left labels
		int y = setTable.find(input_image->GetPixelLabel(i-1,j-1)); 
		if(x!=y) // If the roots are not the same
	          setTable.unionSets(x, y); // Connect the roots 
	    }
	    if(input_image->GetPixelLabel(i-1,j) != -1 && input_image->GetPixelLabel(i-1,j) != input_image->GetPixelLabel(i-1,j-1))
	    { // If top is a label and top left and top labels are different 
		int x = setTable.find(input_image->GetPixelLabel(i-1,j)); // get roots of labels
		int y = setTable.find(input_image->GetPixelLabel(i-1,j-1)); 
		if(x!=y) // If the roots are not the same
	       	 setTable.unionSets(x, y); // Connect the roots 
	    }
	  }// done checking topleft
	  if(min == 99999){ // If none of the neighbors were labeled
	 	input_image->SetPixelLabel(i, j, label++); // add a new label
		setTable.addElement(); // add new label to table
	  }
	  else input_image->SetPixelLabel(i,j,min); // else set smallest label as label
	} // end if pixel==white
    }	// end for j
  } // end for i
  
// Second pass to set all connected labels to one main label  
  for(int i=0; i<input_image->num_rows(); i++)
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	if(input_image->GetPixelLabel(i,j) != -1) // If pixel is labeled as an object
	   input_image->SetPixelLabel(i,j, setTable.find(input_image->GetPixelLabel(i,j))); // set label to root of its label
    }
  }
  vector<int> roots = setTable.getRoots(); // Get all of the roots into a vector 
  for(int i=0; i<roots.size(); i++ ) // initialize map of objects
  {
     input_image->SetObjects(roots[i]); // label used as key for map of objects
  }
} // end Label()

void Area(Image *input_image) 
{
  if(input_image==nullptr) abort(); 

    for(int i=0; i<input_image->num_rows(); i++) // iterate through image
    {
      for(int j=0; j<input_image->num_columns(); j++)
      {
	 int key = input_image->GetPixelLabel(i,j);
	 if(key != -1)
	    input_image->IncrementArea(key); // +1 to area of object
      }
    } // end i
    input_image->RemoveObjects(50); // remove all objects under 100 pixels
} // end Area()

void CreateLabels(Image *input_image)
{
  std::map<int, Object> temp; // temp map to hold current keys found
  for(int i=0; i<input_image->num_rows(); i++)
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	int key = input_image->GetPixel(i,j); 
	if(key != 0) // if pixel is not black
        {
	   input_image->SetPixelLabel(i,j,key); // give the pixel a label
	   if(temp.count(key) == 0) // if key does not exist
	   {
	      temp[key]; // create that label in the objects map
	      input_image->SetObjects(key); // set label in objects map
	   }
	}
    }
  } // end i 
} //  end createlabels

void ColorObjects(Image *input_image) 
{
   std::map<int, Object> temp = input_image->GetObjects();
   std::map<int, int> colors; // create a map to store label and new object color
   int objects = temp.size(); // Number of objects
   int color_division = 255 / objects; // divide greys between number of objects 
   for(std::map<int, Object>::iterator i=temp.begin(); i!=temp.end(); ++i) // iterate through objects
   {
	colors[i->first] = color_division; // initialize map - give each object a color 
	color_division+=(255/objects);
   }

  for(int i=0; i<input_image->num_rows(); i++) // Iterate through image
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	if(input_image->GetPixelLabel(i,j) != -1)  // If object
	{
	  input_image->SetPixel(i, j, colors[input_image->GetPixelLabel(i,j)]); // color object its given color 
	}
    }
  } 
} // end ColorObjects()


void CalculateCenter(Image *input_image)
{
  std::map<int, Object> temp = input_image->GetObjects(); 
  std::map<int, pair<int,int>> centerCount; // map to hold x and y sums for each object

  for(std::map<int, Object>::iterator i=temp.begin(); i!=temp.end(); i++) 
  {
    centerCount[i->first] = std::make_pair(0,0); // initialize x and y counters for each object, using object label as key 
  }
  for(int i=0; i<input_image->num_rows(); i++) // sum up x's and y's 
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	if(input_image->GetPixelLabel(i,j) != -1)
	{
	  centerCount[input_image->GetPixelLabel(i,j)].first+=i; 
	  centerCount[input_image->GetPixelLabel(i,j)].second+=j;  
	}
    }
  }  // end summation
  for(std::map<int, Object>::iterator i=temp.begin(); i!=temp.end(); i++) // iterate through objects and finish calculation 
  {
    int x = centerCount[i->first].first / (i->second).area; // Sum of X's / Area 
    centerCount[i->first].first = x; 
    int y = centerCount[i->first].second / (i->second).area; // Sum of Y's / Area
    centerCount[i->first].second = y;
    input_image->SetObjectCenter(i->first, x, y); // set in objects map
  }
} // end CalculateCenter


void CalcABC(Image *input_image)
{
  std::map <int, Object> temp = input_image->GetObjects(); 
  std::map <int, double> a;
  std::map <int, double> b; 
  std::map <int, double> c;  

  for(std::map<int,Object>::iterator it = temp.begin(); it!=temp.end(); it++) // initialize keys 
  {	
    a[it->first] = 0.0; 
    b[it->first] = 0.0; 
    c[it->first] = 0.0; 
  }
  
 // Calculate summations 
  for(int i=0; i<input_image->num_rows(); i++)
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	int key = input_image->GetPixelLabel(i,j); 
	if(key != -1)
	{
	  double xprime = i-temp[key].centerX; // x - xCenter
	  double yprime = j-temp[key].centerY; // y - yCenter
	  a[key] += (pow(xprime , 2)); 
	  b[key] += (xprime * yprime);
	  c[key] += (pow(yprime, 2)); 
	}
    }
  }// end i

  //Multiply b's by 2 and set a,b,c in class
  for(std::map<int, double>::iterator it=b.begin(); it!= b.end(); it++)
  {
 	b[it->first]*=2; 
  	input_image->SetObjectABC(it->first, a[it->first], b[it->first], c[it->first]); 
  }
}//end CalcABC()

void CalcTheta(Image *input_image)
{
  std::map<int, Object> temp = input_image->GetObjects(); 
  for(std::map<int, Object>::iterator it = temp.begin(); it!= temp.end(); it++) // iterate through objects
  {
    double a = (it->second).a; 
    double b = (it->second).b;
    double c = (it->second).c; 
    double theta = (atan2(b, a-c))/2.0 * (180.0/3.14159265); //Calculate theta as degrees
    input_image->SetObjectTheta(it->first, theta);  
  }
} // end CalcTheta()

void CalcE(Image *input_image)
{
  std::map<int, Object> temp = input_image->GetObjects();
  for(std::map<int, Object>::iterator it=temp.begin(); it!=temp.end(); it++)
  {
    double a = (it->second).a; 
    double b = (it->second).b; 
    double c = (it->second).c;
    double theta = (it->second).theta; 
    double thetaRadian = theta * (3.14159265/180.0); // convert theta to radians 
    double E = a* pow(sin(thetaRadian), 2) - b * sin(thetaRadian)  *cos(thetaRadian) + c * pow(cos(thetaRadian), 2); 
    double hypotenuse = sqrt(pow(b,2) + pow((a-c),2)); 
    double sin2 = -b/hypotenuse; 
    double cos2 = -(a-c)/hypotenuse; 
    double EMAX = 0.5*(a+c) - 0.5 * (a-c) * cos2 - 0.5 * b * sin2; 
    input_image->SetObjectE((it->first), E);
    input_image->SetObjectEMax((it->first), EMAX); 
    input_image->SetObjectRoundess((it->first), E/EMAX);  
  } 
} // end CalcE()

void DrawDot(Image *input_image, int x, int y, int color)
{
  if (input_image == nullptr) abort();
  input_image->SetPixel(x, y, color);
  if(x != 0) // make sure we don't go out of bounds
    input_image->SetPixel(x-1, y, color); // Set pixel left of (x,y) 
  if(x != input_image->num_columns())
    input_image->SetPixel(x+1, y, color); // right
  if(y!=0)
    input_image->SetPixel(x, y+1, color); // top
  if(y!=input_image->num_rows())
    input_image->SetPixel(x, y-1, color); //bottom
  if(x!=0 && y!=0)
    input_image->SetPixel(x-1,y+1, color); // top left
  if(x!=0 && y!=input_image->num_rows())
    input_image->SetPixel(x-1, y-1, color); //bottom left
  if(x!=input_image->num_columns() && y!=0)
    input_image->SetPixel(x+1, y+1, color); //top right
  if(x!=input_image->num_columns() && y!=input_image->num_rows())
    input_image->SetPixel(x+1, y-1, color); //bottom right
} // end DrawDot()

void Database(Image *input_image, string filename)
{
  ofstream database(filename.c_str()); // holds label, center of mass, inertia, theta, area and roundness for objects
  std::map<int, Object> temp = input_image->GetObjects(); 
  for(std::map<int, Object>::iterator it=temp.begin(); it!=temp.end(); it++)
  {
    database << it->first << " " << (it->second).centerX << " " << (it->second).centerY << " " ;
	database << (it->second).e << " " << (it->second).theta << " "<< (it->second).area <<" "<< (it->second).roundness << endl;  // write to database
  }
  database.close();
} // end Database() 

void DrawOrientation(Image *input_image)
{

  std::map<int, Object> temp = input_image->GetObjects(); 
  for(std::map<int, Object>::iterator it = temp.begin(); it!= temp.end(); it++)
  {
    double thetaRadian =  (it->second).theta * (3.14159265/180.0); // convert theta to radians
    int x = (it->second).centerX; 
    int y = (it->second).centerY; 
    int x2 = x + (35* (cos(thetaRadian))); // calculate another x point on line using theta (*25 to make line longer) 
    int y2 = y + (35* (sin(thetaRadian))); // calculate y point 
    DrawDot(input_image, x, y, 0); // draw dot at center of mass
    DrawLine(x, y, x2, y2, 0, input_image); // draw orientation line
  }
} // end DrawOrientation()

void Recognize(Image *input_image, ifstream& db)
{
  std::map<int, Object> temp = input_image->GetObjects(); 
  vector<string> area_str; // string vectors to get data from text file
  vector<string> round_str; 
  string data; 
  while(db >> data) // while data has strings
  {
     for(int i=0; i<5; i++) // there are four items listed before area - centerx, centery, inertia, and theta
	db >> data;  
     area_str.push_back(data); // add word to area
     db >> data; // take roundness
     round_str.push_back(data); // add word to round
  }
  vector <int> area; vector<double> round; 
  for(int i=0; i<area_str.size(); i++) // convert strings to numbers
  {
    int area_convert = stoi(area_str[i]); 
    area.push_back(area_convert);
    double round_convert = stod(round_str[i]);
    round.push_back(round_convert); 
  }
  vector<int> recognized; // save labels of recognized objects 
  for(std::map<int, Object>::iterator it = temp.begin(); it!=temp.end(); it++) // go through every object in image
  {
    vector<int> options; // save the objects with similar roundness values
    for(int i=0; i<round.size(); i++) // compare roundness first
    { // We want roundness value to at least be within 2 decimal places
   	if((it->second).roundness - round[i] < 0.05 && (it->second).roundness - round[i] > -0.05)
	   options.push_back(i); // save that value
    }
    for(int i=0; i<options.size(); i++) // for objects in database that had similar roundess, check against area
    { // We want the area to be within 200 pixels
       if((it->second).area - area[options[i]] < 300 && (it->second).area - area[options[i]] > -300)
	 recognized.push_back(it->first); // if it is within 200 pixels, then it is a match! 
    }
  } // end for it
  DrawRecognized(input_image, recognized); // draw orientation line of recognized objects
}

void DrawRecognized(Image* input_image, vector<int> recognized_objects)
{
  for(int i=0; i<input_image->num_rows(); i++) // color entire image black 
  {
    for(int j=0; j<input_image->num_columns(); j++)
    {
	if(std::find(recognized_objects.begin(), recognized_objects.end(), input_image->GetPixel(i,j)) == recognized_objects.end())
	   input_image->SetPixel(i,j,0);
    }
  } // end i
  std::map<int, Object> temp = input_image->GetObjects(); 
  for(int i=0; i<recognized_objects.size(); i++)
  {
    int key = recognized_objects[i]; // use key of recognized_object to identify the object in the objects map
    double thetaRadian =  temp[key].theta * (3.14159265/180.0); // convert theta to radians
    int x = temp[key].centerX; // get center points to calculate orientation line
    int y = temp[key].centerY; 
    int x2 = x + (35* (cos(thetaRadian))); // calculate a second point and multiply by 25 to make it long
    int y2 = y + (35* (sin(thetaRadian)));
    DrawDot(input_image, x, y, 0); // draw a dot at center of mass
    DrawLine(x, y, x2, y2, 0, input_image); // draw orientation line
  }
}// end DrawRecognized() 

} // end ComputerVisionProjects
