#pragma once

#include <cmath>

struct Vec3 
{
	double x = 0;
	double y = 0;
	double z = 0;

	inline Vec3() = default;
	inline Vec3(double a, double b, double c) :x(a), y(b), z(c) {}
};

inline Vec3 Add(const Vec3& a, const Vec3& b) { return Vec3(a.x + b.x, a.y + b.y, a.z + b.z); }
inline Vec3 Sub(const Vec3& a, const Vec3& b) { return Vec3(a.x - b.x, a.y - b.y, a.z - b.z); }
inline Vec3 Scale(const Vec3& a, double t) { return Vec3(a.x * t, a.y * t, a.z * t); }
inline Vec3 Neg(const Vec3& a) { return Vec3(-1 * a.x, -1 * a.y, -1 * a.z); }
inline Vec3 Mult(const Vec3& a, const Vec3& b) { return Vec3(a.x * b.x, a.y * b.y, a.z * b.z); }
inline Vec3 Div(const Vec3& a, double t) { return Vec3(a.x / t, a.y / t, a.z / t); }

inline double Dot(const Vec3& a, const Vec3& b) { return a.x * b.x + a.y * b.y + a.z * b.z; }
inline Vec3 Cross(const Vec3& a, const Vec3& b) 
{
	double x = a.y * b.z - a.z * b.y;
	double y = a.z * b.x - a.x * b.z;
	double z = a.x * b.y - a.y * b.x;
	return Vec3(x, y, z);
}
inline double LengthSquare(const Vec3& a) { return a.x * a.x + a.y * a.y + a.z * a.z; }
inline double Length(const Vec3& a) { return std::sqrt(LengthSquare(a)); }
inline Vec3 Normalize(const Vec3& a)
{
	double length = Length(a);
	if (length == 0)return Vec3();
	return Vec3(a.x / length, a.y / length, a.z / length);
}
