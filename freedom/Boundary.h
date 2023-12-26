#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
class Boundary : public sf::Drawable // intersects ray
{
public:
	sf::Vertex lines[2];
	Boundary();
	Boundary(sf::Vector2f a, sf::Vector2f b);

	void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

