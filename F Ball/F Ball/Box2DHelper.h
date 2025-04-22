#pragma once
#include <Box2D/Box2D.h>

class Box2DHelper {
public:
    static b2Body* CreateDynamicBody(b2World* world) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_dynamicBody;
        bodyDef.position.Set(0.0f, 0.0f);
        return world->CreateBody(&bodyDef);
    }

    static b2Body* CreateStaticBody(b2World* world) {
        b2BodyDef bodyDef;
        bodyDef.type = b2_staticBody;
        bodyDef.position.Set(0.0f, 0.0f);
        return world->CreateBody(&bodyDef);
    }

    static b2Body* CreateRectangularStaticBody(b2World* world, float width, float height) {
        b2Body* body = CreateStaticBody(world);
        b2PolygonShape shape;
        shape.SetAsBox(width / 2.0f, height / 2.0f);
        b2FixtureDef fixDef;
        fixDef.shape = &shape;
        body->CreateFixture(&fixDef);
        return body;
    }

    static b2Body* CreateCircularDynamicBody(b2World* world, float radius, float density, float friction, float restitution) {
        b2Body* body = CreateDynamicBody(world);
        b2CircleShape circle;
        circle.m_radius = radius;
        b2FixtureDef fixDef;
        fixDef.shape = &circle;
        fixDef.density = density;
        fixDef.friction = friction;
        fixDef.restitution = restitution;
        body->CreateFixture(&fixDef);
        return body;
    }

    static b2DistanceJoint* CreateDistanceJoint(b2World* world, b2Body* a, b2Vec2 anchorA, b2Body* b, b2Vec2 anchorB, float length, float freq, float damp) {
        b2DistanceJointDef jointDef;
        jointDef.Initialize(a, b, anchorA, anchorB);
        jointDef.length = length;
        b2LinearStiffness(jointDef.stiffness, jointDef.damping, freq, damp, jointDef.bodyA, jointDef.bodyB);
        return (b2DistanceJoint*)world->CreateJoint(&jointDef);
    }
};
