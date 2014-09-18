#ifndef _PRINT_STABLE_H_
#define _PRINT_STABLE_H_
#include "../include/TriMesh.h"
#include <vector>
#include <set>
#include <map>
using std::vector;
using std::set;
using std::map;
using namespace trimesh;

class stability
{
public:
	stability(TriMesh* mesh);
	float queryVolumes();
	float queryArea();
	vec	  queryCenterOfMass();
	bool  queryStability();

private:
	//Basic data 
	float				 volumes;
	float				 area;
	//center of mass
	vec					 com; 
	//stand plane
	std::pair<point,vec> splane;
	TriMesh*	         modelMesh;
	void  getInsection(vector<point>& pointSet);
	void  getBaseData();
};
#endif