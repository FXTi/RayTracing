#include <cmath>
#include <cstdlib>
#include <iostream>

class vec3{
public:
	vec3() {}
	vec3(float e0, float e1, float e2): v0(e0), v1(e1), v2(e2) {}
	vec3(const vec3 &v){
		v0 = const_cast<vec3&>(v).x();
		v1 = const_cast<vec3&>(v).y();
		v2 = const_cast<vec3&>(v).z();
	}

	float& x() {return v0;}
	float& y() {return v1;}
	float& z() {return v2;}
	float& r() {return v0;}
	float& g() {return v1;}
	float& b() {return v2;}

	vec3 operator-() const {return vec3(-v0, -v1, -v2);}

	vec3& operator+=(const vec3 &right);
	vec3& operator-=(const vec3 &right);
	vec3& operator*=(const vec3 &right);
	vec3& operator/=(const vec3 &right);
	vec3& operator*=(const float right);
	vec3& operator/=(const float right);

	float length() const {
		return sqrt(v0*v0 + v1*v1 + v2*v2);
	}

	float squared_length() const {
		return v0*v0 + v1*v1 + v2*v2;
	}

	void unit();

private:
	float v0;
	float v1;
	float v2;
};
