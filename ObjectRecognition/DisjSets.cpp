/* Title: DisjSets.cpp 
   Shondell Baijoo
   Purpose: Class for implementing a union-find algorithm. 
  Date: 9/20/2017
*/ 


#include "DisjSets.h" 
#include <iostream>
#include <algorithm> 

DisjSets::DisjSets(int numElements)
{
    for(int i=0; i<numElements; i++)
	s.push_back(-1); 
}

void DisjSets::unionSets(int root1, int root2)
{
   if(s[root2] < s[root1]) 
	s[root1] = root2; // make the smaller root the root of both
   else
   {
	if(s[root1] ==  s[root2])
	    --s[root1]; // decrement root of 1
	s[root2] = root1; // make the smaller root the root  of both
   }
}

int DisjSets::find(int x) 
{
    if(s[x] < 0)
	return x; 
    else
	return find(s[x]); // recurse until root is found
}

// Returns the amount of disjoint sets
int DisjSets::getDisjoint() 
{
    int count = 0; 
    for(int i=0; i<s.size(); i++){
	if(s[i] < 0)
	    count++; 
    }
    return count; 
}

// Displays vector s 
void DisjSets::displaySet()
{
    cout <<endl; 
    for(int i=0; i<s.size(); i++) 
	cout << s[i] <<" ";
    cout <<endl;   
}

void DisjSets::addElement()
{
   s.push_back(-1); 
}

vector<int> DisjSets::getRoots()
{
    vector<int> roots; 
    if(s.size() > 0)
       roots.push_back(DisjSets::find(0)); //push_back first root
    for(int i=1; i<s.size(); i++)
    {
	int curr_root = DisjSets::find(i); //find root
	if( std::find(roots.begin(), roots.end(), curr_root) == roots.end())  // if the root of current variable is not in roots vector
	   roots.push_back(curr_root); // add to vector 
    }
    return roots; 
}

