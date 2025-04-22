#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(RenderWindow* window) {
    wnd = window;
}

SFMLRenderer::~SFMLRenderer(void) { }

Color SFMLRenderer::box2d2SFMLColor(const b2Color& _color) {
    return Color((Uint8)(_color.r * 255), (Uint8)(_color.g * 255), (Uint8)(_color.b * 255));
}

void SFMLRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon;
    polygon.setFillColor(Color(0, 0, 0, 0)); // transparente
    polygon.setOutlineColor(box2d2SFMLColor(color));
    polygon.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));

    wnd->draw(polygon);
}

void SFMLRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    sf::ConvexShape polygon;
    polygon.setFillColor(box2d2SFMLColor(color));
    polygon.setOutlineColor(box2d2SFMLColor(color));
    polygon.setPointCount(vertexCount);

    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));

    wnd->draw(polygon);
}

void SFMLRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setFillColor(Color(0, 0, 0, 0));
    circle.setOutlineColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}

void SFMLRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2& axis, const b2Color& color) {
    sf::CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setFillColor(box2d2SFMLColor(color));
    circle.setOutlineColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}

void SFMLRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    sf::Vertex line[] = {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), box2d2SFMLColor(color)),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), box2d2SFMLColor(color))
    };
    wnd->draw(line, 2, sf::Lines);
}

void SFMLRenderer::DrawTransform(const b2Transform& xf) {
    const float k_axisScale = 0.4f;
    b2Vec2 p1 = xf.p;
    b2Vec2 p2;

    // Eje X
    p2 = p1 + k_axisScale * xf.q.GetXAxis();
    sf::Vertex redLine[] = {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), Color::Red),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), Color::Red)
    };
    wnd->draw(redLine, 2, sf::Lines);

    // Eje Y
    p2 = p1 + k_axisScale * xf.q.GetYAxis();
    sf::Vertex greenLine[] = {
        sf::Vertex(sf::Vector2f(p1.x, p1.y), Color::Green),
        sf::Vertex(sf::Vector2f(p2.x, p2.y), Color::Green)
    };
    wnd->draw(greenLine, 2, sf::Lines);
}

void SFMLRenderer::DrawPoint(const b2Vec2& p, float size, const b2Color& color) {
    sf::CircleShape circle(size);
    circle.setOrigin(size, size);
    circle.setPosition(p.x, p.y);
    circle.setFillColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}

void SFMLRenderer::DrawString(int x, int y, const char* string, ...) {
    sf::Text text;
    text.setString(string);
    text.setPosition((float)x, (float)y);
    wnd->draw(text);
}

void SFMLRenderer::DrawAABB(b2AABB* aabb, const b2Color& color) {
    auto halfSize = aabb->GetExtents();
    sf::RectangleShape rect(sf::Vector2f(halfSize.x * 2.0f, halfSize.y * 2.0f));
    rect.setOrigin(halfSize.x, halfSize.y);
    rect.setPosition(aabb->GetCenter().x, aabb->GetCenter().y);
    rect.setFillColor(Color(0, 0, 0, 0));
    rect.setOutlineColor(box2d2SFMLColor(color));
    wnd->draw(rect);
}
