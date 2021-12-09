#include "ray.h"

struct hit_record;

class material {
	public:
		virtual bool scatter(ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

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

class metal : public material {
	public:
		vec3 atten;
		float fuz;

		metal(vec3& a, float f) {
			atten = a;
			if (f < 1) { fuz = f; }
			else { fuz = 1; }
		}
		
		bool scatter(ray& r_in, hit_record& rec, vec3& attenuation, ray& scattered) const {
			vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);

			scattered = ray(rec.p, reflected + fuz * random_in_unit_sphere());
			attenuation = atten;

			return dot(scattered.direction(), rec.normal) > 0;
		}
};

class dielectric : public material {
	
	public:
		dielectric(double index_of_refraction) : ir(index_of_refraction) {}

		bool scatter(ray& r_in, hit_record& rec, color& attenuation, ray& scattered) const {
			attenuation = color(1.0, 1.0, 1.0);
			double refraction_ratio = (dot(r_in.direction(), rec.normal) < 0) ? (1.0 / ir) : ir;

			vec3 unit_direction = unit_vector(r_in.direction());
			double cos_theta = fmin(dot(-unit_direction, rec.normal), 1.0);
			double sin_theta = sqrt(1.0 - cos_theta * cos_theta);

			bool cannot_refract = refraction_ratio * sin_theta > 1.0;
			vec3 direction;

			if (cannot_refract || reflectance(cos_theta, refraction_ratio) > random_double(0,1))
				direction = reflect(unit_direction, rec.normal);
			else
				direction = refract(unit_direction, rec.normal, refraction_ratio);

			scattered = ray(rec.p, direction);
			return true;
		}

	public:
		double ir; // Index of Refraction

	private:
		static double reflectance(double cosine, double ref_idx) {
			// Use Schlick's approximation for reflectance.
			auto r0 = (1 - ref_idx) / (1 + ref_idx);
			r0 = r0 * r0;
			return r0 + (1 - r0) * pow((1 - cosine), 5);
		}
};