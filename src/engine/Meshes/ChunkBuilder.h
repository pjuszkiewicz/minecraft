//
// Created by piotr on 11.01.25.
//

#ifndef CHUNKBUILDER_H
#define CHUNKBUILDER_H

#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../World/Chunk.h"
#include "../Renderer/Texture.h"

/// Buduje meshe chunków
class ChunkBuilder {
public:
    std::vector<glm::mat4> *positions; /// Macierze pozycji instancji ścian
    std::vector<glm::vec2> *textures; /// Kordynaty uv tekstury z atlasu

    Chunk chunk; /// Chunk do zbudowania
    Chunk *forward; /// Chunk z przodu
    Chunk *back; /// Chunk z tyłu
    Chunk *left; /// Chunk z lewej
    Chunk *right; /// Chunk z prawej

    /// Tworzy wektory i rozpoczyna aktualizacje chunka
    /// @param chunk Chunk do zbudowania
    /// @param forward Chunk z przodu
    /// @param back Chunk z tyłu
    /// @param left Chunk z lewej
    /// @param right Chunk z prawej
    ChunkBuilder(
        const Chunk &chunk,
        Chunk *forward,
        Chunk *back,
        Chunk *left,
        Chunk *right
    ) : chunk(chunk), forward(forward), back(back), left(left), right(right) {

        this->positions = new std::vector<glm::mat4>();
        this->textures = new std::vector<glm::vec2>();
        updateChunk();
    };

    /// Aktualizuje każdy blok
    void updateChunk();

    /// Sprawdza które ściany należy rysować
    void updateBlock(
        const Chunk &chunk, int x, int y, int z
    );

    /// Dodaje górną ściane
    /// @param block blok którego sciana ma być dodana
    void addTopFace(Block block);

    /// Dodaje dolną ściane
    /// @param block blok którego sciana ma być dodana
    void addBottomFace(Block block);

    /// Dodaje lewą ściane
    /// @param block blok którego sciana ma być dodana
    /// @param isTopColliding czy blok koliduje z blokiem na górze
    void addLeftFace(Block block, bool isTopColliding) const;

    /// Dodaje prawą ściane
    /// @param block blok którego sciana ma być dodana
    /// @param isTopColliding czy blok koliduje z blokiem na górze
    void addRightFace(Block block, bool isTopColliding) const;

    /// Dodaje przednią ściane
    /// @param block blok którego sciana ma być dodana
    /// @param isTopColliding czy blok koliduje z blokiem na górze
    void addFrontFace(Block block, bool isTopColliding) const;

    /// Dodaje tylnią ściane
    /// @param block blok którego sciana ma być dodana
    /// @param isTopColliding czy blok koliduje z blokiem na górze
    void addBackFace(Block block, bool isTopColliding);
};


#endif //CHUNKBUILDER_H
