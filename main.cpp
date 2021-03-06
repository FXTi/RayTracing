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

class lambertian : public material{
public:
	lambertian(const vec3 &a): albedo(a) {}

	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 target = rec.p + rec.normal + random_in_unit_sphere();
		scattered = ray(rec.p, target - rec.p);
		attenuation = albedo;
		return true;
	}

private:
	vec3 albedo;
};

vec3 reflect(const vec3 &v, const vec3 &n){
	return v - 2 * dot(v, n) * n;
}

bool refract(const vec3 &v, const vec3 &n, float ni_over_nt, vec3 &refracted){
	vec3 uv = unit_vector(v);
	float dt = dot(uv, n);
	float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
	if(discriminant > 0){
		refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
		return true;
	} else 
		return false;
}

float schlick(float cosine, float ref_idx){
	float r0 = (1.0 - ref_idx) / (1.0 + ref_idx);
	r0 *= r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class metal : public material{
public:
	metal(const vec3 &a, float f): albedo(a) {fuzz = (f<1.0)?f:1.0;}

	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		attenuation = albedo;
		return (dot(scattered.direction(), rec.normal) > 0);
	}

private:
	vec3 albedo;
	float fuzz;
};

class dielectric : public material{
public:
	dielectric(float ri) : ref_idx(ri) {}

	virtual bool scatter(const ray &r_in, const hit_record &rec, vec3 &attenuation, ray &scattered) const {
		vec3 outward_normal;
		vec3 reflected = reflect(r_in.direction(), rec.normal);
		float ni_over_nt;
		attenuation = vec3(1.0, 1.0, 1.0);
		vec3 refracted;
		float reflect_prob;
		float cosine;
		if(dot(r_in.direction(), rec.normal) > 0){
			outward_normal = -rec.normal;
			ni_over_nt = ref_idx;
			cosine = ref_idx * dot(r_in.direction(), rec.normal) / r_in.direction().length();
		} else {
			outward_normal = rec.normal;
			ni_over_nt = 1.0 / ref_idx;
			cosine = -dot(r_in.direction(), rec.normal) / r_in.direction().length();
		}
		if(refract(r_in.direction(), outward_normal, ni_over_nt, refracted)){
			reflect_prob = schlick(cosine, ref_idx);
		} else {
			//scattered = ray(rec.p, reflected);
			reflect_prob = 1.0;
		}
		if(drand48() < reflect_prob)
			scattered = ray(rec.p, reflected);
		else 
			scattered = ray(rec.p, refracted);
		return true;
	}
private:
	float ref_idx;
};

vec3 color(const ray &r, hitable *world, int depth){
	hit_record rec;
	if(world->hit(r, 0.001, MAXFLOAT, rec)){
		ray scattered;
		vec3 attenuation;
		if(depth < 50 && rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * color(scattered, world, depth+1);
		else 
			return vec3(0,0,0);
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
	hitable *list[4];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.8, 0.3, 0.3)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0.0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.3));
	list[3] = new sphere(vec3(-1, 0, -1), -0.5, new dielectric(1.5));
	hitable *world = new hitable_list(list, 4);
	camera cam(vec3(-2, 2, 1), vec3(0, 0, -1), vec3(0, 1, 0), 90, float(nx)/float(ny), 1.0, (vec3(-2, 2, 1) - vec3(0, 0, -1)).length());

	for(int j = ny-1; j >= 0; --j){
		for(int i = 0; i < nx; ++i){
			vec3 col(0, 0, 0);
			for(int s = 0; s < ns; ++s){
				float u = float(i + drand48()) / float(nx);
				float v = float(j + drand48()) / float(ny);
				ray r = cam.get_ray(u, v);
				//vec3 p = r.forward(2.0);
				col += color(r, world, 0);
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
