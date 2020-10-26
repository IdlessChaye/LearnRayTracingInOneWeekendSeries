#include "rtweekend.h"

#include "out_image.h"
#include "sphere.h"
#include "hitable_list.h"
#include "camera.h"


vec3 color(const ray& r, const hitable* scene)
{
	hit_record rec;
	if (scene->hit(r, 0.001, infinity, rec))
	{
		vec3 normal = rec.normal;
		return 0.5 * vec3(normal.x() + 1, normal.y() + 1, normal.z() + 1);
	}

	vec3 unit_dir = unit_vector(r.direction());
	double t = 0.5 * (unit_dir.y() + 1.0);

	vec3 src_color(1.0, 1.0, 1.0);
	vec3 dst_color(0.5, 0.7, 1.0);
	return lerp(src_color, dst_color, t);
}

int main()
{
	// 像素数量
	int nx = 200;
	int ny = 100;
	out_image out_file("out_image.ppm", nx, ny);

	// 一单位距离多少个像素
	double ratio = 50;
	double m = nx / ratio;
	double n = ny / ratio;
	camera cam(m, n);

	// 一像素采样数量
	int ns = 10;

	// 有多少个球
	const size_t list_count = 2;
	hitable* list[list_count];
	list[0] = new sphere(vec3(0, 0, -1), 0.5);
	list[1] = new sphere(vec3(0, -100.5, -1), 100);
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
				col += color(r, scene);
			}
			col /= ns;
			col *= 255.99f;
			out_file << col;
		}
	}
}