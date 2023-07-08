#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <iostream>
#include <sstream>
#include <string>
#include <iomanip>
#include "Player.h"
class MainUI : public sf::Drawable
{

public:

	sf::Texture primaryUITexture;
	sf::Sprite primaryUI;

	sf::Font DisplayFont;
	sf::Text degreesText;
	sf::Text xCoordText;
	sf::Text yCoordText;

	sf::Vector2f lineCenter;
	float lineRadius;

	sf::Vertex dialLine[2];

	MainUI();

	int onLoad();

	void onUpdate(Player player);

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
};

