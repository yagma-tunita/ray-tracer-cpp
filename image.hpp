#pragma once

#include "vec3.hpp"
#include <vector>
#include <string>

class Image 
{
private:
	int m_height;
	int m_width;
	std::vector<Vec3>m_pixels;

public:
	Image(int w, int h);
	void SetPixel(int x, int y, const Vec3& c);
	void SavePPM(const std::string& filename) const;
};