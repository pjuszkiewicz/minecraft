#ifndef SPHERE_GEOMETRY_H
#define SPHERE_GEOMETRY_H
#include <vector>
#include <cmath>

inline std::vector<float> generateSphere(float radius, int sectorCount, int stackCount) {
    std::vector<float> vertices;
    const float PI = 3.14159265359f;

    for (int i = 0; i < stackCount; ++i) {
        float stackAngle1 = PI / 2 - (i * (PI / stackCount));
        float stackAngle2 = PI / 2 - ((i + 1) * (PI / stackCount));

        float xy1 = radius * cosf(stackAngle1);
        float z1 = radius * sinf(stackAngle1);
        float xy2 = radius * cosf(stackAngle2);
        float z2 = radius * sinf(stackAngle2);

        for (int j = 0; j < sectorCount; ++j) {
            float sectorAngle1 = j * (2 * PI / sectorCount);
            float sectorAngle2 = (j + 1) * (2 * PI / sectorCount);

            float x1 = xy1 * cosf(sectorAngle1);
            float y1 = xy1 * sinf(sectorAngle1);
            float x2 = xy2 * cosf(sectorAngle1);
            float y2 = xy2 * sinf(sectorAngle1);
            float x3 = xy1 * cosf(sectorAngle2);
            float y3 = xy1 * sinf(sectorAngle2);
            float x4 = xy2 * cosf(sectorAngle2);
            float y4 = xy2 * sinf(sectorAngle2);

            float nx1 = x1 / radius;
            float ny1 = y1 / radius;
            float nz1 = z1 / radius;
            float nx2 = x2 / radius;
            float ny2 = y2 / radius;
            float nz2 = z2 / radius;
            float nx3 = x3 / radius;
            float ny3 = y3 / radius;
            float nz3 = z1 / radius;
            float nx4 = x4 / radius;
            float ny4 = y4 / radius;
            float nz4 = z2 / radius;

            vertices.insert(vertices.end(), {x1, y1, z1, nx1, ny1, nz1});
            vertices.insert(vertices.end(), {x2, y2, z2, nx2, ny2, nz2});
            vertices.insert(vertices.end(), {x3, y3, z1, nx3, ny3, nz3});

            vertices.insert(vertices.end(), {x3, y3, z1, nx3, ny3, nz3});
            vertices.insert(vertices.end(), {x2, y2, z2, nx2, ny2, nz2});
            vertices.insert(vertices.end(), {x4, y4, z2, nx4, ny4, nz4});
        }
    }

    return vertices;
}


inline std::vector<float> SPHERE_GEOMETRY = generateSphere(1.0f, 36, 18);


#endif //SPHERE_GEOMETRY_H
