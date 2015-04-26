#include <iostream>
#include <cstdio>
#include "quadtree.h"
#include "Point.h"

quadtree::quadtree(double x, double y, double width, double height, int level) {
	if (this->level == MAX_LEVELS) {
    		std::cout<<"Error: Can not split quadtree further.";
    		return;
  	}
	this->x = x;
	this->y = y;
	this->width = width;
	this->height = height;
	this->level = level;
}

void quadtree::pushPoint(Point p) {
	if (split == true) {		//quadtree has children
		int index = getIndex(p);	//get appropriate location for Point

		if (index != -1) {
			nodes[index]->pushPoint(p);
			return;
		}
	}

	points.push_back(p);	//no children, push to parent

	if (points.size() > MAX_POINTS && level < MAX_LEVELS) {		//if no. of points in parent exceed MAX_POINTS (=1)
		if (split == false)		//no children, so split.
			splitIntoQuads();

		int k = 0;
		while (k < points.size()) {
			Point temp = points.back();
			int index = getIndex(temp);
			if (index != -1) {
				points.pop_back();
				nodes[index]->pushPoint(temp);
			}
			else
				k++;
		}
	}
}

int quadtree::getIndex(Point p) {
	int index = -1;
	bool topquad, bottomquad;

	double verMidpoint = this->x + 0.5*this->width;
	double horMidpoint = this->y + 0.5*this->height;

	if (p.y < horMidpoint)
		topquad = true;
	else if (p.y > horMidpoint)
		bottomquad = true;

	if (topquad) {
		if (p.x < verMidpoint)
			index = 0;
		else if (p.x > verMidpoint)
			index = 1;
	}
	else if (bottomquad) {
		if (p.x > verMidpoint)
			index = 2;
		else if (p.x < verMidpoint)
			index = 3;
	}
	return index; 
}

void quadtree::splitIntoQuads() {
	int newWidth = this->width/2;
	int newHeight = this->height/2;
	int newLevel = this->level + 1;

	nodes[0] = new quadtree(x, this->y, newWidth, newHeight, newLevel);
	nodes[1] = new quadtree(this->x + newWidth, this->y, newWidth, newHeight, newLevel);
	nodes[2] = new quadtree(this->x + newWidth, this->y + newHeight, newWidth, newHeight, newLevel);
	nodes[3] = new quadtree(this->x, this->y + newHeight, newWidth, newHeight, newLevel);

	this->split = true;
}

void quadtree::clearQuadtree() {
	points.erase(points.end() - 1);		//start erasing from the end

	for (int i = 0; i < MAX_NODES; i++) {
		if (split == true) {
			nodes[i]->clearQuadtree();
			nodes[i] = NULL;
		}
	}
}

