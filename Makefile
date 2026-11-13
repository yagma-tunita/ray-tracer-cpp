# Makefile - Windows (GNU make + MinGW g++)
# Build:  make
# Run:    make run        (writes out.ppm in the current directory)
# PNG:    make png        (uses python convert.py out.ppm out.png)
# Clean:  make clean
#
# Default compiler is MinGW g++ (available at D:\mingw64\bin).
# For MSVC, open the Visual Studio solution Ray.sln instead (see README).

CXX      ?= g++
CXXFLAGS ?= -std=c++17 -O2 -Wall
TARGET    = ray.exe
SRCS      = main.cpp camera.cpp sphere.cpp image.cpp light.cpp
OBJS      = $(SRCS:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

run: $(TARGET)
	$(TARGET)

png: out.ppm
	python convert.py out.ppm out.png

clean:
	$(RM) $(OBJS) $(TARGET) out.ppm out.png
