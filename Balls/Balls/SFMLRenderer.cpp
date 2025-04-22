#include "SFMLRenderer.h"

SFMLRenderer::SFMLRenderer(RenderWindow* window) {
    wnd = window;
}

Color SFMLRenderer::box2d2SFMLColor(const b2Color& color) {
    return Color(
        static_cast<Uint8>(color.r * 255),
        static_cast<Uint8>(color.g * 255),
        static_cast<Uint8>(color.b * 255)
    );
}

void SFMLRenderer::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));
    polygon.setFillColor(Color(0, 0, 0, 0));
    polygon.setOutlineColor(box2d2SFMLColor(color));
    polygon.setOutlineThickness(0.05f);
    wnd->draw(polygon);
}

void SFMLRenderer::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
    ConvexShape polygon;
    polygon.setPointCount(vertexCount);
    for (int i = 0; i < vertexCount; ++i)
        polygon.setPoint(i, Vector2f(vertices[i].x, vertices[i].y));
    polygon.setFillColor(box2d2SFMLColor(color));
    polygon.setOutlineThickness(0.05f);
    wnd->draw(polygon);
}

void SFMLRenderer::DrawCircle(const b2Vec2& center, float radius, const b2Color& color) {
    CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setFillColor(Color(0, 0, 0, 0));
    circle.setOutlineColor(box2d2SFMLColor(color));
    circle.setOutlineThickness(0.05f);
    wnd->draw(circle);
}

void SFMLRenderer::DrawSolidCircle(const b2Vec2& center, float radius, const b2Vec2&, const b2Color& color) {
    CircleShape circle(radius);
    circle.setOrigin(radius, radius);
    circle.setPosition(center.x, center.y);
    circle.setFillColor(box2d2SFMLColor(color));
    wnd->draw(circle);
}

void SFMLRenderer::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
    Vertex line[] = {
        Vertex(Vector2f(p1.x, p1.y), box2d2SFMLColor(color)),
        Vertex(Vector2f(p2.x, p2.y), box2d2SFMLColor(color))
    };
    wnd->draw(line, 2, Lines);
}

void SFMLRenderer::DrawTransform(const b2Transform& xf) {
    const float axisScale = 0.4f;

    b2Vec2 p1 = xf.p;
    b2Vec2 p2 = p1 + axisScale * xf.q.GetXAxis();
    Vertex redLine[] = {
        Vertex(Vector2f(p1.x, p1.y), Color::Red),
        Vertex(Vector2f(p2.x, p2.y), Color::Red)
    };
    wnd->draw(redLine, 2, Lines);

    p2 = p1 + axisScale * xf.q.GetYAxis();
    Vertex greenLine[] = {
        Vertex(Vector2f(p1.x, p1.y), Color::Green),
        Vertex(Vector2f(p2.x, p2.y), Color::Green)
    };
    wnd->draw(greenLine, 2, Lines);
}

void SFMLRenderer::DrawPoint(const b2Vec2& p, float, const b2Color& color) {
    CircleShape point(0.1f);
    point.setOrigin(0.1f, 0.1f);
    point.setPosition(p.x, p.y);
    point.setFillColor(box2d2SFMLColor(color));
    wnd->draw(point);
}
