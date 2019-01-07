#include "vec3.hpp"

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
