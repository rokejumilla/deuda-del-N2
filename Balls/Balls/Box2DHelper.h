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

    static b2FixtureDef CreateRectangularFixtureDef(float sizeX, float sizeY, float density, float friction, float restitution) {
        b2PolygonShape* box = new b2PolygonShape();
        box->SetAsBox(sizeX / 2.0f, sizeY / 2.0f);
        b2FixtureDef fixtureDef;
        fixtureDef.shape = box;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        return fixtureDef;
    }

    static b2Body* CreateRectangularDynamicBody(b2World* phyWorld, float sizeX, float sizeY, float density, float friction, float restitution) {
        b2Body* body = CreateDynamicBody(phyWorld);
        b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, density, friction, restitution);
        body->CreateFixture(&box);
        return body;
    }
};
