#pragma once
#ifndef SFML_STATIC
#define SFML_STATIC
#endif // !SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
// player data model
class Player
{
	sf::Vector2f _pos;

	float _angle;
	float xComponent, yComponent;
	float energy;
public:
	Player();

	void setPosition(sf::Vector2f pos);
	sf::Vector2f getPosition();

	void setAngle(float angle);
	float getAngle();

	sf::Vector2f getTrigComponent();

	void turn(float amount);
	void move(float amount);

	float getEnergy()
	{
		return energy;
	}
	void setEnergy(float eng)
	{
		energy = eng;
	}

};

