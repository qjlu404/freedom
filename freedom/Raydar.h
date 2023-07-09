#pragma once
#define SFML_STATIC
#include "Ray.h"
#include <SFML/Graphics.hpp>
// RAY Detection And Ranging
// does the ray casting and display
// shows a relative view of the boundaries
// like its own program plugin
class Raydar : public sf::Drawable
{
public:
	float _angle;
	bool mapLoaded;
	int centralRay; // modifies ray count
	float fovMultiplier; // distance between rays
	sf::Vector2f position;
	sf::VertexArray echos;
	sf::View RaydarView;
	std::vector<Ray> rays;
	std::vector<Boundary> boundaryMap;
	Raydar() : centralRay(3), fovMultiplier(5), mapLoaded(0), rays(), boundaryMap(),
		position(0,0), _angle(0), RaydarView()
	{
		if (!(centralRay % 2))
			centralRay++;
		Ray ray;
		for (size_t i = 0; i < centralRay * 2 - 1; i++)
		{
			rays.push_back(ray);
		}
	}
	// boundarymap, centralrayindex, angle between rays 
	Raydar(std::vector<Boundary> map, int cr, int apr) : position(0,0), centralRay(cr), fovMultiplier(apr)
	{
		if (!(centralRay % 2))
			centralRay++;

		Ray ray;
		for (size_t i = 0; i < centralRay * 2 - 1; i++)
		{
			rays.push_back(ray);
		}

		boundaryMap = map;
		mapLoaded = true;
		// l = 148/200 t = 77/150 r = 192/200 b = 143/150
		//RaydarView.setViewport(sf::FloatRect(148.f / 200.f, 77.f / 150.f, 192.f / 200.f, 143.f / 150.f));
	}
	void onUpdate(float ang, sf::Vector2f pos)
	{

		_angle = ang;
		position = pos;
		
		RaydarView.setRotation(_angle);

		float tAngle = _angle + 270;
		if (tAngle < 0) tAngle += 360;
		if (tAngle >= 360) tAngle -= 360;
		sf::Vector2f TrigComponents = sf::Vector2f(cos(3.14f * (tAngle / 180)),
			sin(3.14f * (tAngle / 180)));

		RaydarView.setCenter(position + (TrigComponents * (RaydarView.getSize().y / 2.f)));

		sf::Vertex vtx;
		vtx.color = sf::Color::Green;
		vtx.position = pos;

		int dcr = 0;
		for (size_t i = 0; i < rays.size(); i++)
		{
			// update ray info
			dcr = (int)i - (int)centralRay + 1;
			rays[i].SetAngle(_angle + (dcr * fovMultiplier));
			rays[i].SetPosition(position);
		}


	}
	void ping()
	{
		sf::VertexArray vertecies(sf::TriangleFan);
		if (!mapLoaded) return;
		vertecies.append(sf::Vertex(position, sf::Color::Transparent)); // center vertex
		
		
		for (size_t i = 0; i < rays.size(); i++)
		{
			// record so that only the closest result is reported.
			float record = INFINITY;

			for (size_t j = 0; j < boundaryMap.size(); j++)
			{
				float dist = rays[i].castDistance(boundaryMap[j]);
				if (isnan(dist))
					continue;
				if (dist < record)
					record = dist;
			}

			float angle = rays[i].GetAngle();
			float tAngle = angle + 270;
			if (tAngle < 0) tAngle += 360;
			if (tAngle >= 360) tAngle -= 360;
			sf::Vector2f TrigComponents = sf::Vector2f(cos(3.14f * (tAngle / 180)),
				sin(3.14f * (tAngle / 180)));


			if (record == INFINITY) continue;


			sf::Vertex vtx;
			float g = std::fminf(255 / pow(record / 50, 2), 255.f);
			if (g < 10) g = 0;
			vtx.color = sf::Color::Color(
				0,
			    g,
				0,
				255);
			vtx.position = position + TrigComponents * record;
			vertecies.append(vtx);
		}
		echos = vertecies;
	}
	void setMap(std::vector<Boundary> map)
	{
		boundaryMap = map;
		mapLoaded = true;
	}

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		target.draw(echos, states);
	}

	
};

