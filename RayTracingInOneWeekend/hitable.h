#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "rtweekend.h"

class material;

struct hit_record
{
	double t;
	vec3 p;
	vec3 normal;
	material* mat_ptr;
	bool front_face;

	inline void set_face_normal(const ray& r, const vec3& outward_normal)
	{
		front_face = dot(r.direction(), outward_normal) < 0;
		normal = front_face ? outward_normal : -outward_normal;
	}
};

class hitable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& hit) const = 0;
};


class flip_face : public hitable
{
public:
	flip_face(hitable* p) : ptr(p) {}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const
	{
		if (!ptr->hit(r, t_min, t_max, rec))
			return false;

		rec.front_face = !rec.front_face;
		rec.normal = -rec.normal;
		return true;
	}

public:
	hitable* ptr;
};

#endif
