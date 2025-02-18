#ifndef SPHERE_GEOMETRY_H
#define SPHERE_GEOMETRY_H
#include <vector>
#include <cmath>
#include <algorithm>

#include <vector>
#include <cmath>
#include <algorithm>

inline std::vector<float> generateSphere(float radius, int subdivisionLevel) {
    const float PI = 3.14159265359f;
    const float PHI = (1.0f + sqrtf(5.0f)) / 2.0f; // Złota liczba
    std::vector<float> vertices;

    // Początkowy dwudziestościan foremny (12 wierzchołków)
    std::vector<std::vector<float>> baseVertices = {
        {-1,  PHI,  0}, {1,  PHI,  0}, {-1, -PHI,  0}, {1, -PHI,  0},
        {0, -1,  PHI}, {0, 1,  PHI}, {0, -1, -PHI}, {0, 1, -PHI},
        {PHI,  0, -1}, {PHI,  0,  1}, {-PHI,  0, -1}, {-PHI,  0,  1}
    };

    // Normalizacja i skalowanie do promienia kuli
    for (auto& v : baseVertices) {
        float length = sqrtf(v[0]*v[0] + v[1]*v[1] + v[2]*v[2]);
        v[0] = (v[0] / length) * radius;
        v[1] = (v[1] / length) * radius;
        v[2] = (v[2] / length) * radius;
    }

    // Początkowe trójkąty dwudziestościanu
    std::vector<std::vector<int>> baseTriangles = {
        {0, 11, 5}, {0, 5, 1}, {0, 1, 7}, {0, 7, 10}, {0, 10, 11},
        {1, 5, 9}, {5, 11, 4}, {11, 10, 2}, {10, 7, 6}, {7, 1, 8},
        {3, 9, 4}, {3, 4, 2}, {3, 2, 6}, {3, 6, 8}, {3, 8, 9},
        {4, 9, 5}, {2, 4, 11}, {6, 2, 10}, {8, 6, 7}, {9, 8, 1}
    };

    // Funkcja do podziału trójkątów
    auto subdivide = [&](std::vector<std::vector<float>>& v, std::vector<std::vector<int>>& faces) {
        std::vector<std::vector<int>> newFaces;
        std::vector<std::vector<float>> newVertices = v;

        auto getMidpoint = [&](int a, int b) -> int {
            std::vector<float> mid = {
                (v[a][0] + v[b][0]) / 2.0f,
                (v[a][1] + v[b][1]) / 2.0f,
                (v[a][2] + v[b][2]) / 2.0f
            };
            float len = sqrtf(mid[0]*mid[0] + mid[1]*mid[1] + mid[2]*mid[2]);
            mid[0] = (mid[0] / len) * radius;
            mid[1] = (mid[1] / len) * radius;
            mid[2] = (mid[2] / len) * radius;
            newVertices.push_back(mid);
            return (int)newVertices.size() - 1;
        };

        for (auto& face : faces) {
            int a = face[0], b = face[1], c = face[2];
            int ab = getMidpoint(a, b);
            int bc = getMidpoint(b, c);
            int ca = getMidpoint(c, a);

            newFaces.push_back({a, ab, ca});
            newFaces.push_back({b, bc, ab});
            newFaces.push_back({c, ca, bc});
            newFaces.push_back({ab, bc, ca});
        }

        v = newVertices;
        faces = newFaces;
    };

    // Podział trójkątów na wyższe poziomy szczegółowości
    std::vector<std::vector<float>> finalVertices = baseVertices;
    std::vector<std::vector<int>> finalTriangles = baseTriangles;
    for (int i = 0; i < subdivisionLevel; i++) {
        subdivide(finalVertices, finalTriangles);
    }

    // Generowanie wierzchołków z poprawionymi UV
    // Każdy trójkąt jest przetwarzany osobno
    for (auto& face : finalTriangles) {
        // Tymczasowa tablica dla 3 wierzchołków (każdy: pos(3), normal(3), uv(2))
        float tri[3][8];
        for (int i = 0; i < 3; i++) {
            float x = finalVertices[face[i]][0];
            float y = finalVertices[face[i]][1];
            float z = finalVertices[face[i]][2];
            float nx = x / radius;
            float ny = y / radius;
            float nz = z / radius;
            // Obliczamy kąt theta na podstawie x i z
            float theta = atan2f(z, x);
            if (theta < 0.0f) theta += 2.0f * PI;
            float u = theta / (2.0f * PI);
            float v = 0.5f - (asinf(ny) / PI);
            tri[i][0] = x;  tri[i][1] = y;  tri[i][2] = z;
            tri[i][3] = nx; tri[i][4] = ny; tri[i][5] = nz;
            tri[i][6] = u;  tri[i][7] = v;
        }
        // Sprawdzenie szwu: jeśli różnica między max a min u > 0.5, to korygujemy
        float u0 = tri[0][6], u1 = tri[1][6], u2 = tri[2][6];
        float min_u = std::min({u0, u1, u2});
        float max_u = std::max({u0, u1, u2});
        if (max_u - min_u > 0.5f) {
            for (int i = 0; i < 3; i++) {
                if (tri[i][6] < 0.5f) {
                    tri[i][6] += 1.0f;
                }
            }
        }
        // Dodajemy wierzchołki trójkąta do finalnej listy
        for (int i = 0; i < 3; i++) {
            std::vector<float> tmp = { tri[i][0], tri[i][1], tri[i][2],
                                         tri[i][3], tri[i][4], tri[i][5],
                                         tri[i][6], tri[i][7] };
            vertices.insert(vertices.end(), tmp.begin(), tmp.end());
        }
    }

    return vertices;
}


// inline std::vector<float> SPHERE_GEOMETRY = generateSphere(0.5f, 36, 18);
inline std::vector<float> SPHERE_GEOMETRY = generateSphere(1.0f, 3);


#endif //SPHERE_GEOMETRY_H
