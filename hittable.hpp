#pragma once

#include "vec3.hpp"
#include "ray.hpp"

struct HitRecord 
{
	Vec3 m_point;
	Vec3 m_normal;
	double m_t = 0.0;
	bool m_frontFace = false;
};

class Hittable 
{
public:
	virtual ~Hittable() = default;
	virtual bool Hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const = 0;
};