#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <GLFW/glfw3.h>
class InstancedMesh {
private:
    unsigned int VBO, instanceVBO, visibilityVBO;
    std::vector<glm::vec3> *positions;
    std::vector<uint8_t> *faces;

public:
    unsigned int VAO;
    InstancedMesh();
    void draw();
    void setPositions(std::vector<glm::vec3>* positions);
};



#endif //MESH_H