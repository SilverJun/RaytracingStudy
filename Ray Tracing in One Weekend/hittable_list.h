#pragma once

#include "hittable.h"

#include <vector>
#include <memory>

using std::shared_ptr;
using std::make_shared;
using std::vector;

class hittable_list :public hittable
{
public:
	hittable_list() = default;
	hittable_list(shared_ptr<hittable> object) { add(object); }

	void clear()
	{
		objects.clear();
	}

	void add(shared_ptr<hittable> object) { objects.push_back(object); }

	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		hit_record temp_rec;
		bool hit_anything = false;
		auto closest_so_far = t_max;

		for (const auto& object : objects) {
			if (object->hit(r, t_min, closest_so_far, temp_rec)) {
				hit_anything = true;
				closest_so_far = temp_rec.t;
				rec = temp_rec;
			}
		}

		return hit_anything;
	}

public:
	vector<shared_ptr<hittable>> objects;
};
