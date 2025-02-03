//
// Created by piotr on 17.01.25.
//

#ifndef MATERIAL_H
#define MATERIAL_H
#include "Shader.h"
#include "Texture.h"


class Material {
public:
    /// Destruktor wirtualny klasy Material.
    virtual ~Material() = default;

    /// @brief Wskaźnik na shader używany przez material.
    Shader *shader;

    /// @brief Wskaźnik na teksturę używaną przez material.
    Texture *texture;

    /**
     * @brief Konstruktor domyślny.
     *
     * Ustawia wskaźniki shader oraz texture na nullptr.
     */
    Material();

    /**
     * @brief Konstruktor inicjujący material.
     *
     * Przypisuje przekazany shader oraz texture do obiektu.
     *
     * @param shader  Wskaźnik na shader, który ma być przypisany.
     * @param texture Wskaźnik na teksturę, która ma być przypisana.
     */
    Material(Shader *shader, Texture *texture);

    /**
     * @brief Binduje material i teksturę w OpenGL.
     *
     * Aktywuje shader i wiąże teksturę z określonym jednostką tekstur.
     *
     * @param textureUnit Numer jednostki tekstur, do której ma być przypięta tekstura.
     */
    void Use(int textureUnit);

    /**
     * @brief Aktualizuje projekcję.
     *
     * Funkcja czysto wirtualna, która powinna być implementowana w klasach pochodnych.
     * Uaktualnia macierze projekcji i widoku oraz uwzględnia pozycję.
     *
     * @param projection Referencja do macierzy projekcji.
     * @param view       Referencja do macierzy widoku.
     * @param pos        Pozycja, która ma być uwzględniona przy aktualizacji.
     */
    virtual void UpdateProjection(glm::mat4 &projection, glm::mat4 &view, const glm::vec3 &pos) = 0;
};


#endif //MATERIAL_H
