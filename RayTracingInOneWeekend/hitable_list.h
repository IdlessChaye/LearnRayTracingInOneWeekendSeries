#ifndef _HITABLE_LIST_H_
#define _HITABLE_LIST_H_

#include "hitable.h"

class hitable_list : public hitable
{
public:
	hitable_list():list(nullptr),list_size(0){}
	hitable_list(hitable** l, int n)
		:list(l), list_size(n)
	{}

	virtual bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const;

private:
	hitable** list;
	int list_size;
};

bool hitable_list::hit(const ray& r, double t_min, double t_max, hit_record& rec) const
{
	hit_record temp_rec;
	bool is_hitted = false;
	double closest_so_far = t_max;
	for (int i = 0; i < list_size; i++)
	{
		if (list[i]->hit(r, t_min, closest_so_far, temp_rec))
		{
			is_hitted = true;
			closest_so_far = temp_rec.t;
			rec = temp_rec;
		}
	}
	return is_hitted;
}

#endif // !_HITABLE_LIST_H_
