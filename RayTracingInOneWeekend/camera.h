#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "rtweekend.h"

class camera
{
public:
	camera(int m, int n)
	{
		lower_left_corner = vec3(-m / 2, -n / 2, -1.0);
		horizontal = vec3(m, 0.0, 0.0);
		vertical = vec3(0.0, n, 0.0);
		origin = vec3(0.0, 0.0, 0.0);
	}

	ray get_ray(double u, double v) const
	{
		ray r(origin, lower_left_corner + u * horizontal + v * vertical - origin);
		return r;
	}

public:
	vec3 lower_left_corner;
	vec3 horizontal;
	vec3 vertical;
	vec3 origin;
};

#endif // !_CAMERA_H_
