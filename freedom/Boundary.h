#pragma once
#include <SFML/Graphics.hpp>
class Boundary : public sf::Drawable // intersects ray
{
public:
	sf::Vertex lines[2];
	Boundary() : lines()
	{
		lines[0].color = sf::Color::White;
		lines[1].color = sf::Color::White;
	}
	Boundary(sf::Vector2f a, sf::Vector2f b) : lines()
	{
		lines[0].position = a;
		lines[1].position = b;
		lines[0].color = sf::Color::White;
		lines[1].color = sf::Color::White;
	}

	void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(lines, 2, sf::Lines, states);
	}
};

