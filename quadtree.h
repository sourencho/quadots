/* Header file for quadtree library */
#ifndef __QUADTREE_H
#define __QUADTREE_H

#include <vector>
#include "Point.h"  //include Point library made by Souren

/* Quadtree will consist of levels which will have a certain width and height and a number associated.
Each level will consist of a vector of Points. 
The quadtree library will also have pointer to its parent node and 4 children nodes. 
Each level can not have more than 4 nodes. */

#define MAX_LEVELS 10
#define MAX_POINTS 1
#define MAX_NODES 4
#define RADIUS 70

//std::vector<Point> neighboursList; 

class quadtree {
public:
	quadtree(double x, double y, double width, double height, int level);  //constructor
	~quadtree();	//destructor.. incomplete 

  	double x;
  	double y;
	double width;
	double height;
  	int level;

  	void pushPoint(Point p);
	void clearQuadtree();	
	int traverseTree(Point p);
	quadtree traverseTree(quadtree* q, int level);
	void getNearestNeighbours(quadtree root, double rad, Point p);
	void traverseTree();

private:
	bool split;
	quadtree* nodes[4];
  	std::vector<Point> points;

	int getIndex(Point p);
	int splitIntoQuads();
	int findPoint(quadtree* q, Point p);
	double getDistance(Point p1);
	std::vector<Point> getPointsAtLevel(int level);
	bool isLeaf();
	std::vector<quadtree> getChildren();
};

#endif
