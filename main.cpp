#include "camera.hpp"
#include "image.hpp"
#include "sphere.hpp"
#include "light.hpp"
#include <vector>

const int W = 800;
const int H = 600;
const double aspect = W * 1.0 / H;

int main(void)
{
    Image image(W, H);
    Camera camera(Vec3(0, 0, 0), Vec3(0, 0, -1), Vec3(0, 1, 0), 90.0, aspect);
    Sphere sphere(Vec3(0, 0, -1), 0.5);

    std::vector<Light> lights;
    lights.push_back(Light(Vec3(2, 2, 0), 1.0, Vec3(1, 1, 1)));

    for (int y = 0; y < H; ++y)
    {
        for (int x = 0; x < W; ++x)
        {
            double u = (double)x / (W - 1);
            double v = 1.0 - (double)y / (H - 1);

            Ray ray = camera.GetRay(u, v);
            HitRecord rec;

            Vec3 color;
            if (sphere.Hit(ray, 0.001, 1e9, rec))
            {
                color = Shade(rec, lights, Vec3(0.85, 0.85, 0.8), 0.1);
            }
            else
            {
                double k = 0.5 * (Normalize(ray.direction).y + 1.0);
                color = Add(Scale(Vec3(1.0, 1.0, 1.0), 1.0 - k), Scale(Vec3(0.5, 0.7, 1.0), k));
            }

            image.SetPixel(x, y, color);
        }
    }

    image.SavePPM("out.ppm");
    return 0;
}