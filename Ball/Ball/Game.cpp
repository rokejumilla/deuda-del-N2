#include "Game.h"
#include "Box2DHelper.h"


Game::Game(int ancho, int alto, std::string titulo) {
    this->ancho = ancho;
    this->alto = alto;

    wnd = new sf::RenderWindow(sf::VideoMode(ancho, alto), titulo);
    wnd->setFramerateLimit(60);
    frameTime = 1.0f / 60.0f;

    SetZoom();
    InitPhysics();
}

void Game::Loop() {
    while (wnd->isOpen()) {
        wnd->clear(sf::Color::Black);
        DoEvents();
        UpdatePhysics();
        DrawGame();
        wnd->display();
    }
}

void Game::DoEvents() {
    sf::Event evt;
    while (wnd->pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            wnd->close();
    }
}

void Game::UpdatePhysics() {
    phyWorld->Step(frameTime, 8, 8);
    phyWorld->ClearForces();
    phyWorld->DebugDraw();
}

void Game::DrawGame() {
    b2Vec2 pos = body->GetPosition();
    sprite.setPosition(pos.x, pos.y);
    wnd->draw(sprite);
}

void Game::SetZoom() {
    sf::View camara;
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara);
}

void Game::InitPhysics() {
    phyWorld = new b2World(b2Vec2(0.0f, 0.0f));

    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    // Suelo
    b2Body* ground = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 1);
    ground->SetTransform(b2Vec2(50, 99), 0);

    // Techo
    b2Body* ceiling = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 1);
    ceiling->SetTransform(b2Vec2(50, 1), 0);

    // Pared izquierda
    b2Body* wallLeft = Box2DHelper::CreateRectangularStaticBody(phyWorld, 1, 100);
    wallLeft->SetTransform(b2Vec2(1, 50), 0);

    // Pared derecha
    b2Body* wallRight = Box2DHelper::CreateRectangularStaticBody(phyWorld, 1, 100);
    wallRight->SetTransform(b2Vec2(99, 50), 0);

    // Pelota
    body = Box2DHelper::CreateCircularDynamicBody(phyWorld, 2.5f, 1.0f, 0.3f, 1.0f);
    body->SetTransform(b2Vec2(50, 50), 0.0f);

    texturaPelota.loadFromFile("Pelota.png");
    sprite.setTexture(texturaPelota);
    sprite.setOrigin(texturaPelota.getSize().x / 2.0f, texturaPelota.getSize().y / 2.0f);
    sprite.setScale(5.0f / texturaPelota.getSize().x, 5.0f / texturaPelota.getSize().y);
}
