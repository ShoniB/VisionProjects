/* Title: DisjSets.h 
   Shondell Baijoo
   Purpose: Class for implementing a union-find algorithm. 
  Date: 9/20/2017
*/ 

#ifndef DISJSETS_H
#define DISJSETS_H

#include<vector>
using namespace std; 

class DisjSets 
{
  public: 
	DisjSets(){} // default constr 
	DisjSets(int numElements); 
	/* Finds the root of x in the disjoint set
	Precondition: DisjSets is not empty 
	Postcondition: Returns the root of the tree element x is in */	
	int find(int x); 
	/* Unions two sets into one set.
	Precondition:  DisjSets is not empty, the roots of the set are sent into the function
	Postcondition: Those roots are merged, making both sets one set */
	void unionSets(int root1, int root2);
	/* Adds an element to DisjSet. That element becomes a root of its own set */
	void addElement(); 
	/* Returns the number of disjoint sets (number of roots) */ 
	int getDisjoint(); 
	/* Displays vector s: the roots of all elements */
	void displaySet(); 
	/* Returns a vector containing the int value of the roots in DisjSet */
	vector<int> getRoots(); 
  private: 
	vector<int> s; 
};

#endif
