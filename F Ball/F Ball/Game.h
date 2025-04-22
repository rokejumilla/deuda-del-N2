#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"
#include "Avatar.h"

using namespace sf;

class Game {
private:
    RenderWindow* wnd;
    int ancho, alto;
    float frameTime;
    int fps = 60;
    Color clearColor = Color::Black;

    b2World* phyWorld;
    SFMLRenderer* debugRender;

    b2Body* pelota;
    Avatar* avatarPelota;

    Texture texturaPelota;

public:
    Game(int ancho, int alto, std::string titulo);
    void Loop();
    void InitPhysics();
    void UpdatePhysics();
    void DoEvents();
    void DrawGame();
    void SetZoom();
};
