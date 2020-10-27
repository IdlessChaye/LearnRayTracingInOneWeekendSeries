#include "rtweekend.h"

#include "out_image.h"
#include "camera.h"
#include "sphere.h"
#include "hitable_list.h"
#include "material.h"


vec3 color(const ray& r, const hitable* scene, int depth)
{
	if (depth < 0)
		return vec3(0, 0, 0);

	hit_record rec;

	if (scene -> hit(r, 0.001, infinity, rec))
	{
		vec3 attenuation;
		ray scattered;
		if (rec.mat_ptr->scatter(r, rec, attenuation, scattered))
			return attenuation * color(scattered, scene, depth - 1);
		return vec3(0, 0, 0);
	}

	vec3 unit_direction = unit_vector(r.direction());
	auto t = 0.5 * (unit_direction.y() + 1.0);
	return (1.0 - t) * vec3(1.0, 1.0, 1.0) + t * vec3(0.5, 0.7, 1.0);
}

int main()
{
	// 一光线最大弹射次数
	const int max_depth = 10;

	// 像素数量
	int nx = 200;
	int ny = 100;
	out_image out_file("out_image.ppm", nx, ny);

	// 相机参数
	camera cam(vec3(-2,2,1), vec3(0,0,-1), vec3(0,1,0), 20.0, nx / ny);

	// 一像素采样数量
	int ns = 10;

	// 有多少个球
	const size_t list_count = 5;
	hitable* list[list_count];
	list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0)));
	list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2));
	list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	hitable* scene = new hitable_list(list, list_count);

	for (int j = ny - 1; j >= 0; j--)
	{
		for (int i = 0; i < nx; i++)
		{
			vec3 col;
			for (int k = 0; k < ns; k++)
			{
				double u = (double)(i + random_double()) / nx;
				double v = (double)(j + random_double()) / ny;
				ray r = cam.get_ray(u, v);
				vec3 _color = color(r, scene, max_depth);
				col += _color;
			}
			col *= 1.0 / ns;
			col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
			col *= 255.99f;
			out_file << col;
		}
	}
}