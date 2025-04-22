#pragma once

#include <SFML/Graphics.hpp>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"

class Cube {
private:
    int ancho, alto;
    sf::RenderWindow* wnd;
    b2World* phyWorld;
    SFMLRenderer* debugRender;

    b2Body* bodyCube;
    float frameTime;
    int fps;

public:
    Cube(int ancho, int alto, std::string titulo);
    void Loop();
    void InitPhysics();
    void DoEvents();
    void UpdatePhysics();
    void DrawGame();
    void SetZoom();
};
