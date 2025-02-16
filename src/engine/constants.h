//
// Created by Piotr Juszkiewicz on 09/01/2025.
//

#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

/// @brief Szerokość ekranu w pikselach.
constexpr int SCREEN_WIDTH = 1600;

/// @brief Wysokość ekranu w pikselach.
constexpr int SCREEN_HEIGHT = 900;

/// @brief Odległość renderowania świata w chunkach.
constexpr int RENDER_DISTANCE = 10;

/// @brief Maksymalna odległość, z której gracz może niszczyć bloki.
constexpr float MAX_BREAK_DISTANCE = 10.0f;

/// @brief Czas trwania pełnego cyklu dnia w sekundach.
constexpr float DAY_CYCLE = 25.0f;


#endif //CONSTANTS_H
