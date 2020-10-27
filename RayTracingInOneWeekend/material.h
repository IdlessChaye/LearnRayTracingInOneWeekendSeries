#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include "hitable.h"

double schlick(double cosine, double ref_idx)
{
	auto r0 = (1 - ref_idx) / (1 + ref_idx);
	r0 = r0 * r0;
	return r0 + (1 - r0) * pow((1 - cosine), 5);
}

class material
{
public:
	virtual bool scatter(const ray& r, const hit_record& rec, vec3& attenuation, ray& scattered) const = 0;
};

class lambertian : public material
{
public:
	lambertian(const vec3& a) : albedo(a) {}
	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		attenuation = albedo;
		scattered = ray(rec.p, rec.normal + random_unit_vector());
		return true;
	}

private:
	vec3 albedo;
};


class metal : public material
{
public:
	metal(const vec3& a,const double f): albedo(a) 
	{
		if (abs(f) <= 1)
			fuzz = f;
		else
			fuzz = 1;
	}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		attenuation = albedo;
		vec3 reflected = reflect(unit_vector(r_in.direction()), rec.normal);
		scattered = ray(rec.p, reflected + fuzz * random_in_unit_sphere());
		return (dot(scattered.direction(), rec.normal) > 0);
	}

public:
	vec3 albedo;
	double fuzz;
};


class dielectric : public material
{
public:
	dielectric(double ri) : ref_idx(ri) {}

	virtual bool scatter(const ray& r_in, const hit_record& rec, vec3& attenuation, ray& scattered) const
	{
		attenuation = vec3(1,1,1);
		double etai_over_etat = rec.front_face ? 1.0 / ref_idx : ref_idx;

		vec3 unit_direction = unit_vector(r_in.direction());
		double cos_theta = ffmin(dot(-unit_direction, rec.normal), 1.0);
		double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		if (etai_over_etat * sin_theta > 1.0)
		{
			vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = ray(rec.p, reflected);
			return true;
		}

		double reflect_prob = schlick(cos_theta, etai_over_etat);
		if (random_double() < reflect_prob)
		{
			vec3 reflected = reflect(unit_direction, rec.normal);
			scattered = ray(rec.p, reflected);
			return true;
		}

		vec3 refracted = refract(unit_direction, rec.normal, etai_over_etat);
		scattered = ray(rec.p, refracted);
		return true;
	}
	
private:
	double ref_idx;
};


#endif // !_MATERIAL_H_
