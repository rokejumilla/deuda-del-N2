#include "TwoBallsGame.h"
#include <iostream> 

TwoBallsGame::TwoBallsGame(int ancho, int alto, std::string titulo) {
    window = new sf::RenderWindow(sf::VideoMode(ancho, alto), titulo);
    window->setFramerateLimit(60);

    SetZoom();
    InitPhysics();
}

void TwoBallsGame::SetZoom() {
    sf::View view;
    view.setSize(100.0f, 100.0f);
    view.setCenter(50.0f, 50.0f);
    window->setView(view);
}

void TwoBallsGame::InitPhysics() {
    world = new b2World(b2Vec2(0.0f, 9.8f));
    debugRenderer = new SFMLRenderer(window);
    debugRenderer->SetFlags(UINT_MAX);
    world->SetDebugDraw(debugRenderer);

    // Cargar textura de la pelota
    if (!texturePelota.loadFromFile("Pelota.png")) {
        std::cout << "Error al cargar Pelota.png" << std::endl;
    }
    else {
        spritePelota.setTexture(texturePelota);
    }

    // Crear pelotas físicas
    pelota1 = Box2DHelper::CreateCircularDynamicBody(world, 5, 1.0f, 0.3f, 0.8f);
    pelota1->SetTransform(b2Vec2(40.0f, 40.0f), 0.0f);

    pelota2 = Box2DHelper::CreateCircularDynamicBody(world, 5, 1.0f, 0.3f, 0.8f);
    pelota2->SetTransform(b2Vec2(60.0f, 40.0f), 0.0f);

    // Conectar con resorte
    Box2DHelper::CreateDistanceJoint(
        world,
        pelota1, pelota1->GetWorldCenter(),
        pelota2, pelota2->GetWorldCenter(),
        20.0f, 2.0f, 0.3f
    );

    // Cuerpo fantasma para el MouseJoint
    mouseBody = Box2DHelper::CreateStaticBody(world);
}

void TwoBallsGame::Loop() {
    while (window->isOpen()) {
        window->clear(sf::Color::White);
        DoEvents();
        UpdatePhysics();
        DrawGame();
        window->display();
    }
}

void TwoBallsGame::UpdatePhysics() {
    world->Step(1.0f / 60.0f, 8, 8);
    world->ClearForces();
    world->DebugDraw();
}

void TwoBallsGame::DrawGame() {
    // Dibuja pelota 1
    b2Vec2 pos1 = pelota1->GetPosition();
    spritePelota.setPosition(pos1.x, pos1.y);
    window->draw(spritePelota);

    // Dibuja pelota 2
    b2Vec2 pos2 = pelota2->GetPosition();
    spritePelota.setPosition(pos2.x, pos2.y);
    window->draw(spritePelota);
}

void TwoBallsGame::DoEvents() {
    sf::Event evt;
    while (window->pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            window->close();

        else if (evt.type == sf::Event::MouseButtonPressed) {
            sf::Vector2f worldPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
            b2Vec2 p(worldPos.x, worldPos.y);
            b2Body* body = nullptr;

            if (pelota1->GetFixtureList()->TestPoint(p))
                body = pelota1;
            else if (pelota2->GetFixtureList()->TestPoint(p))
                body = pelota2;

            if (body) {
                b2MouseJointDef mjDef;
                mjDef.bodyA = mouseBody;
                mjDef.bodyB = body;
                mjDef.target = p;
                mjDef.maxForce = 1000.0f * body->GetMass();
                mjDef.dampingRatio = 0.5f;
                mouseJoint = (b2MouseJoint*)world->CreateJoint(&mjDef);
                body->SetAwake(true);
            }
        }

        else if (evt.type == sf::Event::MouseButtonReleased) {
            if (mouseJoint) {
                world->DestroyJoint(mouseJoint);
                mouseJoint = nullptr;
            }
        }
    }

    // Si el mouse está presionando una pelota, actualiza la posición del mouseJoint
    if (mouseJoint) {
        sf::Vector2f worldPos = window->mapPixelToCoords(sf::Mouse::getPosition(*window));
        mouseJoint->SetTarget(b2Vec2(worldPos.x, worldPos.y));
    }
}
