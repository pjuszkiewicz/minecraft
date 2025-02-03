#ifndef RENDERER_H
#define RENDERER_H

#include "../../lib/Renderer/Texture.h"
#include "../../lib/Map/PairHash.h"
#include "../../lib/Renderer/Shader.h"
#include "../../lib/Player/Player.h"
#include "../../lib/World/Chunk.h"
#include <unordered_map>

#include <vector>

#include "../Meshes/ChunkBuilder.h"
#include "../Meshes/CrosshairMesh.h"
#include "../Meshes/ChunkMesh.h"
#include "../Meshes/Mesh.h"
#include "../Constants.h"
#include "../../../vendor/glad/glad.h"

#include <glm/glm.hpp> // Używając GLM dla vec3
#include <cmath>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "../Materials/SunAndMoonMaterial.h"

#include "../GameObjects/CrosshairObject.h"
#include "../GameObjects/SunAndMoon.h"
#include "../GameObjects/WorldObject.h"
#include "../Materials/CrosshairMaterial.h"
#include "../Materials/WorldMaterial.h"

class Renderer {
public:
    /// @brief Obiekt reprezentujący słońce i księżyc.
    SunAndMoon sunAndMoon;

    /// @brief Obiekt reprezentujący elementy świata.
    WorldObject worldObject;

    /// @brief Obiekt reprezentujący celownik.
    CrosshairObject crosshairObject;

    /**
     * @brief Konstruktor klasy Renderer.
     *
     * Inicjalizuje obiekt renderera.
     */
    Renderer();

    /**
     * @brief Czyści ekran.
     *
     * Funkcja czyści ekran kolorem zwróconym przez DateTime::getSkyColor().
     */
    void Clear();

    /**
     * @brief Aktualizuje projekcję i rysuje obiekty.
     *
     * Na podstawie pozycji gracza aktualizuje macierze projekcji, a następnie rysuje obiekty sceny.
     *
     * @param player Obiekt gracza, którego pozycja i kamera wpływają na ustawienia projekcji i rysowanych obiektów.
     */
    void Draw(const Player &player);

    /**
     * @brief Aktualizuje projekcję.
     *
     * Uaktualnia macierze projekcji na podstawie pozycji i rotacji kamery gracza.
     *
     * @param player Obiekt gracza, którego dane (pozycja oraz rotacja kamery) są wykorzystywane przy aktualizacji projekcji.
     */
    void UpdateProjection(const Player &player) const;

};

#endif //RENDERER_H
