#include "Game.h"
#include "Box2DHelper.h"

Game::Game(int ancho, int alto, std::string titulo) : ancho(ancho), alto(alto) {
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setFramerateLimit(fps);
    frameTime = 1.0f / fps;
    SetZoom();
    InitPhysics();
}

void Game::Loop() {
    while (wnd->isOpen()) {
        wnd->clear(clearColor);
        DoEvents();
        UpdatePhysics();
        DrawGame();
        wnd->display();
    }
}

void Game::SetZoom() {
    View camara;
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara);
}

void Game::InitPhysics() {
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    // Cuerpo estático (techo)
    b2Body* techo = Box2DHelper::CreateRectangularStaticBody(phyWorld, 100, 10);
    techo->SetTransform(b2Vec2(50.0f, 5.0f), 0.0f);

    // Cuerpo dinámico (pelota)
    pelota = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5.0f, 1.0f, 0.5f, 0.3f);
    pelota->SetTransform(b2Vec2(50.0f, 25.0f), 0.0f);

    // Crear DistanceJoint (resorte)
    Box2DHelper::CreateDistanceJoint(
        phyWorld,
        pelota, pelota->GetWorldCenter(),
        techo, techo->GetWorldCenter(),
        20.0f, 5.0f, 0.7f
    );

    texturaPelota.loadFromFile("Pelota.png");
    avatarPelota = new Avatar(pelota, new Sprite(texturaPelota));
}

void Game::UpdatePhysics() {
    phyWorld->Step(frameTime, 8, 8);
    phyWorld->ClearForces();
    phyWorld->DebugDraw();
}

void Game::DoEvents() {
    Event evt;
    while (wnd->pollEvent(evt)) {
        if (evt.type == Event::Closed)
            wnd->close();
    }
}

void Game::DrawGame() {
    avatarPelota->Actualizar();
    avatarPelota->Dibujar(*wnd);
}
