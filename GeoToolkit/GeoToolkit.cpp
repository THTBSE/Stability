#include "GeoToolkit.h"
#include <algorithm>
#include <cmath>

class point_comp
{
public:
	bool operator () (const point& a, const point&b)
	{
		return (a[0] < b[0] || is_equal<float>(a[0],b[0]) && a[1] < b[1]);
	}
};

class polar_angle_comp
{
public:
	point center;
	polar_angle_comp(const point& p):center(p){}
	bool operator () (const point& a, const point& b) const
	{
		vec xc(0,1,0);
		vec v1 = a - center;
		vec v2 = b - center;
		float a1 = trimesh::angle(v1,xc);
		float a2 = trimesh::angle(v2,xc);
		return (a1+1e-6<a2 || is_equal<float>(a1,a2) && len(v1)<len(v2));
	}
};

static inline float multiply(const vec& a,const vec&b)
{
	return (a[0]*b[1] - a[1]*b[0]);
}

void geoToolkit::GrahamScan(vector<point>& PointSet,vector<point>& ch)
{
	if (PointSet.empty())
		return;

	ch.clear();
	int base_index = min_element(PointSet.begin(),PointSet.end(),point_comp()) - PointSet.begin();
	point base_point = PointSet[base_index];
	std::swap(PointSet[0],PointSet[base_index]);
	std::sort(PointSet.begin()+1,PointSet.end(),polar_angle_comp(base_point));

	if (PointSet.size() < 4)
	{
		ch.assign(PointSet.begin(),PointSet.end());
		return;
	}
	
	ch.assign(PointSet.begin(),PointSet.begin()+3);
	for (size_t i=3; i<PointSet.size(); i++)
	{
		int j=1;
		int chsize = ch.size();
		while (true)
		{
			float t = multiply(PointSet[i]-ch[chsize-j],ch[chsize-j]-ch[chsize-(j+1)]);
			if (t > 0 && !is_zero(t))
				break;
			ch.pop_back();
			if (ch.size() < 3)
				break;
			j++;
		}
		ch.push_back(PointSet[i]);
	}
	return;
}

bool geoToolkit::insidePolygon(const point& pt, const vector<point>& polygon)
{
	if (polygon.size() < 3)
		return false;

	bool inside = false;
	for (size_t i=0,j=polygon.size()-1; i < polygon.size(); j=i,i++)
	{
		vec U0(polygon[i]),U1(polygon[j]);

		if (pt[1] < U1[1])
		{
			if (U0[1] <= pt[1])
				if ((pt[1] - U0[1]) * (U1[0] - U0[0]) > (pt[0] - U0[0]) * (U1[1] - U0[1]))
					inside = !inside;
		}
		else if (pt[1] < U0[1])
		{
			if ((pt[1] - U0[1]) * (U1[0] - U0[0]) < (pt[0] - U0[0]) * (U1[1] - U0[1]))
				inside = !inside;
		}
	}
	return inside;
}

