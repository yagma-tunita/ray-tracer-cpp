#pragma once

#include "vec3.hpp"

struct Ray 
{
	Vec3 origin;
	Vec3 direction;

	Ray(const Vec3& O, const Vec3& D) :origin(O), direction(D) {}
	Vec3 At(double t) const
	{
		return Add(origin, Scale(direction, t));
	}
};

