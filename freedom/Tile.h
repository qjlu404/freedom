// Deprecated

#pragma once
#ifndef SFML_STATIC
#define SFML_STATIC
#endif // !SFML_STATIC
#include <SFML/Graphics.hpp>
#include <string>
#include <array>
#include "Boundary.h"
class Tile : public sf::Drawable
{
public:
	bool _passable; // true: collision
	float _capital; // true: money made
	sf::Color _color;
	std::string _name;
	sf::RectangleShape tileRect;
	Boundary bounds[4]; // 0 left, 1 bottom, 2 right, 3 top

	void Bounds()
	{
		bounds[0] = Boundary(tileRect.getPosition(),
			tileRect.getPosition() + sf::Vector2f(0, tileRect.getSize().y));

		bounds[1] = Boundary(tileRect.getPosition() + sf::Vector2f(0, tileRect.getSize().y),
			tileRect.getPosition() + tileRect.getSize());


		bounds[2] = Boundary(tileRect.getPosition() + tileRect.getSize(),
			tileRect.getPosition() + sf::Vector2f(tileRect.getSize().x, 0));

		bounds[3] = Boundary(tileRect.getPosition() + sf::Vector2f(tileRect.getSize().x, 0),
			tileRect.getPosition());
	}

	Tile() : _passable(1), _capital(0), _color(100, 75, 30, 255), _name("Tile"), tileRect()
	{
		tileRect.setFillColor(_color);
		tileRect.setOutlineColor(sf::Color::Black);
		Bounds();
	}
	Tile(bool passable, float capital, sf::Color color, std::string name)
	{
		_passable = passable;
		_capital = capital;
		_color = color;
		_name = name;
		tileRect.setFillColor(_color);
		tileRect.setOutlineColor(sf::Color::Black);
		Bounds();
	}
	
	
	
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(tileRect);
		target.draw(bounds[0].lines, 2, sf::Lines, states);
		target.draw(bounds[1].lines, 2, sf::Lines, states);
		target.draw(bounds[2].lines, 2, sf::Lines, states);
		target.draw(bounds[3].lines, 2, sf::Lines, states); 
		
	}
};

