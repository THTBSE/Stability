#include <iostream>
#include "include/TriMesh.h"
#include "stable/stable.h"
#include "GeoToolkit/GeoToolkit.h"
using namespace trimesh;

int main(int argc,char* argv[])
{
	
	TriMesh* mesh;
	mesh = mesh->read("Head_init.stl");
	stability isStable(mesh);
	bool stb = isStable.queryStability();
	float model_vol = isStable.queryVolumes();
	float model_area = isStable.queryArea();
	std::cout << "the volumes is : " << isStable.queryVolumes() << std::endl
		<< "the area is : " << isStable.queryArea() << std::endl;
	
	vec center_of_mass = isStable.queryCenterOfMass();
	std::cout << "the center of mass is :" << center_of_mass[0] << ", "
		<< center_of_mass[1] << ", " << center_of_mass[2];

	return 0;
}