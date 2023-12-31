#pragma once
#ifndef SFML_STATIC
#define SFML_STATIC
#endif // !SFML_STATIC

#include <SFML/Graphics.hpp>
#include "Boundary.h"
class Ray : public sf::Drawable
{
	sf::Vector2f _position;
	sf::Vector2f _TrigComponents; // direction
	float _angle;
	sf::Vertex lines[2];

public:

	Ray();
	Ray(sf::Vector2f pos, float angle);

	void SetPosition(sf::Vector2f pos);
	sf::Vector2f GetPosition();
	void SetAngle(float _angle);
	float GetAngle();

	sf::Vector2f cast(Boundary b);
	float castDistance(Boundary b);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

