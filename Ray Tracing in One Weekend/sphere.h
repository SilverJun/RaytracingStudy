#pragma once
#include "hittable.h"
class sphere : public hittable
{
public:
	sphere() = default;
	virtual ~sphere() = default;

	sphere(point3 cen, double r, shared_ptr<material> m)
		: center(cen), radius(r), mat_ptr(m) {}

	bool hit(const ray& r, double t_min, double t_max, hit_record& rec) const override
	{
        vec3 oc = r.orig - center;
        auto a = r.dir.length_squared();
        auto half_b = dot(oc, r.dir);
        auto c = oc.length_squared() - radius * radius;

        auto discriminant = half_b * half_b - a * c;
        if (discriminant < 0) return false;
        auto sqrtd = sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (-half_b - sqrtd) / a;
        if (root < t_min || t_max < root) {
            root = (-half_b + sqrtd) / a;
            if (root < t_min || t_max < root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        vec3 outward_normal = (rec.p - center) / radius;
        rec.set_face_normal(r, outward_normal);
        rec.mat_ptr = mat_ptr;

        return true;
	}
	
public:
	point3 center;
	double radius;
	shared_ptr<material> mat_ptr;
};

