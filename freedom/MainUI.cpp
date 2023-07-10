#include "MainUI.h"

MainUI::MainUI() : lineRadius(10), lineCenter(30, 120), primaryUITexture(), primaryUI(), 
				   DisplayFont(), energyMeterRect()
{

}

int MainUI::onLoad()
{
	// load main ui sprite and texture

	if (!primaryUITexture.loadFromFile("./resources/bitmaps/primaryUI.bmp"))
	{
		std::cerr << "\nin main.cpp: int main():"
			"primaryUI.loadFromFile(...) failed to load primaryUI.png" << std::endl;
		system("pause");
		return 1;
	}
	primaryUI = sf::Sprite(primaryUITexture);


	// fonts and text

	if (!DisplayFont.loadFromFile("./Resources/Fonts/sevenseg.ttf"))
	{
		std::cerr << "\nin main.cpp: int main():"
			"degreesFont.loadFromFile(...) failed to load sevenseg.ttf" << std::endl;
		system("pause");
	}
	degreesText = sf::Text("000", DisplayFont, 12);
	xCoordText = sf::Text("000", DisplayFont, 12);
	yCoordText = sf::Text("000", DisplayFont, 12);

	degreesText.setFillColor(sf::Color::Color(35, 177, 76, 255));
	xCoordText.setFillColor(sf::Color::Color(35, 177, 76, 255));
	yCoordText.setFillColor(sf::Color::Color(35, 177, 76, 255));

	degreesText.setPosition(7, 85);
	xCoordText.setPosition(67, 82);
	yCoordText.setPosition(67, 108);
	// Dial line

	dialLine[0] = sf::Vertex(lineCenter); // center
	dialLine[1] = sf::Vertex(sf::Vector2f(30, 120 + lineRadius));
	dialLine[0].color = sf::Color::Red;
	dialLine[1].color = sf::Color::Red;

	energyMeterRect.setFillColor(sf::Color::Green);
	energyMeterRect.setPosition(142, 12);
	energyMeterRect.setSize(sf::Vector2f(17, 57));

	return 0;
}

void MainUI::onUpdate(Player player)
{
	// dialLine

	dialLine[1].position = lineCenter + (player.getTrigComponent() * lineRadius);

	//degreesText

	std::stringstream stream;
	stream << std::fixed << std::right << std::setprecision(2) << player.getAngle();
	if (stream.str().length() < 6)
	{
		stream.str(std::string());
		stream << "0" << std::fixed << std::right << std::setprecision(2) << player.getAngle();
	}
	degreesText.setString(stream.str());

	//xCoordText

	stream.str(std::string());
	stream << std::fixed << std::right << std::setprecision(2) << player.getPosition().x;

	if (stream.str().length() < 6)
	{
		stream.str(std::string());
		stream << "0" << std::fixed << std::right << std::setprecision(2) << player.getPosition().x;
	}
	xCoordText.setString(stream.str());

	//ycoordText

	stream.str(std::string());
	stream << std::fixed << std::right << std::setprecision(2) << player.getPosition().y;

	if (stream.str().length() < 6)
	{
		stream.str(std::string());
		stream << "0" << std::fixed << std::right << std::setprecision(2) << player.getPosition().y;
	}
	yCoordText.setString(stream.str());

	energyMeterRect.setFillColor(sf::Color::Color(0,255*player.getEnergy(),0,255));

}

void MainUI::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	target.draw(primaryUI, states);
	target.draw(dialLine, 2, sf::Lines, states);
	target.draw(degreesText, states);
	target.draw(xCoordText, states);
	target.draw(yCoordText, states);
	target.draw(energyMeterRect, states);
}

