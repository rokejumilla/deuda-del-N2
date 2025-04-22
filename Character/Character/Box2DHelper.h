#pragma once

#include <Box2D/Box2D.h>

class Box2DHelper {
public:

    // Crear cuerpos sin fixtures
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

    static b2Body* CreateKinematicBody(b2World* phyWorld) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_kinematicBody;
        bodyDef.position.Set(0.0f, 0.0f);
        return phyWorld->CreateBody(&bodyDef);
    }

    // Fixtures
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

    static b2FixtureDef CreateCircularFixtureDef(float radius, float density, float friction, float restitution) {
        b2CircleShape* circle = new b2CircleShape();
        circle->m_radius = radius;
        b2FixtureDef fixtureDef;
        fixtureDef.shape = circle;
        fixtureDef.density = density;
        fixtureDef.friction = friction;
        fixtureDef.restitution = restitution;
        return fixtureDef;
    }

    // Crear cuerpos con fixture
    static b2Body* CreateRectangularDynamicBody(b2World* phyWorld, float sizeX, float sizeY, float density, float friction, float restitution) {
        b2Body* body = CreateDynamicBody(phyWorld);
        b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, density, friction, restitution);
        body->CreateFixture(&box);
        return body;
    }

    static b2Body* CreateCircularDynamicBody(b2World* phyWorld, float radius, float density, float friction, float restitution) {
        b2Body* body = CreateDynamicBody(phyWorld);
        b2FixtureDef cir = CreateCircularFixtureDef(radius, density, friction, restitution);
        body->CreateFixture(&cir);
        return body;
    }

    static b2Body* CreateRectangularStaticBody(b2World* phyWorld, float sizeX, float sizeY) {
        b2Body* body = CreateStaticBody(phyWorld);
        b2FixtureDef box = CreateRectangularFixtureDef(sizeX, sizeY, 0.0f, 0.0f, 0.0f);
        body->CreateFixture(&box);
        return body;
    }

    static b2Body* CreateCircularStaticBody(b2World* phyWorld, float radius) {
        b2Body* body = CreateStaticBody(phyWorld);
        b2FixtureDef cir = CreateCircularFixtureDef(radius, 0.0f, 0.0f, 0.0f);
        body->CreateFixture(&cir);
        return body;
    }

    // Crear un DistanceJoint (resorte)
    static b2DistanceJoint* CreateDistanceJoint(b2World* phyWorld,
        b2Body* first, b2Vec2 anchorFirst,
        b2Body* second, b2Vec2 anchorSecond,
        float distance, float frec, float dampRatio)
    {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(first, second, anchorFirst, anchorSecond);
        jointDef.collideConnected = true;
        jointDef.length = distance;
        b2LinearStiffness(jointDef.stiffness, jointDef.damping, frec, dampRatio, jointDef.bodyA, jointDef.bodyB);
        return (b2DistanceJoint*)phyWorld->CreateJoint(&jointDef);
    }
};
