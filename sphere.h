#ifndef SPHEREH
#define SPHEREH 

#include "hitable.h"

class sphere: public hitable{
public:
	sphere() {}
	sphere(vec3 cen, float r): center(cen), radius(r) {}
	virtual bool hit(const ray &r, float tmin, float tmax, hit_record &rec) const;

private:
	vec3 center;
	float radius;
};

bool sphere::hit(const ray &r, float t_min, float t_max, hit_record &rec) const {
	vec3 oc = r.origin() - center;
	float a = dot(r.direction(), r.direction());
	float b = dot(oc, r.direction());
	float c = dot(oc, oc) - radius*radius;
	float disciminant = b * b - a * c;
	if(disciminant > 0){
		float tmp = (-b - sqrt(b * b - a * c)) / a;
		if(tmp < t_max && t_min < tmp){
			rec.t = tmp;
			rec.p = r.forward(tmp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
		tmp = (-b + sqrt(b * b - a * c)) / a;
		if(tmp < t_max && t_min < tmp){
			rec.t = tmp;
			rec.p = r.forward(tmp);
			rec.normal = (rec.p - center) / radius;
			return true;
		}
	}
	return false;
}

#endif
