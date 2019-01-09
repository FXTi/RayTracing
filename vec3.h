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

inline std::istream& operator>>(std::istream &is, vec3 &v){
	is >> v.x() >> v.y() >> v.z();
	return is;
}

inline std::ostream& operator<<(std::ostream &os, vec3 &v){
	os << v.x() << v.y() << v.z();
	return os;
}

inline void vec3::unit(){
	operator/=(length());
}

inline vec3 operator+(const vec3 &left, const vec3 &right){
	vec3 v(left);
	v += right;
	return v;
}

inline vec3 operator-(const vec3 &left, const vec3 &right){
	vec3 v(left);
	v -= right;
	return v;
}

inline vec3 operator*(const vec3 &left, const vec3 &right){
	vec3 v(left);
	v *= right;
	return v;
}

inline vec3 operator/(const vec3 &left, const vec3 &right){
	vec3 v(left);
	v /= right;
	return v;
}


inline vec3 operator*(float t, const vec3 &right){
	vec3 v(right);
	v *= t;
	return v;
}

inline vec3 operator*(const vec3 &left, float t){
	vec3 v(left);
	v *= t;
	return v;
}

inline vec3 operator/(const vec3 &left, float t){
	vec3 v(left);
	v /= t;
	return v;
}

inline float dot(const vec3 &left, const vec3 &right){
	vec3 &lhs = const_cast<vec3&>(left);
	vec3 &rhs = const_cast<vec3&>(right);
	return lhs.x() * rhs.x() + lhs.y() * rhs.y() + lhs.z() * rhs.z();
}

inline vec3 cross(const vec3 &left, const vec3 &right){
	vec3 &lhs = const_cast<vec3&>(left);
	vec3 &rhs = const_cast<vec3&>(right);
	return vec3(lhs.y()*rhs.z() - lhs.z()*rhs.y(),
				-(lhs.x()*rhs.z() - lhs.z()*rhs.x()),
				lhs.x()*rhs.y() - lhs.y()*rhs.x());
}

inline vec3& vec3::operator+=(const vec3 &v){
	v0 += v.v0;
	v1 += v.v1;
	v2 += v.v2;
	return *this;
}

inline vec3& vec3::operator*=(const vec3 &v){
	v0 *= v.v0;
	v1 *= v.v1;
	v2 *= v.v2;
	return *this;
}

inline vec3& vec3::operator/=(const vec3 &v){
	v0 /= v.v0;
	v1 /= v.v1;
	v2 /= v.v2;
	return *this;
}

inline vec3& vec3::operator-=(const vec3 &v){
	v0 -= v.v0;
	v1 -= v.v1;
	v2 -= v.v2;
	return *this;
}

inline vec3& vec3::operator*=(const float right){
	v0 *= right;
	v1 *= right;
	v2 *= right;
	return *this;
}

inline vec3& vec3::operator/=(const float right){
	v0 /= right;
	v1 /= right;
	v2 /= right;
	return *this;
}

inline vec3 unit_vector(const vec3 &v){
	return v / v.length();
}
