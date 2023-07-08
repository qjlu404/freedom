#include "Boundary.h"

Boundary::Boundary() : lines()
{
	lines[0].color = sf::Color::White;
	lines[1].color = sf::Color::White;
}

Boundary::Boundary(sf::Vector2f a, sf::Vector2f b) : lines()
{
	lines[0].position = a;
	lines[1].position = b;
	lines[0].color = sf::Color::White;
	lines[1].color = sf::Color::White;
}

void Boundary::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(lines, 2, sf::Lines, states);
}

