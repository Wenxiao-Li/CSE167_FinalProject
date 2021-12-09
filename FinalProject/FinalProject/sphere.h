#include "Geometry.h"

class sphere : public Geometry {
	public:
		sphere() {};

		sphere(vec3 ctr, float r) {
			center = ctr;
			radius = r; 
		};

		bool hit(ray& r, float t_max, hit_record& rec) const;
		vec3 center;
		float radius;
};

bool sphere::hit(ray& r, float t_max, hit_record& rec) const {
	
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant = b * b - a * c;
	if (discriminant > 0) { 
		float temp = (-b - sqrt(discriminant)) / a;
		if (temp > 0.001 && temp < t_max) {
			rec.t = temp;
			rec.p = r.point_at_parameter(temp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	else {
		return false;
	}
}

class triangle : public Geometry {
public:
	triangle() {}
	triangle(vec3 a, vec3 b, vec3 c) {
		pa = a;
		pb = b;
		pc = c;
	}

	bool hit(ray& r, float t_max, hit_record& rec) const;
	vec3 pa;
	vec3 pb;
	vec3 pc;
};

bool triangle::hit(ray& r, float t_max, hit_record& rec) const {

	vec3 edge1, edge2, h, s, q;
	float a, f, u, v;
	edge1 = pb - pa;
	edge2 = pc - pa;
	h = cross(r.direction(), edge2);
	a = dot(edge1, h);
	if (a > -0.000001 && a < -0.000001) return false;    // This ray is parallel to this triangle.
	f = 1.0 / a;
	s = r.origin() - pa;
	u = f * dot(s,h);
	if (u < 0.0 || u > 1.0) return false;
	q = cross(s, edge1);
	v = f * dot(r.direction(), q);
	if (v < 0.0 || u + v > 1.0) return false;
	// At this stage we can compute t to find out where the intersection point is on the line.
	float t = f * dot(edge2, q);
	if (t > 0.001) // ray intersection
	{
		rec.p = r.origin() + r.direction() * t;
		rec.t = t;
		rec.normal = h;
		return true;
	}
	else // This means that there is a line intersection but not a ray intersection.
		return false;
}
