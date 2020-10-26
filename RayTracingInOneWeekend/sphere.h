#ifndef _SPHERE_H_
#define _SPHERE_H_

#include "hitable.h"

class sphere : public hitable
{
public:
	sphere(const vec3& cen, const double r)
		:center(cen), radius(r)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

private:
	vec3 center;
	double radius;

};

bool sphere::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	vec3 oc = r.origin() - center;
	auto a = r.direction().length_squared();
	auto half_b = dot(oc, r.direction());
	auto c = oc.length_squared() - radius * radius;
	auto discriminant = half_b * half_b - a * c;

	if (discriminant > 0)
	{
		auto root = sqrt(discriminant);

		auto temp = (-half_b - root) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.normal = outward_normal;
			return true;
		}

		temp = (-half_b + root) / a;
		if (temp < t_max && temp > t_min)
		{
			rec.t = temp;
			rec.p = r.at(rec.t);
			vec3 outward_normal = (rec.p - center) / radius;
			rec.normal = outward_normal;
			return true;
		}
	}
	return false;
}

#endif // !_SPHERE_H_
