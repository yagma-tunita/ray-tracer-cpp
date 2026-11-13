#pragma once

#include "hittable.hpp"

class Sphere :public Hittable
{
private:
	Vec3 m_center;
	double m_radius;

public:
	inline Sphere(const Vec3& center, double radius) :m_center(center), m_radius(radius) {}
	bool Hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const override;
};