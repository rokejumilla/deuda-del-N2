#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"

class Game {
private:
    int ancho, alto;
    sf::RenderWindow* wnd;
    sf::Texture texturaPelota;
    sf::Sprite sprite;

    b2World* phyWorld;
    SFMLRenderer* debugRender;

    float frameTime;

    b2Body* body;

public:
    Game(int ancho, int alto, std::string titulo);
    void Loop();
    void DoEvents();
    void UpdatePhysics();
    void DrawGame();
    void SetZoom();
    void InitPhysics();
};
