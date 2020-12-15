#pragma once
#include "hittable.h"
class sphere : public hittable
{
public:
	sphere() = default;
	virtual ~sphere() = default;

	sphere(point3 cen, double r) : center(cen), radius(r) {}

	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
		vec3 oc = r.orig - center;
		const double a = r.dir.length_squared();
		const double half_b = dot(oc, r.dir);
		const double c = oc.length_squared() - radius * radius;

		const double discriminant = half_b * half_b - a * c;
		if (discriminant < 0) return false;
		const double sqrtd = sqrt(discriminant);

		double root = (-half_b - sqrtd) / a;
		if (root < t_min || t_max < root)
		{
			root = (-half_b + sqrtd) / a;
			if (root < t_min || t_max < root)
			{
				return false;
			}
		}

		rec.t = root;
		rec.p = r.at(rec.t);
		vec3 outward_normal = (rec.p - center) / radius;
		rec.set_face_normal(r, outward_normal);

		return true;
	}
	
public:
	point3 center;
	double radius;
};

