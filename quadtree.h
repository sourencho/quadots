/* Header file for quadtree library */
#ifndef __QUADTREE_H
#define __QUADTREE_H

#include <vector>
#include "Point"  //include Point library made by Souren

/* Quadtree will consist of levels which will have a certain width and height and a number associated.
Each level will consist of a vector of Points. 
The quadtree library will also have pointer to its parent node and 4 children nodes. 
Each level can not have more than 4 nodes. */

#define MAX_LEVEL 4
#define MAX_POINTS 1
#define MAX

class quadtree {
public:
	quadtree(float x, float y, int level);  //constructor
  
  	void pushPoint(Point p);
  	vector<Point> getNeighbouringPoints(float x, float y);
  	vector<Point> getPointsAt(float x, float y);

private:
  	float x;
  	float y;
  	int level;
  	int maxlevel = MAX_LEVEL;
  
  	vector<Point> points;
	quadtree [] nodes;
};

