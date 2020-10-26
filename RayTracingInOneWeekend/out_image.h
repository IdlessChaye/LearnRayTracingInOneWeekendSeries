#ifndef _OUT_IMAGE_H_
#define _OUT_IMAGE_H_

#include <iostream>
#include <fstream>

#include "vec3.h"

class out_image
{
public:
	out_image(const char* file_name,int nx,int ny): image(file_name),nx(nx),ny(ny) 
	{
		image << "P3\n" << nx << " " << ny << "\n255\n";
	}

	int get_nx() const { return nx; }
	int get_ny() const { return ny; }

	void add_color(const vec3& color)
	{
		image << (int)color.r() << " " << (int)color.g() << " " << (int)color.b() << "\n";
	}

	void add_color(const int r, const int g, const int b)
	{
		image << r << " " << g << " " << b << "\n";
	}

	out_image& operator<<(const char* str) { 
		image << str;
		return *this;
	}

	out_image& operator<<(const vec3& v)
	{
		add_color(v);
		return *this;
	}

	~out_image()
	{
		image.close();
	}

private:
	std::ofstream image;
	int nx;
	int ny;
};

#endif