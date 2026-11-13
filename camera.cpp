#include "camera.hpp"
#include <cmath>

static const double PI = 3.1415926535;

Camera::Camera(const Vec3& eye, const Vec3& lookat, const Vec3& up, double vfov, double aspect) :m_origin(eye)
{
	Vec3 back = Normalize(Sub(eye, lookat));
	Vec3 right = Normalize(Cross(up, back));
	Vec3 cameraUp = Cross(back, right);

	double theta = vfov * PI / 180;
	double height = 2 * std::tan(theta / 2);
	double width = aspect * height;

	m_horizontal = Scale(right, width);
	m_vertical = Scale(cameraUp, height);
	m_leftZero = Sub(Sub(Sub(eye, back), Div(m_horizontal, 2)), Div(m_vertical, 2));
}

Ray Camera::GetRay(double x, double y) const
{
	Vec3 point = Add(Add(m_leftZero, Scale(m_horizontal, x)), Scale(m_vertical, y));
	Vec3 dir = Sub(point, m_origin);

	return Ray(m_origin, Normalize(dir));
}
