#include "Ray.h"

Ray::Ray() : _position(0, 0), _TrigComponents(1, 0), _angle(0)
{
}
Ray::Ray(sf::Vector2f pos, float angle) : _position(pos), _angle(angle)
{
	float tAngle = _angle + 270;
	if (tAngle < 0) tAngle += 360;
	if (tAngle >= 360) tAngle -= 360;
	_TrigComponents = sf::Vector2f(cos(3.14f * (tAngle / 180)),
		sin(3.14f * (tAngle / 180)));


	lines[1].position = _position + sf::Vector2f(_TrigComponents.x * 10, _TrigComponents.y * 10);
	lines[0].position = _position;
	lines[0].color = sf::Color::White;
	lines[1].color = sf::Color::White;
}

void Ray::SetPosition(sf::Vector2f pos)
{
	_position = pos;
	lines[0].position = _position;
	lines[1].position = _position + sf::Vector2f(_TrigComponents.x * 10, _TrigComponents.y * 10);

}
sf::Vector2f Ray::GetPosition()
{
	return _position;
}
void Ray::SetAngle(float _angle)
{
	float tAngle = _angle + 270;
	if (tAngle < 0) tAngle += 360;
	if (tAngle >= 360) tAngle -= 360;
	_TrigComponents = sf::Vector2f(cos(3.14f * (tAngle / 180)),
		sin(3.14f * (tAngle / 180)));


	lines[1].position = _position + sf::Vector2f(_TrigComponents.x * 10, _TrigComponents.y * 10);
}


sf::Vector2f Ray::cast(Boundary b)
{
	sf::Vector2f v1 = b.lines[0].position;				   // x1 y1, boundary start point
	sf::Vector2f v2 = b.lines[1].position;				   // x2 y2, boundary end point
	sf::Vector2f v3 = _position;						   // x3 y3, ray start point
	sf::Vector2f v4 = _position + _TrigComponents;// x4 y4, ray end point

	float tdenom = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
	if (tdenom == 0)
	{
		return sf::Vector2f(NAN, NAN);
	}// hopefully could avoid divide by zero error
	float t = ((v1.x - v3.x) * (v3.y - v4.y) - (v1.y - v3.y) * (v3.x - v4.x)) / tdenom;

	float udenom = (v1.x - v2.x) * (v3.y - v4.y) - (v1.y - v2.y) * (v3.x - v4.x);
	if (udenom == 0)
	{
		return sf::Vector2f(NAN, NAN);
	}
	float u = ((v1.x - v3.x) * (v1.y - v2.y) - (v1.y - v3.y) * (v1.x - v2.x)) / udenom;

	if (!(t > 0 && t < 1 && u>0))
	{
		return sf::Vector2f(NAN, NAN);
	}

	sf::Vector2f ipoint(v1.x + t * (v2.x - v1.x),
		v1.y + t * (v2.y - v1.y));
	return ipoint;

}
void Ray::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	sf::Vertex templines[2] =
	{
		lines[0], lines[1]
	};
	templines[1].position = _position + _TrigComponents * (float)100;

	target.draw(templines, 2, sf::Lines, states);
}
