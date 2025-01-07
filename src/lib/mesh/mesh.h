#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

class Mesh {
private:
    unsigned int VBO, instanceVBO, visibilityVBO;
    std::vector<glm::vec3> *positions;
    std::vector<uint8_t> *faces;

public:
    unsigned int VAO;
    Mesh();
    void draw();
    void setPositions(std::vector<glm::vec3>* positions);
};



#endif //MESH_H