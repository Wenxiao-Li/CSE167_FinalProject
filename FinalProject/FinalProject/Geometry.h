#include "ray.h"

class material;

struct hit_record {
	float t = 0; // hit distance
	vec3 p;		 // intersection
	vec3 normal;
};

class Geometry {
	public:
		virtual bool hit(ray& r, float t_max, hit_record& rec) const = 0;
};