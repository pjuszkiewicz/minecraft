//
// Created by piotr on 15.01.25.
//

#ifndef DATETIME_H
#define DATETIME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class DateTime {
public:
    static float getTime();
    static glm::vec3 getSkyColor();
    static glm::vec3 getSunPos();
};



#endif //DATETIME_H
