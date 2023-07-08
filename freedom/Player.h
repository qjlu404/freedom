#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
// player data model
class Player
{
	sf::Vector2f _pos;

	float _angle;
	float xComponent, yComponent;
public:
	Player() : _pos(0, 0), _angle((float)(rand()%359)), xComponent(0),yComponent(0)
	{
	}

	void setPosition(sf::Vector2f pos)
	{
		this->_pos = pos;
	}
	sf::Vector2f getPosition()
	{
		return _pos;
	}

	void setAngle(float angle)
	{
		if (angle < 0)
		{
			_angle = angle + 360;
		}
		if (angle >= 360)
		{
			_angle = angle - 360;
		} 
		// keep it terminal
		_angle = angle;
	}
	float getAngle()
	{
		return _angle;
	}

	sf::Vector2f getTrigComponent()
	{
		float tAngle = _angle + 270;
		if (tAngle < 0) tAngle += 360;
		if (tAngle >= 360) tAngle -= 360;
		yComponent = sin(3.14f * (tAngle / 180));
		xComponent = cos(3.14f * (tAngle / 180));
		return sf::Vector2f(xComponent, yComponent);
	}

	void turn(float amount)
	{
		_angle += amount;
		if (_angle < 0) _angle += 360; // only if below zero, should add up to 359
		if (_angle >= 360) _angle -= 360; 
	}
	void move(float amount)
	{
		sf::Vector2f ratios = getTrigComponent();
		sf::Vector2f add = ratios * amount;
		std::cout << add.x << " " << add.y << std::endl;
		_pos += add;
		// trig -> geo: +270 degrees or subtract 90 degrees
	}

};

