#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include <direct.h>
#include <vector>

using namespace sf;

#pragma region Creation des entites et de leurs boxs de collisions

sf::CircleShape hero(20.f, 4);
	CircleShape enemy;
sf::RectangleShape wallO(sf::Vector2f(50, 1200));
sf::RectangleShape wallN(sf::Vector2f(2000, 50));
sf::RectangleShape wallE(sf::Vector2f(50, 1200));
sf::RectangleShape wallS(sf::Vector2f(2000, 50));

#pragma endregion 

class Shoot
{
public:
	CircleShape shot;
	Vector2f currVelocity;
	float maxSpeed;

	Shoot(float radius = 5.f) 
		: currVelocity(0.f, 0.f), maxSpeed(15.f)
	{
		this->shot.setRadius(radius);
		this->shot.setFillColor(Color::Cyan);
	};
};

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;

	sf::RenderWindow window(sf::VideoMode(1920, 1080), "SFML works!" , Style::Fullscreen);   // Taille de la fenetre

	#pragma region Pour les tirs

	Vector2f playerCenter;
	Vector2f mousePos;
	Vector2f aimDir;
	Vector2f aimDirNorm;

	Shoot tir;
	std::vector<Shoot> tirs;

	tirs.push_back(Shoot(tir));

	#pragma endregion

	#pragma region Entites : Couleurs, position, etc...

	hero.setPosition(600, 400);
	hero.setFillColor(sf::Color::Cyan);	// Couleur
	hero.setOutlineThickness(4);
	hero.setOutlineColor(sf::Color::Blue);

	enemy.setPosition(600, 400);
	enemy.setFillColor(sf::Color::Magenta);	// Couleur
	enemy.setOutlineThickness(4);
	enemy.setOutlineColor(sf::Color::Red);

	wallO.setPosition(0, 0);
	wallO.setFillColor(sf::Color::Black);	// Couleur
	wallO.setOutlineThickness(4);
	wallO.setOutlineColor(sf::Color::Red);

	wallN.setPosition(0, 0);
	wallN.setFillColor(sf::Color::Black);	// Couleur
	wallN.setOutlineThickness(4);
	wallN.setOutlineColor(sf::Color::Red);

	wallE.setPosition(1875, 0);
	wallE.setFillColor(sf::Color::Black);	// Couleur
	wallE.setOutlineThickness(4);
	wallE.setOutlineColor(sf::Color::Red);

	wallS.setPosition(0, 1035);
	wallS.setFillColor(sf::Color::Black);	// Couleur
	wallS.setOutlineThickness(4);
	wallS.setOutlineColor(sf::Color::Red);

	#pragma endregion 

	#pragma region Ennemis



	#pragma endregion

	window.setVerticalSyncEnabled(true);

	sf::Font * font = new sf::Font();
	MemFile f;
	if (font->loadFromFile("Res/DejaVuSans.ttf") == false) {
		printf("no such font\n");
	}

	sf::Text myFpsCounter;
	int every = 0;

	while (window.isOpen())   // Tant que la fenetre est ouverte DEBUT DE LA FRAME
	{
		sf::Event event;   // Recup les evenements clavier/souris	

		Vector2f lastGoodPos = hero.getPosition();

		// Pour les tirs
		playerCenter = Vector2f(hero.getPosition().x + hero.getRadius(), hero.getPosition().y + hero.getRadius());
		mousePos = Vector2f(Mouse::getPosition(window));
		aimDir = mousePos - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		while (window.pollEvent(event))
		{
			switch (event.type)
			{				
				case sf::Event::KeyPressed :					
					if (event.key.code == sf::Keyboard::Q)
						hero.move(-10.f, 0.f);
					if (event.key.code == sf::Keyboard::D)
						hero.move(10.f, 0.f);
					if (event.key.code == sf::Keyboard::Z)
						hero.move(0.f, -10.f);
					if (event.key.code == sf::Keyboard::S)
						hero.move(0.f, 10.f);
					break;

				case sf::Event::Closed :
					window.close();
					break;

				default:
					break;
			}	
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				tir.shot.setPosition(playerCenter);
				tir.currVelocity = aimDirNorm * tir.maxSpeed;

				tirs.push_back(Shoot(tir));
			}
			for (size_t i = 0; i < tirs.size(); i++)
			{
				tirs[i].shot.move(tirs[i].currVelocity);

				if (tirs[i].shot.getPosition().x < 0 || tirs[i].shot.getPosition().x > window.getSize().x ||
					tirs[i].shot.getPosition().y < 0 || tirs[i].shot.getPosition().y > window.getSize().y)
				{
					tirs.erase(tirs.begin() + i);
				}
			}
		}

	#pragma region Tests de collision des 4 murs Ouest, Nord, Est et Sud

		if (hero.getGlobalBounds().intersects(wallO.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPos);
		}
		if (hero.getGlobalBounds().intersects(wallN.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPos);
		}
		if (hero.getGlobalBounds().intersects(wallE.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPos);
		}
		if (hero.getGlobalBounds().intersects(wallS.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPos);
		}

	#pragma endregion 
		
		window.clear();   // Nettoie la frame
		window.draw(hero);

		for (size_t i = 0; i < tirs.size(); i++)
		{
			window.draw(tirs[i].shot);
		}

		window.draw(wallO);	window.draw(wallE);	window.draw(wallN); window.draw(wallS);

		window.display();   // Dessine et ça attend la vsync
	}

	return 0;
}