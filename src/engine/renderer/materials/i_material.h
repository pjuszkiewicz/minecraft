//
// Created by piotr on 16.02.25.
//

#ifndef I_MATERIAL_H
#define I_MATERIAL_H

#include "../shader.h"

class IMaterial{
  public:
    Shader *shader;

    virtual void updateUniforms() const = 0;
    virtual void updateProjections(
        const glm::mat4 &projection,
        const glm::mat4 &view,
        const glm::mat4 &model,
        const glm::vec3 &viewPos
    ) const {
        shader->setMat4("projection", projection);
        shader->setMat4("view", view);
        shader->setMat4("model", model);

        shader->setVec3("viewPos", viewPos);
    }

    virtual void use() const {
        updateUniforms();
        shader->use();
    }
};

#endif //I_MATERIAL_H
