#include "FinalProject.h"
#include "vec3.h"
#include "ray.h"
#include <iostream>
#include <fstream>
#include <math.h>
#include "sphere.h"
#include <vector>
#include "camera.h"
#include "material.h"
#include "triangle.h"

using namespace std;

/*
float hit_sphere(vec3& center, float radius, ray& r) {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = 2.0 * dot(oc, r.direction());
	float c = dot(oc, oc) - radius * radius;

	float discriminant =  b * b - 4 * a * c;
	if (discriminant < 0) { return -1.0; }
	else {
		return (-b - sqrt(discriminant)) / (a * 2.0);
	}
}
*/

vec3 calColor(ray& r, vector<Geometry*>& world, vector<material*>& materials, int depth) {
	hit_record curRecord;
	hit_record rec;
	material* cur_mat;
	float closest = 100000.0;
	bool hasHit = false;
	for (int i = 0; i < world.size(); i++) {
		auto curGeo = world[i];
		if (curGeo->hit(r, closest, rec)) {
			hasHit = true;
			closest = rec.t;
			curRecord = rec;
			cur_mat = materials[i];
		}
	}
	
	float t = 0;
	if (hasHit) {
		vec3 attenuation;
		ray scattered;
		if (depth < 5 && cur_mat->scatter(r, curRecord, attenuation, scattered)) {
			return attenuation * calColor(scattered, world, materials, depth+1);
		}
		else {
			return vec3(0.0, 0.0, 0.0);
		}
	}
	else {
		vec3 unit_dir = unit_vector(r.direction());
		t = 0.5 * (unit_dir.y() + 1.0);
	}
	return (1.0-t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main() {
	ofstream outFile;
	outFile.open("out_camera_megaRandom.ppm");

	int nx = 900;
	int ny = 600;
	int ns = 25;

	outFile << "P3\n" << nx << " " << ny << "\n255\n";

	camera cam(vec3(13, 2, 3), vec3(0, 0, 0), vec3(0,1,0), 20, float(nx) / float(ny));

	//camera cam;
	vector<Geometry*> world;
	vector<material*> materials;
	/*
	world.push_back(new sphere( vec3(0,0,-1), 0.5));
	materials.push_back(new lambertian(vec3(0.1, 0.2, 0.5)));
	world.push_back(new sphere(vec3(0, -100.5, -1), 100));
	materials.push_back(new lambertian(vec3(0.8, 0.8, 0.0)));
	world.push_back(new sphere(vec3(1, 0, -1), 0.5));
	materials.push_back(new metal(vec3(0.8, 0.6, 0.2), 1.0));
	world.push_back(new sphere(vec3(-1, 0, -1), 0.5));
	materials.push_back(new dielectric(1.5));
	
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				ray r = cam.get_ray(u, v);

				col += calColor(r, world, materials, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outFile << ir << " " << ig << " " << ib << "\n";
			
		}
	}
	*/

	
	/*
	float R = cos(M_PI / 4);
	world.push_back(new sphere(vec3(-R, 0, -1), R));
	materials.push_back(new lambertian(vec3(0, 0, 1)));
	world.push_back(new sphere(vec3(R, 0, -1), R));
	materials.push_back(new lambertian(vec3(1, 0, 0)));
	*/
	/*out.ppm
	world.push_back(new sphere(vec3(0, 0, -1), 0.5));
	materials.push_back(new lambertian(vec3(0.8, 0.3, 0.3)));
	world.push_back(new sphere(vec3(0, -100.5, -1), 100));
	materials.push_back(new lambertian(vec3(0.8, 0.8, 0.0)));
	world.push_back(new sphere(vec3(1, 0, -1), 0.5));
	materials.push_back(new metal(vec3(0.8, 0.6, 0.2), 1.0));
	world.push_back(new sphere(vec3(-1, 0, -1), 0.5));
	materials.push_back(new metal(vec3(0.8, 0.8, 0.8), 0.3));
	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				ray r = cam.get_ray(u, v);

				col += calColor(r, world, materials, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outFile << ir << " " << ig << " " << ib << "\n";

		}
	}
	*/
	
	world.push_back(new sphere(vec3(0, -1000, 0), 1000));
	materials.push_back(new lambertian(vec3(0.5, 0.5, 0.5)));

	for (int a = -4; a < 4; a++) {
		for (int b = -4; b < 4; b++) {
			float choose_mat = random_double(0, 1);
			vec3 center(a + 0.9 * random_double(0, 1), 0.2, b + 0.9 * random_double(0, 1));
			if ((center - vec3(4, 0.2, 0)).length() > 0.9) {
				if (choose_mat < 0.8) {
					float sphere_tri = random_double(0, 1);
					if (sphere_tri > 0.5) {
						world.push_back(new sphere(center, 0.2));
					}
					else {
						world.push_back(new triangle(center, center - vec3(0.5 * random_double(0, 1), 0.5 * random_double(0, 1), 0.5 * random_double(0, 1)), center + vec3(0.5 * random_double(0, 1), 0.5 * random_double(0, 1), 0.5 * random_double(0, 1))));
					}
					materials.push_back(new lambertian(vec3(random_double(0, 1) * random_double(0, 1), random_double(0, 1) * random_double(0, 1), random_double(0, 1) * random_double(0, 1))));
				}
				else if (choose_mat < 0.95) {
					world.push_back(new sphere(center, 0.2));
					materials.push_back(new metal(vec3(0.5 * (1+random_double(0, 1)), 0.5 * (1 + random_double(0, 1)), 0.5 * (1 + random_double(0, 1))), 0.5* random_double(0, 1)));
				}
				else {
					world.push_back(new sphere(center, 0.2));
					materials.push_back(new dielectric(1.5));
				}
			}
		}
	}
	world.push_back(new sphere(vec3(0, 1, 0), 1.0));
	materials.push_back(new metal(vec3(0.7, 0.6, 0.5), 0.0));
	world.push_back(new sphere(vec3(-4, 1, 0), 1.0));
	materials.push_back(new lambertian(vec3(0.4, 0.2, 0.1)));
	world.push_back(new sphere(vec3(4, 1, 0), 1.0));
	materials.push_back(new metal(vec3(0.8, 0.6, 0.3), 0.2));

	for (int j = ny - 1; j >= 0; j--) {
		for (int i = 0; i < nx; i++) {
			vec3 col(0, 0, 0);
			for (int s = 0; s < ns; s++) {
				float u = float(i) / float(nx);
				float v = float(j) / float(ny);

				ray r = cam.get_ray(u, v);

				col += calColor(r, world, materials, 0);
			}
			col /= float(ns);
			col = vec3(sqrt(col[0]), sqrt(col[1]), sqrt(col[2]));
			int ir = int(255.99 * col[0]);
			int ig = int(255.99 * col[1]);
			int ib = int(255.99 * col[2]);

			outFile << ir << " " << ig << " " << ib << "\n";

		}
	}

	outFile.close();

	return 0;
}