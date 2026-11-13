#pragma once

#include "ray.hpp"
#include "hittable.hpp"
#include <vector>

class Light
{
private:
	Vec3 m_position;
	double m_intensity;
	Vec3 m_color;

public:
	inline Light(Vec3 position, double intensity, Vec3 color)
		:m_position(position), m_intensity(intensity), m_color(color) {}
	inline Vec3 Position()const { return m_position; }
	inline double Intensity() const{ return m_intensity; }
	inline Vec3 Color()const { return m_color; }
};

Vec3 Shade(const HitRecord& rec, const std::vector<Light>& lights, const Vec3& baseColor, double ambient);