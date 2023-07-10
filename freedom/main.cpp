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
#include "Raydar.h"
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
    PlayerLine[0].color = sf::Color::Green;
    PlayerLine[1].color = sf::Color::Green;
    

    Boundary boundary(sf::Vector2f(400, 50), sf::Vector2f(500, 250));
    Boundary boundary1(sf::Vector2f(400, 50), sf::Vector2f(200, 100));
    Boundary boundary2(sf::Vector2f(200, 100), sf::Vector2f(250, 200));
    Boundary boundary3(sf::Vector2f(250, 200), sf::Vector2f(500, 250));
    std::vector<Boundary> Boundaries = {boundary, boundary1, boundary2, boundary3};

    // map, center ray index, degrees between rays
    Raydar rad(Boundaries, 7, 10);
    
    // delta time

    sf::Clock clock;
    while (mainWindow.isOpen())
    {

        sf::Int32 dt = clock.restart().asMilliseconds() * 2;


        // Events

        sf::Event event;
        while (mainWindow.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                mainWindow.close();
            if (event.type == sf::Event::Resized)
            {
            }
            if (event.type == sf::Event::KeyPressed)
            {
                switch (event.key.code)
                {
                case sf::Keyboard::P:
                    player.onPing();
                    rad.ping();
                    break;
                }
            }
        }

        sf::sleep(sf::milliseconds(32));


        // movement and rotation

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
        {
            if (Va <= 0.02f)
                Va += 0.01f;
            player.turn(Va * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            if (V <= 0.02)
                V += 0.01f;
            player.strafe(V * dt);
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            if (V >= -0.02)
                V += -0.01f;
            player.strafe(V * dt);
        }
        else if (abs(V) > 0)
        {
            if (abs(V) < 0.01)
                V = 0;
            else if (V < 0)
                V += 0.01f;
            else if (V > 0)
                V -= 0.01f;

            player.strafe(V * dt);
        }

        // update
        player.onUpdate();
        ui.onUpdate(player);


        PlayerCircle.setPosition(player.getPosition());

        PlayerLine[0].position = PlayerCircle.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius());
        PlayerLine[1].position = PlayerLine[0].position + (player.getTrigComponent() * (float)dt);

        rad.onUpdate(player.getAngle(), player.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius()));
        
        // render
        mainWindow.clear();
        if (view == 0)
        {
            mainWindow.setView(sf::View((sf::FloatRect)ui.primaryUI.getTextureRect()));
            mainWindow.draw(ui);
            rad.RaydarView.setSize(200, 200); // left, top, width, height
            rad.RaydarView.setViewport(sf::FloatRect(
                148.f / 200.f, // left
                77.f / 150.f,  // top
                44.f / 200.f,  // width
                66.f / 150.f   // height
            ));
            mainWindow.setView(rad.RaydarView);
            mainWindow.draw(rad);
            //mainWindow.draw(PlayerCircle);
            mainWindow.draw(PlayerLine, 2, sf::Lines);
        }
        mainWindow.display();

    }
    

    return 0;
}