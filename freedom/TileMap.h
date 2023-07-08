#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>
#include "Tile.h"

class TileMap : public sf::Drawable
{
	sf::Vector2u _mapsize;
	unsigned _tilesize;
public:
	std::vector<std::vector<Tile>> tiles;

	TileMap() : tiles(), _mapsize(80, 60), _tilesize(10)
	{
		
	}

	TileMap(unsigned tilesize, sf::Vector2u mapsize) : tiles()
	{
		_tilesize = tilesize;
		_mapsize = mapsize;
	}


	void onLoad()
	{
		for (size_t i = 0; i < _mapsize.x; i++)
		{
			std::vector<Tile> temp;

			for (size_t j = 0; j < _mapsize.y; j++)
			{
				Tile tile;

				tile.tileRect.setPosition((float)i * (float)_tilesize, (float)j * (float)_tilesize);
				tile.tileRect.setSize(sf::Vector2f((float)_tilesize, (float)_tilesize));
				tile.tileRect.setFillColor(sf::Color::Color(100,100,100,255));
				tile.tileRect.setOutlineThickness(10.f);
				tile.Bounds();
				temp.push_back(tile);
			}

			tiles.push_back(temp);
		}
	}

	int LoadFromFile(std::string path)
	{
		std::ifstream file(path);
		_mapsize = sf::Vector2u(0,0);
		if (!(file >> _mapsize.x >> _mapsize.y))
		{
			std::cerr << "in TileMap.h, class TileMap, function (int) LoadFromFile(string)" << std::endl
				<< " Error loading file: " << path << std::endl;
			return 1; // error
		}

		onLoad();

		sf::Vector2u tempPos;
		bool tempPassable = 0;
		float tempCapital = 0;
		unsigned r, g, b;
		std::string tempName;

		while (file >> tempPos.x >> tempPos.y >> tempPassable >> tempCapital >> r >>
			g >> b >> tempName)
		{
			if (tempPos.x > tiles.size() || tempPos.y > tiles[tempPos.x].size())
			{
				std::cerr << "in TileMap.h, class TileMap, function (int) LoadFromFile(string)" << std::endl
					<< " Tile position out of range: " << std::endl
					<< "(" << tempPos.x << ", " << tempPos.y << ")" << std::endl
					<< "Range: (" << tiles.size() << ", " << tiles[0].size() << ")" << std::endl;
				return 1; // error
			}

			tiles[tempPos.x][tempPos.y]._passable = tempPassable;
			tiles[tempPos.x][tempPos.y]._capital = tempCapital;
			tiles[tempPos.x][tempPos.y].tileRect.setFillColor(sf::Color(r, g, b, 0xff));
			tiles[tempPos.x][tempPos.y]._name = tempName;
			
		}
		
		return 0; // OK
	}

private:
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		for (size_t i = 0; i < tiles.size(); i++)
		{
			for (size_t j = 0; j < tiles[i].size(); j++)
			{
				target.draw(tiles[i][j], states);
			}
		}
	}
};

