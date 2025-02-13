#ifndef GAME_H
#define GAME_H

#include "../../engine/Renderer/Renderer.h"

#include "../World/World.h"
#include "../../engine/Window/Window.h"

/// Główna klasa gry
class Game {
public:
    Window window; /// Wrapper dla okna GLFW
    Renderer renderer; /// Rysuje rzeczy na ekranie
    Player player; /// Obsługuje gracza
    World world; /// Przechowuje i generuje świat

    float deltaTime = 0.0f; /// Czas pomiędzy ostatnio klatką
    float lastFrame = 0.0f; /// Czas ostatniej klatki glfwGetTime()
    float lastFpsTime = 0.0f; /// Czas ostatniej klatki glfwGetTime() do obliczania fps
    int fps = 0; /// Klatki na sekunde

    bool isLeftMousePressed = false; /// Zapobiega ciągłemu niszczeniu klocków
    bool isRightMousePressed = false; /// Zapobiega ciągłemu stawianiu klocków

    /// Uruchamia wątek ładowania świata
    Game();

    /// Wątek dla pętli ładowania chunków, jeżeli chunk jest w polu widzenia tworzy się objekt klasy ChunkBuilder, który generuje dane dla mesh chunka.
    void prepareChunksLoop();

    /// Główna pętla gry, aktualizuje pozycje, rysuje grafike oraz sprawdza inputy.
    void loop();

    /// Aktualizuje różnice czasu między poprzednia klatką
    void updateDeltaTime();

    /// Sprawdza wcisnięte klawisze i podujemuje odpowiednią akcje.
    void processInput();

    /// Niszczy blok na podstawie punktu na który patrzy kamera
    void destroyBlock();

    /// Stawia blok na podstawie punktu na który patrzy kamera
    void createBlock();

    /// Aktualizuje poszczególne chunki po zniszczeniu lub postawieniu bloku
    /// @param chunkX kordynat x chunku
    /// @param chunkZ kordynat z chunku
    void rerenderChunks(int chunkX, int chunkZ);
};

#endif
