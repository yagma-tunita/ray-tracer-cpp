#include "light.hpp"

Vec3 Shade(const HitRecord& rec, const std::vector<Light>& lights, const Vec3& baseColor, double ambient)
{
    Vec3 color = Scale(baseColor, ambient);

    for (const Light& light : lights)
    {
        Vec3 Lvec = Sub(light.Position(), rec.m_point);
        if (Length(Lvec) == 0.0) continue;
        Vec3 L = Normalize(Lvec);

        double c = Dot(rec.m_normal, L);
        if (c < 0.0) c = 0.0;

        Vec3 albedo = Mult(baseColor, light.Color());
        Vec3 term = Scale(albedo, c * light.Intensity());
        color = Add(color, term);
    }

    return color;
}