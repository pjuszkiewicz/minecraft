// https://learnopengl.com/code_viewer_gh.php?code=includes/learnopengl/shader.h
#ifndef SHADER_H
#define SHADER_H

#include "../../../vendor/glad/glad.h"
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

/**
 * @brief Klasa reprezentująca program shaderów.
 *
 * Klasa odpowiada za ładowanie, kompilację oraz ustawianie uniformów w shaderach.
 */
class Shader {
public:
    /// @brief Identyfikator programu shaderów w OpenGL.
    unsigned int ID;

    /**
     * @brief Konstruktor klasy Shader.
     *
     * Ładuje i kompiluje shadery z podanych ścieżek do plików źródłowych.
     *
     * @param vertexPath   Ścieżka do pliku z kodem źródłowym vertex shadera.
     * @param fragmentPath Ścieżka do pliku z kodem źródłowym fragment shadera.
     */
    Shader(const char *vertexPath, const char *fragmentPath);

    /**
     * @brief Aktywuje program shaderów.
     *
     * Ustawia program shaderów jako aktywny, aby mógł być używany przy renderowaniu.
     */
    void use() const;

    /**
     * @brief Ustawia uniform typu bool w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wartość logiczna do ustawienia.
     */
    void setBool(const std::string &name, bool value) const;

    /**
     * @brief Ustawia uniform typu int w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wartość całkowita do ustawienia.
     */
    void setInt(const std::string &name, int value) const;

    /**
     * @brief Ustawia uniform typu float w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wartość zmiennoprzecinkowa do ustawienia.
     */
    void setFloat(const std::string &name, float value) const;

    /**
     * @brief Ustawia uniform typu vec2 w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wektor 2-elementowy glm::vec2 do ustawienia.
     */
    void setVec2(const std::string &name, const glm::vec2 &value) const;

    /**
     * @brief Ustawia uniform typu vec2 w shaderze przy użyciu osobnych komponentów.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param x    Wartość składowej X.
     * @param y    Wartość składowej Y.
     */
    void setVec2(const std::string &name, float x, float y) const;

    /**
     * @brief Ustawia uniform typu vec3 w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wektor 3-elementowy glm::vec3 do ustawienia.
     */
    void setVec3(const std::string &name, const glm::vec3 &value) const;

    /**
     * @brief Ustawia uniform typu vec3 w shaderze przy użyciu osobnych komponentów.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param x    Wartość składowej X.
     * @param y    Wartość składowej Y.
     * @param z    Wartość składowej Z.
     */
    void setVec3(const std::string &name, float x, float y, float z) const;

    /**
     * @brief Ustawia uniform typu vec4 w shaderze.
     *
     * @param name  Nazwa uniformu w shaderze.
     * @param value Wektor 4-elementowy glm::vec4 do ustawienia.
     */
    void setVec4(const std::string &name, const glm::vec4 &value) const;

    /**
     * @brief Ustawia uniform typu vec4 w shaderze przy użyciu osobnych komponentów.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param x    Wartość składowej X.
     * @param y    Wartość składowej Y.
     * @param z    Wartość składowej Z.
     * @param w    Wartość składowej W.
     */
    void setVec4(const std::string &name, float x, float y, float z, float w) const;

    /**
     * @brief Ustawia uniform typu mat2 w shaderze.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param mat  Macierz 2x2 (glm::mat2) do ustawienia.
     */
    void setMat2(const std::string &name, const glm::mat2 &mat) const;

    /**
     * @brief Ustawia uniform typu mat3 w shaderze.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param mat  Macierz 3x3 (glm::mat3) do ustawienia.
     */
    void setMat3(const std::string &name, const glm::mat3 &mat) const;

    /**
     * @brief Ustawia uniform typu mat4 w shaderze.
     *
     * @param name Nazwa uniformu w shaderze.
     * @param mat  Macierz 4x4 (glm::mat4) do ustawienia.
     */
    void setMat4(const std::string &name, const glm::mat4 &mat) const;

private:
    /**
     * @brief Sprawdza błędy kompilacji i linkowania shaderów.
     *
     * Funkcja pomocnicza, która sprawdza czy wystąpiły błędy podczas kompilacji lub linkowania
     * shaderów, oraz wypisuje komunikaty błędów na standardowe wyjście.
     *
     * @param shader Identyfikator shadera lub programu shaderów.
     * @param type   Typ shadera (np. "VERTEX", "FRAGMENT" lub "PROGRAM").
     */
    static void checkCompileErrors(GLuint shader, std::string type);
};

#endif
