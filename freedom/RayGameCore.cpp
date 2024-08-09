#include "RayGameCore.h"

RayGameCore::RayGameCore() // constructor
    : view(0), mainWindow(sf::VideoMode(resX, resY), "Freedom"), ui(), player(),
    playerAngularVelocity(0), playerVelocity(0), PlayerCircle(5), PlayerlineRadius(10),
    map(), rad(), ScannedMap(), _dt(0), mainTexture()
{
    PlayerLine[0] = sf::Vertex(PlayerCircle.getPosition()); // center
    PlayerLine[1] = sf::Vertex(sf::Vector2f(PlayerCircle.getPosition() + sf::Vector2f(0, PlayerlineRadius))); // radius
    PlayerLine[0].color = sf::Color::Green;
    PlayerLine[1].color = sf::Color::Green;
    ScannedMap.setViewport(sf::FloatRect(72.f / 200.f, 12.f / 150.f, 56.f / 200.f, 56.f / 150.f));
    ScannedMap.setSize(2000, 2000);
    mainTexture.setView(sf::View(sf::Vector2f(400, 300), sf::Vector2f(800, 600)));
    mainSprite = new sf::Sprite(mainTexture.getTexture());
}

int RayGameCore::Load()
{
    if (ui.onLoad())                  return 1001; // error loading ui
    if (map.loadFromFile("./map.te")) return 1002; // error loading map
    rad = Raydar(map.GetMap(), 5, 10);
    return 0;
}

void RayGameCore::update(sf::Int32 dt)
{
    //sf::sleep(sf::milliseconds(64));
    rad.ping();

    // movement and rotation
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        if (playerAngularVelocity <= 0.02f)
            playerAngularVelocity += 0.01f;
        player.turn(playerAngularVelocity * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        if (playerAngularVelocity >= -0.02)
            playerAngularVelocity -= 0.01f;
        player.turn(playerAngularVelocity * dt);
    }
    else if (abs(playerAngularVelocity) > 0)
    {
        if (abs(playerAngularVelocity) < 0.003)
            playerAngularVelocity = 0;
        else if (playerAngularVelocity < 0)
            playerAngularVelocity += 0.003f;
        else if (playerAngularVelocity > 0)
            playerAngularVelocity -= 0.003f;

        player.turn(playerAngularVelocity * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        if (playerVelocity <= 0.02)
            playerVelocity += 0.01f;
        player.move(playerVelocity * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        if (playerVelocity >= -0.02)
            playerVelocity += -0.01f;
        player.move(playerVelocity * dt);
    }
    else if (abs(playerVelocity) > 0)
    {
        if (abs(playerVelocity) < 0.01)
            playerVelocity = 0;
        else if (playerVelocity < 0)
            playerVelocity += 0.01f;
        else if (playerVelocity > 0)
            playerVelocity -= 0.01f;

        player.move(playerVelocity * dt);
    }

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        if (playerVelocity <= 0.02)
            playerVelocity += 0.01f;
        player.strafe(playerVelocity * dt);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        if (playerVelocity >= -0.02)
            playerVelocity += -0.01f;
        player.strafe(playerVelocity * dt);
    }
    else if (abs(playerVelocity) > 0)
    {
        if (abs(playerVelocity) < 0.01)
            playerVelocity = 0;
        else if (playerVelocity < 0)
            playerVelocity += 0.01f;
        else if (playerVelocity > 0)
            playerVelocity -= 0.01f;

        player.strafe(playerVelocity * dt);
    }

    // update
    player.onUpdate();
    ui.onUpdate(player);


    PlayerCircle.setPosition(player.getPosition());

    PlayerLine[0].position = PlayerCircle.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius());
    PlayerLine[1].position = PlayerLine[0].position + player.getTrigComponent() * 1.1f;

    rad.onUpdate(player.getAngle(), player.getPosition() + sf::Vector2f(PlayerCircle.getRadius(), PlayerCircle.getRadius()));

}

void RayGameCore::windowEvents()
{
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
                rad.ping(); // I know it's bad practice to put game controls in event logic but 
                break;      // they said this was the only way to prevent duplicate actions.
            }
        }
    }
}

void RayGameCore::render()
{
    // render
    mainTexture.create(800,600);
    mainTexture.clear();
    mainTexture.setView(sf::View((sf::FloatRect)ui.primaryUI.getTextureRect()));
    mainTexture.draw(ui);
    mainTexture.setView(rad.RaydarView);
    mainTexture.draw(rad);
    mainTexture.draw(PlayerCircle);
    mainTexture.draw(PlayerLine, 2, sf::Lines);
    // left 72 / 200,   right 128 / 200,
    // bottom 68 / 150, top 12 / 150

    mainTexture.setView(ScannedMap);

    mainTexture.draw(rad);
    mainTexture.draw(PlayerCircle);
    mainTexture.draw(PlayerLine, 2, sf::Lines);
    mainTexture.display();
    mainSprite = new sf::Sprite(mainTexture.getTexture());
}