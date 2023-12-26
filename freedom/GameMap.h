#pragma once
#define SFML_STATIC
#include <vector>
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <SFML/System/Vector2.hpp>
#include "Boundary.h"

// boundary map
// boundary begin, boundary end 
// [x][y] [x][y]
class GameMap
{
public:
	std::vector<Boundary> boundaries;
	GameMap() : boundaries()
	{

	}

	int loadFromFile(std::string name)
	{
		std::ifstream handle(name, std::ios::in);
		float ax, ay, bx, by;
		while (handle >> ax >> ay >> bx >> by)
		{
			boundaries.push_back(Boundary(sf::Vector2f(ax, ay), sf::Vector2f(bx, by)));
		}
		handle.close();
		return 0;
	}

	int serialize(std::string name)
	{
		std::ofstream handle;
		handle.open(name, std::ios::out);
		for (size_t i = 0; i < boundaries.size(); i++)
		{
			handle << (float)boundaries[i].lines[0].position.x << " " << (float)boundaries[i].lines[0].position.y
		    << " " << (float)boundaries[i].lines[1].position.x << " " << (float)boundaries[i].lines[1].position.y 
		    << std::endl;
		}
		handle.close();
		return 0;
	}

	std::vector<Boundary> GetMap()
	{
		return boundaries;
	}


};

