#ifndef _PRINT_STABLE_H_
#define _PRINT_STABLE_H_
#include "../include/TriMesh.h"
#include <vector>
using std::vector;
using namespace trimesh;

class stability
{
public:
	stability();
	void  getBaseData(TriMesh* mesh);
	float queryVolumes();
	float queryArea();
	vec	  queryCenterOfMass();

private:
	//Basic data 
	float volumes;
	float area;
	//center of mass
	vec	   com; 
};
#endif