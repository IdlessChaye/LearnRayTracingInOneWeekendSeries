#ifndef _HITABLE_H_
#define _HITABLE_H_

#include "rtweekend.h"

struct hit_record
{
	double t;
	vec3 p;
	vec3 normal;
};

class hitable
{
public:
	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& hit) const = 0;
};

#endif
