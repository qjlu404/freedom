#define SFML_STATIC
#include <iostream>
#include <array>
#include <sstream>
#include <SFML/Graphics.hpp>
#include "GameMap.h"

void main()
{
	sf::RenderWindow mainWindow(sf::VideoMode(1280, 720), "Map Editor", sf::Style::Close);
	sf::View mainView(mainWindow.getDefaultView());
	sf::RectangleShape mouseRect;
	mouseRect.setFillColor(sf::Color::Red);
	mouseRect.setSize(sf::Vector2f(5, 5));
	GameMap map;
	sf::Font arialFont;
	if (!arialFont.loadFromFile("./resources/fonts/tuffy.ttf"))
	{
		std::cerr << "Project: Freedom-MapMaker. Main.cpp \n error loading 'tuffy.ttf' " << std::endl;
	}
	sf::Text frameSizeText("--, --", arialFont);
	frameSizeText.setPosition(0, 0);
	std::array<sf::Vector2f, 2> poses;
	int increment = 0;
	int firstbit = 0;
	while (mainWindow.isOpen())
	{

		sf::Event event;
		while (mainWindow.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				if (map.serialize("./map.te")) std::cerr << "serialization error.";
				mainWindow.close();
			}
			if (event.type == sf::Event::MouseButtonReleased)
			{
				if (!firstbit)
				{
					poses[increment] = mouseRect.getPosition() + sf::Vector2f(2.5f, 2.5f);
					increment++;
					if (increment > 1)
					{
						Boundary localboundary(poses[0], poses[1]);
						map.boundaries.push_back(localboundary);
						increment = 0;
						firstbit = 1;
					}
				}
				else
				{
					poses[0] = poses[1];
					poses[1] = mouseRect.getPosition() + sf::Vector2f(2.5f, 2.5f);
					Boundary localboundary(poses[0], poses[1]);
					map.boundaries.push_back(localboundary);
				}

			}

		}

		sf::Vector2i mousePos = sf::Mouse::getPosition(mainWindow);
		mouseRect.setPosition(mainWindow.mapPixelToCoords(mousePos));

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Equal))
		{
			mainView.zoom(1.003f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Hyphen))
		{
			mainView.zoom(0.997f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			mainView.move(-0.001f * mainView.getSize().x, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			mainView.move(0.001f * mainView.getSize().x, 0);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			mainView.move(0, -0.001f * mainView.getSize().x);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			mainView.move(0, 0.001f * mainView.getSize().x);
		}
		std::stringstream fstext;
		fstext << "Width: "  << mainView.getSize().x << "\n"
			   << "Height: " << mainView.getSize().y << "\n"
			   << "Increment: " << increment;
		frameSizeText.setString(fstext.str());

		mainWindow.clear();
		mainWindow.setView(mainView);
		
		for (size_t i = 0; i < map.boundaries.size(); i++)
		{
			mainWindow.draw(map.boundaries[i]);
		}
		mainWindow.draw(mouseRect);
		mainWindow.setView(mainWindow.getDefaultView());
		mainWindow.draw(frameSizeText);
		mainWindow.setView(mainView);
		mainWindow.display();


	}
}
