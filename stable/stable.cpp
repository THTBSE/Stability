#include "stable.h"
#include "../GeoToolkit/GeoToolkit.h"

stability::stability(TriMesh* mesh):volumes(0.0),area(0.0),modelMesh(mesh)
{
	splane.second = vec(0,0,1);
}

void stability::getBaseData()
{
	if (!modelMesh || modelMesh->vertices.empty() || modelMesh->faces.empty())
	{
		printf("error mesh ");
		return;
	}

	const vector<vec>& v = modelMesh->vertices;
	const vector<TriMesh::Face>& f = modelMesh->faces;
	for (size_t i=0; i<f.size(); i++)
	{
		const vec &vi = v[f[i][0]];
		const vec &vj = v[f[i][1]];
		const vec &vk = v[f[i][2]];

		vec nor = (vj - vi) % (vk - vi);
		volumes += (nor)^(vi + vj + vk);

		vec g = vi*vj + vj*vk + vk*vi;
		com += (nor * g);

		area += len(modelMesh->trinorm(i));
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

class zmin_comp
{
public:
	bool operator() (point& a, point& b)
	{
		return a[2] < b[2];
	}
};

template <typename T>
inline bool is_close(T a, T b)
{
	return (fabs(a-b) < 0.5);
}

void stability::getInsection(vector<point>& pointSet)
{
	vector<point>& v = modelMesh->vertices;
	float zmin = (*min_element(v.begin(),v.end(),zmin_comp()))[2];

	for (size_t i=0; i<v.size(); i++)
	{
		if (is_close(v[i][2],zmin))
		{
			pointSet.push_back(vec(v[i][0],v[i][1],0));
		}
	}
}

bool stability::queryStability()
{
	vector<point> pointSet,ch;
	getBaseData();
	getInsection(pointSet);
	geoToolkit::GrahamScan(pointSet,ch);
	point Gproj(vec(com[0],com[1],0));
	return geoToolkit::insidePolygon(Gproj,ch);
}