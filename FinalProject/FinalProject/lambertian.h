#include "material.h"

class lambertian : public material {
public:
	vec3 atten;

	lambertian(vec3 a) {
		atten = a;
	}

	bool scatter(ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = atten;

		return true;
	}
};