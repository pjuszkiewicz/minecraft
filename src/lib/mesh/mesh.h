#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>

class Mesh{
private:
    unsigned int VBO;
    float* vertices;

public:
    unsigned int VAO;
    Mesh();
    void draw() const;
};




#endif //MESH_H