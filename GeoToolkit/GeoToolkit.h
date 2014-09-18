#ifndef _GEOTOOLKIT_H_
#define _GEOTOOLKIT_H_
#include <vector>
#include "../include/Vec.h"
using std::vector;
using trimesh::point;
using trimesh::vec;

template <typename T>
inline bool is_zero(T a)
{
	return fabs(a) < 1e-6;
}

//type of a & b must be float or double
template <typename T>
inline bool is_equal(T a, T b)
{
	return is_zero(a-b);
}


class geoToolkit
{
public:
	//Find the ConvexHull of a point set in a plane
	//PointSet is the input point set£»
	//ch is the outpoint set of the Convexhull,clockwise;
	static void GrahamScan(vector<point>& PointSet,vector<point>& ch);

	static bool insidePolygon(const point& pt, const vector<point>& polygon);
};


#endif