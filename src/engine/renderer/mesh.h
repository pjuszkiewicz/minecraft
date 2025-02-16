#ifndef MESH_H
#define MESH_H

#include "../../../vendor/glad/glad.h"
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../renderer/geometry/cube_geometry.h"
#include <GLFW/glfw3.h>

class Mesh {
    unsigned int _vbo;
    int _verticesCount;

public:
    unsigned int vao;
    Mesh(std::vector<float> *geometry);
    void draw() const;
};


#endif //MESH_H
