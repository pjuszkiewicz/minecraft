cmake_minimum_required(VERSION 3.5.0)
project(minecraft VERSION 0.1.0)
set(CMAKE_CXX_STANDARD 17)
cmake_policy(SET CMP0072 NEW)

find_package(OpenGL REQUIRED)

add_executable(minecraft src/glad.c src/main.cpp
        src/lib/map/pair_hash.h)

target_link_libraries(minecraft glfw)
# target_link_libraries(minecraft include/glad/glad.h)
# target_link_libraries(minecraft src/lib/KHR/khrplatform.h)
