#include "Character.h"
#include "Box2DHelper.h"

Character::Character(int ancho, int alto, std::string titulo) {
    wnd = new sf::RenderWindow(sf::VideoMode(ancho, alto), titulo);
    wnd->setFramerateLimit(60);
    fps = 60;
    frameTime = 1.0f / fps;

    SetZoom();
    InitPhysics();
}

void Character::SetZoom() {
    sf::View camara;
    camara.setSize(100.0f, 100.0f);
    camara.setCenter(50.0f, 50.0f);
    wnd->setView(camara);
}

void Character::InitPhysics() {
    phyWorld = new b2World(b2Vec2(0.0f, 9.8f));
    debugRender = new SFMLRenderer(wnd);
    debugRender->SetFlags(UINT_MAX);
    phyWorld->SetDebugDraw(debugRender);

    CreateRagdoll();
}

void Character::Loop() {
    while (wnd->isOpen()) {
        wnd->clear(sf::Color::Black);
        DoEvents();
        UpdatePhysics();
        DrawGame();
        wnd->display();
    }
}

void Character::DoEvents() {
    sf::Event evt;
    while (wnd->pollEvent(evt)) {
        if (evt.type == sf::Event::Closed)
            wnd->close();
    }
}

void Character::UpdatePhysics() {
    phyWorld->Step(frameTime, 8, 8);
    phyWorld->ClearForces();
    phyWorld->DebugDraw();
}

void Character::DrawGame() {
    // Nada extra, ya se dibuja todo por DebugDraw
}

void Character::CreateRagdoll() {
    // Crear partes del cuerpo
    b2Body* torso = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 4, 6, 1, 0.3f, 0.2f);
    torso->SetTransform(b2Vec2(50.0f, 40.0f), 0.0f);

    b2Body* head = Box2DHelper::CreateCircularDynamicBody(phyWorld, 2, 1, 0.3f, 0.2f);
    head->SetTransform(b2Vec2(50.0f, 35.0f), 0.0f);

    b2Body* leftArm = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.5f, 5.0f, 1, 0.3f, 0.2f);
    leftArm->SetTransform(b2Vec2(46.5f, 40.0f), 0.0f);

    b2Body* rightArm = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.5f, 5.0f, 1, 0.3f, 0.2f);
    rightArm->SetTransform(b2Vec2(53.5f, 40.0f), 0.0f);

    b2Body* leftLeg = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.5f, 6.0f, 1, 0.3f, 0.2f);
    leftLeg->SetTransform(b2Vec2(48.0f, 48.0f), 0.0f);

    b2Body* rightLeg = Box2DHelper::CreateRectangularDynamicBody(phyWorld, 1.5f, 6.0f, 1, 0.3f, 0.2f);
    rightLeg->SetTransform(b2Vec2(52.0f, 48.0f), 0.0f);

    // Crear joints (resortes)
    Box2DHelper::CreateDistanceJoint(phyWorld, head, head->GetWorldCenter(), torso, b2Vec2(50.0f, 37.5f), 3.0f, 2.0f, 0.7f);
    Box2DHelper::CreateDistanceJoint(phyWorld, leftArm, leftArm->GetWorldCenter(), torso, b2Vec2(48.0f, 40.0f), 3.0f, 2.0f, 0.7f);
    Box2DHelper::CreateDistanceJoint(phyWorld, rightArm, rightArm->GetWorldCenter(), torso, b2Vec2(52.0f, 40.0f), 3.0f, 2.0f, 0.7f);
    Box2DHelper::CreateDistanceJoint(phyWorld, leftLeg, leftLeg->GetWorldCenter(), torso, b2Vec2(49.0f, 45.0f), 4.0f, 2.0f, 0.7f);
    Box2DHelper::CreateDistanceJoint(phyWorld, rightLeg, rightLeg->GetWorldCenter(), torso, b2Vec2(51.0f, 45.0f), 4.0f, 2.0f, 0.7f);

    ragdollBodies = { head, torso, leftArm, rightArm, leftLeg, rightLeg };
}
