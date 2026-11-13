#include "image.hpp"
#include <fstream>

Image::Image(int w, int h):m_height(h),m_width(w)
{
	m_pixels = std::vector<Vec3>(h * w, Vec3(0, 0, 0));
}

void Image::SetPixel(int x, int y, const Vec3& c)
{
	m_pixels[static_cast<std::vector<Vec3, std::allocator<Vec3>>::size_type>(y) * m_width + x] = c;
}

namespace 
{
	static double Clamp01(double x)
	{
		if (x < 0.0) return 0.0;
		if (x > 1.0) return 1.0;
		return x;
	}
}

void Image::SavePPM(const std::string& filename) const
{
    std::ofstream out(filename, std::ios::binary);
    if (!out) return;              

    out << "P6\n" << m_width << " " << m_height << "\n255\n";

    for (const Vec3& c : m_pixels)
    {
        int r = (int)(255.0 * Clamp01(c.x));
        int g = (int)(255.0 * Clamp01(c.y));
        int b = (int)(255.0 * Clamp01(c.z));

        out.put((char)r);
        out.put((char)g);
        out.put((char)b);
    }
}