//
// Created by piotr on 15.01.25.
//

#ifndef DATETIME_H
#define DATETIME_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


/// Obsługa czasu w grze, koloru tła i pozycji słońca
class DateTime {
public:
    /// Zwraca wewnętrzny czas gry na podstawie DAY_CYCLE
    static float getTime();

    /// Zwraca kolor tła na podstawie czasu
    /// @return Zwraca wektor z zmiennymi vec3(r, g, b)
    static glm::vec3 getSkyColor();

    /// Zwraca pozycje słońca zależną od czasu
    /// @return Zwraca wektor z pozycją słońca
    static glm::vec3 getSunPos();

    /// Zwraca pozycje słońca zależną od czasu
    /// @param time czas zwracany w glfwGetTime()
    /// @return Zwraca wektor z pozycją słońca
    static glm::vec3 getSunPos(float time);
};


#endif //DATETIME_H
