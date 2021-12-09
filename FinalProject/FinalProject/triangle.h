/*
#include "Geometry.h"

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
	vec3 ab = pb - pa;
	vec3 ac = pc - pa;
	vec3 normal = cross(ab, ac);
	
	float NRdir = dot(r.direction(), normal);
	if (NRdir < 0.001 && NRdir > -0.001) { return false; }

	float d = dot(normal, pa);
	float t = (dot(normal, r.origin()) + d) / NRdir;
	if (t < 0.001 || t > t_max) { return false; }

	vec3 p_intersect = r.origin() + t * r.direction();

	vec3 C; // vector perpendicular to triangle's plane 

	// edge 0
	vec3 edge0 = pb - pa;
	vec3 vp0 = p_intersect - pa;
	C = cross(edge0, vp0);
	if (dot(normal, C) < 0) return false; // P is on the right side 

	// edge 1
	vec3 edge1 = pc - pb;
	vec3 vp1 = p_intersect - pb;
	C = cross(edge1, vp1);
	if (dot(normal, C) < 0) return false; // P is on the right side 

	// edge 2
	vec3 edge2 = pa - pc;
	vec3 vp2 = p_intersect - pc;
	C = cross(edge2, vp2);
	if (dot(normal, C) < 0) return false; // P is on the right side 

	rec.p = p_intersect;
	rec.normal = normal;
	rec.t = t;
	return true;

}
*/