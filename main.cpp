#include <iostream>
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"
#include <cfloat>

vec3 random_in_unit_sphere(){
	vec3 p;
	do{
		p = 2.0 * vec3(drand48(), drand48(), drand48()) - vec3(1.0, 1.0, 1.0);
	} while (p.squared_length() >= 1.0);
	return p;
}

vec3 color(const ray &r, hitable *world){
	hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)){
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		return 0.5 * color(ray(rec.p, target - rec.p), world);
	}else{
		vec3 unit_direction = unit_vector(r.direction());
		float t = 0.5 * (unit_direction.y() + 1.0);
		return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
	}
}

int main(){
	int nx = 800;
	int ny = 400;
	int ns = 100;
	std::cout << "P3" << std::endl;
	std::cout << nx << " " << ny << std::endl;
	std::cout << "255" << std::endl;
	hitable *list[2];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
	hitable *world = new hitable_list(list, 2);
	camera cam;

	for(int j = ny-1; j >= 0; --j){
		for(int i = 0; i < nx; ++i){
			vec3 col(0, 0, 0);
			for(int s = 0; s < ns; ++s){
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				//vec3 p = r.forward(2.0);
				col += color(r, world);
			}
			col /= float(ns);
			col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
			int ir = int(255.99 * col.r());
			int ig = int(255.99 * col.g());
			int ib = int(255.99 * col.b());

			std::cout << ir << " " << ig << " " << ib << std::endl;
		}
	}

	return 0;
}