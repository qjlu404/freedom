#define SFML_STATIC
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#ifndef NOMINMAX
#define NOMINMAX
#endif // !NOMINMAX
#include <windows.h>
#include "Player.h"
#include "TileMap.h"
#include "MainUI.h"
#include "Boundary.h"
#include "Ray.h"
// const variable declaration
static const unsigned resX = 800;
static const unsigned resY = 600;

int main()
{
    int view = 0; // 0 main panel
                  // 1 player location
                  // 
    // main window init

    sf::RenderWindow mainWindow(sf::VideoMode(resX,resY), "Freedom");

    MainUI ui;
    ui.onLoad();
    // Initialize Player

    Player player;
    float Va = 0;
    float V = 0;


    // view = 1

    sf::CircleShape PlayerCircle;
    PlayerCircle.setRadius(5);
    float PlayerlineRadius = 10;
    sf::Vertex PlayerLine[] =
    {
        sf::Vertex(PlayerCircle.getPosition()), // center
        sf::Vertex(sf::Vector2f(PlayerCircle.getPosition() + sf::Vector2f(0,PlayerlineRadius))) // radius
    };
    PlayerLine[0].color = sf::Color::Red;
    PlayerLine[1].color = sf::Color::Red;
    
    /*TileMap tm;
    if (tm.LoadFromFile("./resources/MapData/map1.te"))
    {
        return 0;
    }*/

    Boundary boundary(sf::Vector2f(400, 50), sf::Vector2f(500, 250));
    Boundary boundary1(sf::Vector2f(400, 50), sf::Vector2f(200, 100));
    Boundary boundary2(sf::Vector2f(200, 100), sf::Vector2f(250, 200));
    Boundary boundary3(sf::Vector2f(250, 200), sf::Vector2f(500, 250));
    std::vector<Boundary> Boundaries = {boundary, boundary1, boundary2, boundary3};

    Ray ray1(sf::Vector2f(200, 200), 90);
    size_t centralRay = 5;
    int fovMultiplier = 4; // <- markiplier
    if (!(centralRay % 2)) 
        centralRay++;
    std::vector<Ray> rays;
    for (int i = 0; i < centralRay * 2-1; i++)
    {
        rays.push_back(ray1);
    }
    // delta time

    sf::Clock clock;

   
    // mainloop

    while (mainWindow.isOpen())
    {

        sf::Int32 dt = clock.restart().asMilliseconds();


        // Events

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            if (event.type == sf::Event::Resized)
            {
            }
        }

        sf::sleep(sf::milliseconds(32));


        // movement and rotation

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (Va <= 0.02f)
                Va += 0.01f;
            player.turn(Va * dt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (Va >= -0.02)
                Va -= 0.01f;
            player.turn(Va * dt);
        }
        else if (abs(Va) > 0)
        {
            if (abs(Va) < 0.003)
                Va = 0;
            else if (Va < 0)
                Va += 0.003f;
            else if (Va > 0)
                Va -= 0.003f;

            player.turn(Va * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            if (V <= 0.02)
                V += 0.01f;
            player.move(V * dt);
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            if (V >= -0.02)
                V += -0.01f;
            player.move(V * dt);
        }
        else if (abs(V) > 0)
        {
            if (abs(V) < 0.01)
                V = 0;
            else if (V < 0)
                V += 0.01f;
            else if (V > 0)
                V -= 0.01f;

            player.move(V * dt);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::I))
        {
            view = 0;
        }
        else if (sf::Keyboard::isKeyPressed(sf::Keyboard::O))
        {
            view = 1;
        }

        // update
        
        ui.onUpdate(player);

        PlayerCircle.setPosition(player.getPosition());
        PlayerLine[0].position = PlayerCircle.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius());
        PlayerLine[1].position = PlayerLine[0].position + (PlayerlineRadius * player.getTrigComponent());

        
        std::vector <sf::CircleShape> endpoints;

        //Distance to Center Ray
        int dcr = 0;
        for (size_t i = 0; i < rays.size(); i++)
        {
            
            dcr = (int)i - (int)centralRay+1;
            rays[i].SetAngle(player.getAngle() + dcr * fovMultiplier);


            rays[i].SetPosition(player.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius()));
            
            sf::CircleShape shape(3.f);
            shape.setFillColor(sf::Color::White);
            for (size_t j = 0; j < Boundaries.size(); j++)
            {
                sf::Vector2f iPosition = rays[i].cast(Boundaries[j]);
                if (iPosition.x == NAN || iPosition.y == NAN)
                {
                    continue;
                }
                shape.setPosition(iPosition - sf::Vector2f(shape.getRadius(), shape.getRadius()));
                endpoints.push_back(shape);
            }
            /*
            for (size_t j = 0; j < tm.tiles.size(); j++)
            {
                for (size_t k = 0; k < tm.tiles[j].size(); k++)
                {
                    for (int l = 0; l < 4; l++)
                    {
                        rays[i].cast(tm.tiles[j][k].bounds[l]);
                    }
                }
            }*/
        }

        // render

        mainWindow.clear();
        //mainWindow.setView(view);
        if (view == 0)
        {
            mainWindow.setView(sf::View((sf::FloatRect)ui.primaryUI.getTextureRect()));
            mainWindow.draw(ui);
        }
        if (view == 1)
        {
            mainWindow.setView(mainWindow.getDefaultView());/*
            mainWindow.draw(tm);*/

            mainWindow.draw(PlayerCircle);
            mainWindow.draw(PlayerLine, 2, sf::Lines);

            mainWindow.draw(boundary);
            mainWindow.draw(boundary1);
            mainWindow.draw(boundary2);
            mainWindow.draw(boundary3);
            for (size_t i = 0; i < rays.size(); i++)
            {
                mainWindow.draw(rays[i]);
            }
            for (size_t i = 0; i < endpoints.size(); i++)
            {
                mainWindow.draw(endpoints[i]);
            }
        }
        mainWindow.display();

    }
    

    return 0;
}