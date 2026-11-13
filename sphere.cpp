#include "sphere.hpp"
#include <cmath>

bool Sphere::Hit(const Ray& ray, double tmin, double tmax, HitRecord& rec) const
{
    Vec3   oc = Sub(ray.origin, m_center);
    double a = Dot(ray.direction, ray.direction);
    double b = 2 * Dot(oc, ray.direction);
    double c = Dot(oc, oc) - m_radius * m_radius;
    double disc = b * b - 4 * a * c;

    if (disc < 0) return false;

    double sq = std::sqrt(disc);
    double t = (-b - sq) / (2 * a);        
    if (t < tmin || t > tmax)              
    {
        t = (-b + sq) / (2 * a);           
        if (t < tmin || t > tmax)          
            return false;
    }

    rec.m_t = t;
    rec.m_point = ray.At(t);
    Vec3 outward = Normalize(Sub(rec.m_point, m_center));

    if (Dot(ray.direction, outward) < 0)    
    {
        rec.m_frontFace = true;
        rec.m_normal = outward;
    }
    else                                    
    {
        rec.m_frontFace = false;
        rec.m_normal = Neg(outward);
    }

    return true;
}