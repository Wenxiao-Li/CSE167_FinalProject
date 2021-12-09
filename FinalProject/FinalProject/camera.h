#include "ray.h"
# define M_PI 3.14159265358979323846  /* pi */

class camera {
	public:

		camera() {
			lower_left = vec3(-2.0, -1.0, -1.0);
			horizontal = vec3(4.0, 0.0, 0.0);
			vertical = vec3(0.0, 2.0, 0.0);
			origin = vec3(0.0, 0.0, 0.0);
		}

		camera(vec3 lookfrom, vec3 lookat, vec3 vup, float vfov, float aspect) {
			vec3 u, v, w;
			float theta = vfov * M_PI / 180;
			float half_height = tan(theta / 2);
			float half_width = aspect * half_height;
			origin = lookfrom;
			w = unit_vector(lookfrom - lookat);
			u = unit_vector(cross(vup, w));
			v = cross(w, u);
			
			horizontal = 2 * half_width * u;
			vertical = 2 * half_height * v;
			lower_left = origin - half_width * u - half_height * v - w;
			//lower_left = vec3(-half_width, -half_height, -1.0);
			//horizontal = vec3(2.0 * half_width, 0.0, 0.0);
			//vertical = vec3(0.0, 2.0 * half_height, 0.0);
			
		}

		ray get_ray(float u, float v) {
			return ray(origin, lower_left + u * horizontal + v * vertical - origin);
		}

		vec3 origin;
		vec3 lower_left;
		vec3 horizontal;
		vec3 vertical;

};