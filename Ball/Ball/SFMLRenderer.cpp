#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(sf::RenderWindow* window) {
    wnd = window;
}

SFMLRenderer::~SFMLRenderer() {}

sf::Color SFMLRenderer::box2d2SFMLColor(const b2Color& _color) {
    return sf::Color(_color.r * 255, _color.g * 255, _color.b * 255);
}

void SFMLRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
    polygon.setOutlineColor(box2d2SFMLColor(color));
    polygon.setFillColor(sf::Color(0, 0, 0, 0));
    wnd->draw(polygon);
}

void SFMLRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, sf::Vector2f(vertices[i].x, vertices[i].y));
    polygon.setFillColor(box2d2SFMLColor(color));
    wnd->draw(polygon);
}

void SFMLRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setOutlineColor(box2d2SFMLColor(color));
    circle.setFillColor(sf::Color(0, 0, 0, 0));
    wnd->draw(circle);
}

void SFMLRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2&, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setFillColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}

void SFMLRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), box2d2SFMLColor(color)),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), box2d2SFMLColor(color))
    };
    wnd->draw(line, 2, sf::Lines);
}

void SFMLRenderer::DrawTransform(const b2Transform& xf) {}

void SFMLRenderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    sf::CircleShape circle(size);
    circle.setOrigin(size, size);
    circle.setPosition(p.x, p.y);
    circle.setFillColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}
