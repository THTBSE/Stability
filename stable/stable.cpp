#include "stable.h"

stability::stability():volumes(0.0),area(0.0)
{

}

void stability::getBaseData(TriMesh* mesh)
{
	if (!mesh || mesh->vertices.empty() || mesh->faces.empty())
	{
		printf("error mesh ");
		return;
	}

	vector<vec>& v = mesh->vertices;
	vector<TriMesh::Face>& f = mesh->faces;
	for (size_t i=0; i<f.size(); i++)
	{
		vec &vi = v[f[i][0]];
		vec &vj = v[f[i][1]];
		vec &vk = v[f[i][2]];

		vec nor = (vj - vi) % (vk - vi);
		volumes += (nor)^(vi + vj + vk);

		vec g = vi*vj + vj*vk + vk*vi;
		com += (nor * g);

		area += len(mesh->trinorm(i));
	}

	volumes /= 18.0;
	float coeff = 1 / (12 * volumes);
	com = coeff * com;
}

float stability::queryVolumes()
{
	return volumes;
}

float stability::queryArea()
{
	return area;
}

vec stability::queryCenterOfMass()
{
	return com;
}