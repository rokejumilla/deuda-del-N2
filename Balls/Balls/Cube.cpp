#include "Cube.h"

using namespace sf;

Cube::Cube(int ancho, int alto, std::string titulo)
{
    this->ancho = ancho;
    this->alto = alto;
    wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
    wnd->setFramerateLimit(60);
    fps = 60;
    frameTime = 1.0f / fps;
    SetZoom();
    InitPhysics();
}

void Cube::Loop()
{
    while (wnd->isOpen()) {
        wnd->clear(Color::Black);
        DoEvents();
        UpdatePhysics();
        DrawGame();
        wnd->display();
    }
}

void Cube::InitPhysics()
{
    phyWorld = new b2World(b2Vec2(0.0f, 0.0f)); // sin gravedad
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    bodyCube = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 10, 10, 1.0f, 0.3f, 0.1f);
    bodyCube->SetTransform(b2Vec2(50.0f, 50.0f), 0.0f);
}

void Cube::DoEvents()
{
    Event evt;
    while (wnd->pollEvent(evt)) {
        if (evt.type == Event::Closed)
            wnd->close();
    }

    b2Vec2 fuerza(0.0f, 0.0f);
    float fuerzaMagnitud = 30.0f;

    if (Keyboard::isKeyPressed(Keyboard::Up))
        fuerza.y -= fuerzaMagnitud;
    if (Keyboard::isKeyPressed(Keyboard::Down))
        fuerza.y += fuerzaMagnitud;
    if (Keyboard::isKeyPressed(Keyboard::Left))
        fuerza.x -= fuerzaMagnitud;
    if (Keyboard::isKeyPressed(Keyboard::Right))
        fuerza.x += fuerzaMagnitud;

    bodyCube->ApplyForceToCenter(fuerza, true);
}

void Cube::UpdatePhysics()
{
    phyWorld->Step(frameTime, 8, 8);
    phyWorld->ClearForces();
    phyWorld->DebugDraw();
}

void Cube::DrawGame()
{
    // Dibujo físico usando SFMLRenderer
}

void Cube::SetZoom()
{
    View camara;
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara);
}
