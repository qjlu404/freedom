#include "Player.h"

Player::Player() : _pos(0, 0), _angle(90.f), xComponent(0), yComponent(0), energy(100)
{
	energy = 100;
}

void Player::setPosition(sf::Vector2f pos)
{
	this->_pos = pos;
}

sf::Vector2f Player::getPosition()
{
	return _pos;
}

void Player::onUpdate()
{
	if (energy < 1) energy = 0;
}

void Player::setAngle(float angle)
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
float Player::getAngle()
{
	return _angle;
}

sf::Vector2f Player::getTrigComponent()
{
	float tAngle = _angle + 270;
	if (tAngle < 0) tAngle += 360;
	if (tAngle >= 360) tAngle -= 360;
	yComponent = sin(3.14f * (tAngle / 180));
	xComponent = cos(3.14f * (tAngle / 180));
	return sf::Vector2f(xComponent, yComponent);
}

void Player::turn(float amount)
{
	_angle += amount;
	if (_angle < 0) _angle += 360; // only if below zero, should add up to 359
	if (_angle >= 360) _angle -= 360;
	energy -= 0.0001f;
}
void Player::move(float amount)
{
	sf::Vector2f ratios = getTrigComponent();
	sf::Vector2f add = ratios * amount;
	_pos += add;
	// trig -> geo: +270 degrees or subtract 90 degrees
	energy -= 0.0001f;
}
void Player::strafe(float amount)
{
	turn(90);
	move(amount);
	turn(-90);
	energy -= 0.0001f;
}

void Player::onPing()
{
	energy -= 0.02f;
}

