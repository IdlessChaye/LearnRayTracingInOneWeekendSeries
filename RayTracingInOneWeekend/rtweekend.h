#ifndef _RTWEEKEND_H_
#define _RTWEEKEND_H_

#include <cstdlib>
#include <limits>

const double infinity = std::numeric_limits<double>::infinity();

inline double random_double()
{
	return rand() / (RAND_MAX + 1.0);
}

inline double random_double(double min, double max)
{
	return min + (max - min) * random_double();
}

inline int random_int(int min, int max)
{
	return static_cast<int>(random_double(min, max + 1));
}

#include "vec3.h"
#include "ray.h"

#endif