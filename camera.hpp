#pragma once

#include "ray.hpp"
#include "vec3.hpp"

class Camera 
{
private:
	Vec3 m_origin;
	Vec3 m_leftZero;
	Vec3 m_horizontal;    // row
	Vec3 m_vertical;      // cal

public:
	Camera(const Vec3& eye, const Vec3& lookat, const Vec3& up, double vfov, double aspect);
	Ray GetRay(double u, double v) const;
};