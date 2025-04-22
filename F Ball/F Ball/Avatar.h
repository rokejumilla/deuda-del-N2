#pragma once

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class Avatar {
private:
    sf::Sprite* m_pSprite = nullptr;
    b2Body* m_pCuerpo = nullptr;
    b2Vec2 m_posAux = b2Vec2(0.0f, 0.0f);
    float m_angAux = 0.0f;

public:
    Avatar(b2Body* pCuerpo, sf::Sprite* pSprite);
    ~Avatar();

    operator b2Body* ();
    void Actualizar();
    void Dibujar(sf::RenderWindow& RW);
    b2Vec2 GetPosition();
    b2Body& GetCuerpo();
    sf::Sprite& GetSprite();
    void SetPosition(b2Vec2 position);
    void AplicarFuerza(b2Vec2& fuerza, b2Vec2& origen = b2Vec2(0.0f, 0.0f));
    void AplicarImpulso(b2Vec2& impulso, b2Vec2& origen = b2Vec2(0.0f, 0.0f));
};
