# Ray Tracer (C++, from scratch)

A small CPU ray tracer written from scratch in modern C++. For each pixel it shoots a ray
from the camera, finds the closest intersection with the scene, computes a shaded color
(Lambert diffuse + ambient with a point light), and writes the result to a **PPM (P6)** image.

The project has **no external C++ dependencies** (standard library only). It currently renders
a single sphere on a sky-gradient background, which is the foundation for adding more shapes,
materials and shadows.

> Note on file names: on Windows the names `readme.md` and `README.md` are the *same* file
> (case-insensitive), so this repository uses `README.md` for English and `README.zh.md` for Chinese.

---

## Code environment (for future contributors)

- **OS**: Windows (developed and tested on Windows 11). Build instructions are Windows-oriented.
- **Language standard**: **C++17** (`-std=c++17` with g++, `/std:c++17` with MSVC).
- **Compilers** (both work):
  - **MSVC** from **Visual Studio 2022** (`cl.exe`), via the solution `Ray.sln`.
  - **MinGW-w64 g++** (e.g. `D:\mingw64\bin\g++.exe`), via the `Makefile`.
- **External libraries**: none for C++ (only the standard library: `vec3`, `cmath`, `vector`,
  `fstream`, `string`). Image output uses the plain **PPM (P6)** format, which needs no library.
- **Python (optional, viewing only)**: Python 3 + **Pillow**, used only to convert `out.ppm`
  to a viewable `out.png` (`convert.py`). The renderer itself does not need Python.
- **Build outputs**: `ray.exe` (MinGW) or the VS debug/release output.
- **Working directory matters**: the program writes `out.ppm` to the *current working directory*
  (in Visual Studio this is the project directory by default).

---

## Project structure

| File | Type | Purpose |
|---|---|---|
| `vec3.hpp` | C++ header | 3D vector type + math (Add/Sub/Scale/Dot/Cross/Normalize...) |
| `ray.hpp` | C++ header | Ray = origin + direction, `At(t)` |
| `camera.hpp` / `camera.cpp` | C++ | Camera: pixel (u,v) -> ray; builds basis + viewport |
| `hittable.hpp` | C++ header | `HitRecord` + abstract `Hittable` interface |
| `sphere.hpp` / `sphere.cpp` | C++ | Sphere: ray-sphere intersection (quadratic) |
| `image.hpp` / `image.cpp` | C++ | Image buffer + `SavePPM` (P6) |
| `light.hpp` / `light.cpp` | C++ | Point light `Light` + `Shade` (Lambert + ambient) |
| `main.cpp` | C++ | Assembly + render loop + output |
| `Makefile` | Build | Windows build script (GNU make + MinGW g++ by default) |
| `convert.py` | Python | Convert `out.ppm` -> `out.png` (Pillow); for viewing only |
| `codelog.txt` / `codelog2.txt` | docs | Development log (Chinese / English) |
| `Ray.sln`, `Ray.vcxproj*` | VS | Visual Studio solution/project for MSVC |

---

## Build & run (Windows)

### Option A: Visual Studio 2022 (MSVC)
1. Open `Ray.sln` in Visual Studio 2022.
2. Build and run (F5). The program writes `out.ppm` to the project directory.
3. (Optional) Convert to PNG for viewing:
   ```
   python convert.py out.ppm out.png
   ```

### Option B: Makefile (GNU make + MinGW g++)
The `Makefile` is written for **Windows** and uses **MinGW g++** by default.
Run these from the project directory in a terminal where `make` and `g++` are on `PATH`:

```
make            # builds ray.exe
make run        # runs ray.exe (writes out.ppm in the current directory)
make png        # converts out.ppm -> out.png via python convert.py
make clean      # removes .o, ray.exe, out.ppm, out.png
```

If you prefer MSVC with the Makefile, use the **"x64 Native Tools Command Prompt for VS 2022"**
(so `cl` and the environment are set up) and adjust the compiler/flags accordingly. The easiest
MSVC route is simply the Visual Studio solution.

---

## How it works (pipeline)

```
for each pixel (x, y):
    (u, v) = normalized pixel coordinates in [0,1]      // v is flipped vertically
    ray    = camera.GetRay(u, v)                       // from the eye into the scene
    if scene is hit (closest t):
        color = Shade(hit, lights, baseColor, ambient)  // Lambert diffuse + ambient
    else:
        color = background gradient
    image.SetPixel(x, y, color)
image.SavePPM("out.ppm")
```

Key ideas:
- **Ray tracing is backward**: rays start at the eye, pass through the pixel, and go into the
  scene to find what is visible. The physical light direction is the reverse of this.
- **Intersection** = solving an equation for the ray parameter `t` (for a sphere it is a
  quadratic). The nearest valid root in `[tmin, tmax]` is the visible surface.
- **Normal** = the normal of the *tangent plane* at the hit point (perpendicular to the surface,
  not to the ray). It is oriented toward the camera side and used for shading.
- **Shading** uses the angle between the surface normal and the light direction:
  `max(0, dot(normal, lightDir))`.

---

## Module summary

- **vec3.hpp**: `Vec3` with `Add/Sub/Scale/Neg/Mult/Div/Dot/Cross/Length/Normalize`.
  Same type is used for points, directions and colors (colors 0..1).
- **ray.hpp**: `Ray(origin, direction)` with `At(t) = origin + t*direction`.
- **camera.hpp/.cpp**: builds an orthonormal camera basis (`back/right/up`), a viewport of size
  `2*tan(vfov/2)` (height) times `aspect` (width), and returns a ray through `(u,v)`.
- **hittable.hpp**: `HitRecord { point, normal, t, frontFace }` and abstract `Hittable` with
  `virtual bool Hit(ray, tmin, tmax, rec) const`. The renderer depends only on this interface.
- **sphere.hpp/.cpp**: `Sphere : public Hittable`; quadratic ray-sphere intersection, fills
  `HitRecord` (nearest root, point, normal, frontFace).
- **image.hpp/.cpp**: `Image(w, h)` buffer; `SetPixel` (row-major `y*w + x`); `SavePPM` writes a
  binary P6 PPM (clamp to [0,1], multiply by 255).
- **light.hpp/.cpp**: `Light(position, intensity, color)` + `Shade(rec, lights, baseColor, ambient)`
  which sums `baseColor * lightColor * intensity * max(0, dot(N,L))` over all lights, plus ambient.
- **main.cpp**: sets resolution, camera, sphere and lights; renders all pixels; writes `out.ppm`.

---

## About `convert.py`

`convert.py` is a 4-line helper that converts the rendered PPM into PNG so it can be viewed with
the Windows Photos app (PPM is not supported by default):

```python
import sys
from PIL import Image
Image.open(sys.argv[1]).save(sys.argv[2])
```

Usage:
```
python convert.py out.ppm out.png
```
Requires Python 3 and Pillow (`pip install Pillow`). This script is **only for viewing**; the
ray tracer does not depend on it.

---

## Current status & roadmap

Done:
- Camera + ray generation, sphere intersection, normal calculation.
- Point light with Lambert diffuse + ambient; sky-gradient background.
- PPM output (800x600) and PNG conversion for viewing.

Next steps (suggested):
- **Shadows**: cast a shadow ray from the hit point to each light; occluded => no diffuse term.
- **Materials**: diffuse / metal / glass, with reflection and refraction (Snell).
- **Multiple objects**: add a `HittableList`/`Scene` that returns the closest hit.
- **Gamma correction** and **anti-aliasing** (multiple samples per pixel).
- Configurable parameters (resolution, samples, FOV) via command line or a config file.

---

## How to extend / rewrite (for future contributors)

- **Add a new shape**: create `class Xxx : public Hittable` and implement
  `bool Hit(ray, tmin, tmax, rec) const override`. No renderer changes needed.
- **Multiple objects**: add a `HittableList` (holds `Hittable*`/`std::unique_ptr`) that iterates
  shapes and keeps the closest `t`; pass it to `Shade` for shadow rays.
- **Materials**: extend `HitRecord` with a material pointer and let materials compute the color
  (reflection/refraction) instead of the fixed `Shade`.
- **More lights**: just push more `Light` objects into the vector; `Shade` sums them.
- **Image size/quality**: change `W/H` and sample count; remember `aspect = W/H` and flip `v`.
- **Switching compilers**: the code is standard C++17 with no MSVC/GCC extensions; both
  `cl` and `g++` should build it. Only `image.cpp` uses a verbose standard-library cast.

---

## Troubleshooting

- **`out.ppm` cannot be opened**: Windows Photos does not support PPM. Convert it:
  `python convert.py out.ppm out.png`. Or open the PPM in IrfanView / GIMP / Photoshop.
- **Image looks transposed / wrong size (e.g. 600x800)**: `Image`'s constructor is
  `Image(int w, int h)` (width first). Construct it as `Image(W, H)`.
- **Image upside down**: flip the vertical coordinate: `v = 1 - y/(H-1)`.
- **Everything black / no sphere**: check the camera looks at the sphere (e.g. eye at origin,
  lookat `(0,0,-1)`, sphere at `(0,0,-1)`) and that `tmax` is large (e.g. `1e9`).
- **Link error LNK1561 (no entry point)**: make sure `main.cpp` is included in the build.
