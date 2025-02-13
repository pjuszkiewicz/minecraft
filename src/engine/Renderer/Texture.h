#ifndef TEXTURE_H
#define TEXTURE_H

#include "../../../vendor/glad/glad.h"
#include "../../../vendor/stb_image.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Texture {
public:
    /// @brief Identyfikator tekstury w OpenGL.
    unsigned int ID;

    /**
     * @brief Wczytuje teksturę z pliku.
     *
     * Konstruktor wczytuje teksturę znajdującą się pod podaną ścieżką i ustawia jej format.
     *
     * @param path Ścieżka do pliku z teksturą.
     * @param format Format tekstury (np. GL_RGB, GL_RGBA).
     */
    Texture(const char *path, int format);

    /**
     * @brief Binduje teksturę w OpenGL.
     *
     * Ustawia teksturę jako aktywną na określonej jednostce tekstur.
     *
     * @param textureUnit Numer jednostki tekstur, na której tekstura ma być aktywna.
     */
    void use(int textureUnit) const;

    /**
     * @brief Zwraca wektor współrzędnych UV dla bloku.
     *
     * Funkcja statyczna, która oblicza i zwraca współrzędne UV na podstawie identyfikatora bloku oraz
     * pozycji (ui, vi) w atlasie tekstur.
     *
     * @param blockID Identyfikator bloku.
     * @param ui Pozycja w poziomie (u) w atlasie tekstur.
     * @param vi Pozycja w pionie (v) w atlasie tekstur.
     * @return glm::vec2 Wektor współrzędnych UV.
     */
    static glm::vec2 getUVForBlock(int blockID, int ui, int vi);
};

#endif
