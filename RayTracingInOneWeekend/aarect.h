#ifndef _AARECT_H_
#define _AARECT_H_

#include "hitable.h"

class material;

class xy_rect : public hitable
{
public:
	xy_rect(float x0, float x1, float y0, float y1, float z, material* mat_ptr)
		:x0(x0), x1(x1), y0(y0), y1(y1), z(z), mat_ptr(mat_ptr)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

private:
	float x0;
	float x1;
	float y0;
	float y1;
	float z;
	material* mat_ptr;
};

class yz_rect : public hitable
{
public:
	yz_rect(float y0, float y1, float z0, float z1, float x, material* mat_ptr)
		:z0(z0), z1(z1), y0(y0), y1(y1), x(x), mat_ptr(mat_ptr)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

private:
	float z0;
	float z1;
	float y0;
	float y1;
	float x;
	material* mat_ptr;
};

class zx_rect : public hitable
{
public:
	zx_rect(float z0, float z1, float x0, float x1, float y, material* mat_ptr)
		:z0(z0), z1(z1), x0(x0), x1(x1), y(y), mat_ptr(mat_ptr)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

private:
	float z0;
	float z1;
	float x0;
	float x1;
	float y;
	material* mat_ptr;
};

bool xy_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	auto dir = r.direction();
	if (dir.z() == 0)
		return false;

	float t_arrive = (z - r.origin().z()) * (1.0 / r.direction().z());
	if (t_arrive < t_min || t_arrive > t_max)
		return false;

	vec3 p_arrive = r.at(t_arrive);
	if (p_arrive.x() > x1 || p_arrive.x() < x0 || p_arrive.y() > y1 || p_arrive.y() < y0)
		return false;

	rec.t = t_arrive;
	rec.p = p_arrive;
	vec3 outward_normal = vec3(0, 0, 1);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

bool yz_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	auto dir = r.direction();
	if (dir.x() == 0)
		return false;

	float t_arrive = (x - r.origin().x()) * (1.0 / r.direction().x());
	if (t_arrive < t_min || t_arrive > t_max)
		return false;

	vec3 p_arrive = r.at(t_arrive);
	if (p_arrive.y() > y1 || p_arrive.y() < y0 || p_arrive.z() > z1 || p_arrive.z() < z0)
		return false;

	rec.t = t_arrive;
	rec.p = p_arrive;
	vec3 outward_normal = vec3(1, 0, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

bool zx_rect::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	auto dir = r.direction();
	if (dir.y() == 0)
		return false;

	float t_arrive = (y - r.origin().y()) * (1.0 / r.direction().y());
	if (t_arrive < t_min || t_arrive > t_max)
		return false;

	vec3 p_arrive = r.at(t_arrive);
	if (p_arrive.x() > x1 || p_arrive.x() < x0 || p_arrive.z() > z1 || p_arrive.z() < z0)
		return false;

	rec.t = t_arrive;
	rec.p = p_arrive;
	vec3 outward_normal = vec3(0, 1, 0);
	rec.set_face_normal(r, outward_normal);
	rec.mat_ptr = mat_ptr;
	return true;
}

#endif // !_AARECT_H_
