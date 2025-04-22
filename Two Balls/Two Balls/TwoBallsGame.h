#pragma once

#include <SFML/Graphics.hpp>
#include <Box2D/Box2D.h>
#include "SFMLRenderer.h"
#include "Box2DHelper.h"

class TwoBallsGame {
private:
    sf::RenderWindow* window;
    b2World* world;
    SFMLRenderer* debugRenderer;

    b2Body* pelota1;
    b2Body* pelota2;
    b2MouseJoint* mouseJoint = nullptr;
    b2Body* mouseBody;

    sf::Texture texturePelota;
    sf::Sprite spritePelota;

public:
    TwoBallsGame(int ancho, int alto, std::string titulo);
    void Loop();
    void InitPhysics();
    void UpdatePhysics();
    void DrawGame();
    void DoEvents();
    void SetZoom();
};
