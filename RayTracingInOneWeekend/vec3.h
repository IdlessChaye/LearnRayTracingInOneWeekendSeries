#ifndef _VEC3_H_
#define _VEC3_H_

#include <iostream>

class vec3
{
public:
	vec3() :e{ 0,0,0 } {}
	vec3(double e0, double e1, double e2) { e[0] = e0; e[1] = e1; e[2] = e2; }

	double x() const { return e[0]; }
	double y() const { return e[1]; }
	double z() const { return e[2]; }
	double r() const { return e[0]; }
	double g() const { return e[1]; }
	double b() const { return e[2]; }

	vec3 operator-() const { return vec3(-e[0], -e[1], -e[2]); }
	double operator[](int i) const { return e[i]; }
	double& operator[](int i) { return e[i]; }

	vec3& operator+=(const vec3& v)
	{
		e[0] += v.e[0];
		e[1] += v.e[1];
		e[2] += v.e[2];
		return *this;
	}

	vec3& operator*=(const double t)
	{
		e[0] *= t;
		e[1] *= t;
		e[2] *= t;
		return *this;
	}

	vec3& operator/=(const double t)
	{
		return *this *= 1 / t;
	}

	double length_squared() const { return e[0] * e[0] + e[1] * e[1] + e[2] * e[2]; }
	double length() const { return sqrt(length_squared()); }

	inline static vec3 random()
	{
		return vec3(random_double(), random_double(), random_double());
	}

	inline static vec3 random(double min, double max)
	{
		return vec3(random_double(min, max), random_double(min, max), random_double(min, max));
	}

private:
	double e[3];
};

inline std::ostream& operator<<(std::ostream& out, const vec3& v)
{
	return out << v.x() << ' ' << v.y() << ' ' << v.z();
}

inline vec3 operator+(const vec3& u, const vec3& v)
{
	return vec3(u.x() + v.x(), u.y() + v.y(), u.z() + v.z());
}

inline vec3 operator-(const vec3& u, const vec3& v)
{
	return vec3(u.x() - v.x(), u.y() - v.y(), u.z() - v.z());
}

inline vec3 operator*(const vec3& u, const vec3& v)
{
	return vec3(u.x() * v.x(), u.y() * v.y(), u.z() * u.z());
}

inline vec3 operator*(double t, const vec3& v)
{
	return vec3(t * v.x(), t * v.y(), t * v.z());
}

inline vec3 operator*(const vec3& v, double t)
{
	return t * v;
}

inline vec3 operator/(const vec3& v, double t)
{
	return (1 / t) * v;
}

inline double dot(const vec3& v, const vec3& u)
{
	return v.x() * u.x() + v.y() * u.y() + v.z() * u.z();
}

inline vec3 cross(const vec3& v, const vec3& u)
{
	return vec3(
		v.y() * u.z() - v.z() * u.y(),
		v.z() * u.x() - v.x() * u.z(),
		v.x() * u.y() - v.y() * u.x());
}

inline vec3 unit_vector(vec3 v)
{
	return v / v.length();
}

inline vec3 lerp(const vec3& u, const vec3& v, double t)
{
	return (1 - t) * u + t * v;
}

#endif