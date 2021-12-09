# CMakeList.txt: FinalProject 的 CMake 项目，在此处包括源代码并定义
# 项目特定的逻辑。
#
cmake_minimum_required (VERSION 3.8)

project ("FinalProject")

# 将源代码添加到此项目的可执行文件。
add_executable (FinalProject "FinalProject.cpp" "FinalProject.h" "vec3.h" "ray.h" "Geometry.h" "sphere.h" "spreadSheet.h" "camera.h" "material.h" "triangle.h")

# TODO: 如有需要，请添加测试并安装目标。
