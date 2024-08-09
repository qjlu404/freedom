#pragma once
#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <thread>
#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX
#include <windows.h>
#include "Player.h"
#include "Raydar.h"
#include "MainUI.h"
#include "GameMap.h"
#include "Ray.h"
// const variable declaration
static unsigned resX = 800;
static unsigned resY = 600;

class RayGameCore
{
	int view; // 0 main panel
              // 1 player location

	sf::RenderWindow mainWindow;  // (sf::VideoMode(resX, resY), "Freedom");
	MainUI ui;
	Player player;                // mainly handles position and actions
	float playerAngularVelocity;
	float playerVelocity;
	sf::CircleShape PlayerCircle; // just the shape of the player. Must be updated with player transformation.
	sf::Vertex PlayerLine[2];     // just the visual line of player pointing. Also must be updated with player transformation
	float PlayerlineRadius;       // = 10;
	GameMap map;				  // the game map
	Raydar rad;					  // (map.GetMap(), 3, 3);
	sf::View ScannedMap;	      // The big picture map of the overall scanned shape
	sf::Int32 _dt;     	     	  // deltuh
	sf::RenderTexture mainTexture;
	sf::Sprite* mainSprite;
	std::thread renderThread;
	std::thread windowThread;
	std::thread logicThread;
public:
	RayGameCore();    // Init
	int Load();    // Start
	void update(sf::Int32 dt);    // giving main control of updating instead of concealing within a run loop function
	void windowEvents(); // handle window events.
	bool windowIsOpen()
	{
		return mainWindow.isOpen();
	}
	void render();    // render
	void asyncUpdate(sf::Int32 dt)
	{
			update(dt);
	}
	void asyncRender()
	{
			render();
	}
	void asyncEvents()
	{
			windowEvents();
	}
	void run()
	{
		//windowThread = std::thread(&RayGameCore::asyncEvents, this);
		//logicThread = std::thread(&RayGameCore::asyncUpdate,this,  _dt);
		//renderThread = std::thread(&RayGameCore::asyncRender, this);
		while (windowIsOpen())
		{
			asyncEvents();
			asyncUpdate(_dt);
			asyncRender();
			mainWindow.clear();
			mainWindow.draw(*mainSprite);
			mainWindow.display();
		}
	}

};

