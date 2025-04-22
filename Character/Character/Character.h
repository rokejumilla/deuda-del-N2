#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Box2D/Box2D.h"
#include "SFMLRenderer.h"

class Character {
private:
    sf::RenderWindow* wnd;
    b2World* phyWorld;
    SFMLRenderer* debugRender;
    int fps;
    float frameTime;

    std::vector<b2Body*> ragdollBodies;

public:
    Character(int ancho, int alto, std::string titulo);
    void InitPhysics();
    void Loop();
    void DoEvents();
    void UpdatePhysics();
    void DrawGame();
    void SetZoom();
    void CreateRagdoll();
};