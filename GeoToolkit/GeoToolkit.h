#ifndef _GEOTOOLKIT_H_
#define _GEOTOOLKIT_H_
#include <vector>
#include "../include/Vec.h"
using std::vector;
using trimesh::point;
using trimesh::vec;

class geoToolkit
{
public:
	//Find the ConvexHull of a point set in a plane
	//PointSet is the input point set£»
	//ch is the outpoint set of the Convexhull,clockwise;
	static void GrahamScan(vector<point>& PointSet,vector<point>& ch);
};


#endif