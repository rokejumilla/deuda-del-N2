#pragma once
#include <Box2D/Box2D.h>

class Box2DHelper {
public:
    static b2Body* CreateDynamicBody(b2World* phyWorld) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 0.0f);
        return phyWorld->CreateBody(&bodyDef);
    }

    static b2Body* CreateStaticBody(b2World* phyWorld) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(0.0f, 0.0f);
        return phyWorld->CreateBody(&bodyDef);
    }

    static b2Body* CreateRectangularStaticBody(b2World* phyWorld, float sizeX, float sizeY) {
        b2Body* body = CreateStaticBody(phyWorld);
        b2PolygonShape shape;
        shape.SetAsBox(sizeX / 2.0f, sizeY / 2.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = 0.0f;
        fixtureDef.friction = 0.0f;
        fixtureDef.restitution = 1.0f;
        body->CreateFixture(&fixtureDef);
        return body;
    }

    static b2Body* CreateCircularDynamicBody(b2World* phyWorld, float radius, float density, float friction, float restitution) {
        b2Body* body = CreateDynamicBody(phyWorld);
        b2CircleShape shape;
        shape.m_radius = radius;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = &shape;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        body->CreateFixture(&fixtureDef);
        return body;
    }
};
