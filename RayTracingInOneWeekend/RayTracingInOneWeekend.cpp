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

hitable_list* random_scene()
{
	const int n = 500;
	hitable** list = new hitable * [n + 1];
	hitable_list* world = new hitable_list(list,n);

	world->add(
		new sphere(vec3(0, -1000, 0), 1000,new lambertian(vec3(0.5, 0.5, 0.5)))
	);

	int i = 1;
	for (int a = -11; a < 11; a++)
	{
		for (int b = -11; b < 11; b++)
		{
			auto choose_mat = random_double();
			vec3 center(a + 0.9 * random_double(), 0.2, b + 0.9 * random_double());
			if ((center - vec3(4, 0.2, 0)).length() > 0.9)
			{
				if (choose_mat < 0.8)
				{
					// diffuse
					auto albedo = vec3::random() * vec3::random();
					world->add(
						new sphere(center, 0.2,new lambertian(albedo)));
				}
				else if (choose_mat < 0.95)
				{
					// metal
					auto albedo = vec3::random(.5, 1);
					auto fuzz = random_double(0, .5);
					world->add(
						new sphere(center, 0.2, new metal(albedo, fuzz)));
				}
				else
				{
					// glass
					world->add(new sphere(center, 0.2, new dielectric(1.5)));
				}
			}
		}
	}

	world->add(
		new sphere(vec3(0, 1, 0), 1.0, new dielectric(1.5)));
	world->add(
		new sphere(vec3(-4, 1, 0), 1.0,new lambertian(vec3(0.4, 0.2, 0.1))));
	world->add(
		new sphere(vec3(4, 1, 0), 1.0, new metal(vec3(0.7, 0.6, 0.5), 0.0)));

	return world;
}

int main()
{
	// 一光线最大弹射次数
	const int max_depth = 50;
	// 一像素采样数量
	const int ns = 12;
	// 像素数量
	const int image_width = 400;
	const int image_height = 300;
	// 相机参数
	vec3 lookfrom(13, 2, 3);
	vec3 lookat(0, 0, 0);
	double dist_to_focus = 10.0;
	double aperture = 0.2;


	out_image out_file("out_image.ppm", image_width, image_height);

	vec3 vup(0, 1, 0);
	const auto aspect_ratio = double(image_width) / image_height;
	camera cam(lookfrom, lookat, vup, 20, aspect_ratio, aperture, dist_to_focus);

	// 有多少个球
	//const size_t list_count = 5;
	//hitable* list[list_count];
	//list[0] = new sphere(vec3(0, 0, -1), 0.5, new lambertian(vec3(0.1, 0.2, 0.5)));
	//list[1] = new sphere(vec3(0, -100.5, -1), 100, new lambertian(vec3(0.8, 0.8, 0)));
	//list[2] = new sphere(vec3(1, 0, -1), 0.5, new metal(vec3(0.8, 0.6, 0.2), 0.2));
	//list[3] = new sphere(vec3(-1, 0, -1), 0.5, new dielectric(1.5));
	//list[4] = new sphere(vec3(-1, 0, -1), -0.45, new dielectric(1.5));
	//hitable* scene = new hitable_list(list, list_count);
	hitable* scene = random_scene();

	for (int j = image_height - 1; j >= 0; j--)
	{
		for (int i = 0; i < image_width; i++)
		{
			vec3 col;
			for (int k = 0; k < ns; k++)
			{
				double u = (double)(i + random_double()) / image_width;
				double v = (double)(j + random_double()) / image_height;
				ray r = cam.get_ray(u, v);
				vec3 _color = color(r, scene, max_depth);
				col += _color;
			}
			col *= 1.0 / ns;
			col = vec3(sqrt(col.r()), sqrt(col.g()), sqrt(col.b()));
			col *= 255.99f;
			out_file << col;
		}
		std::cout << "new line: " << j << std::endl;
	}
}