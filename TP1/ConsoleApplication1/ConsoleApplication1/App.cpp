#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include <direct.h>
#include <vector>

using namespace sf;

static sf::Shader * simpleShader = nullptr;
static sf::Shader * redShader = nullptr;
static sf::Shader * bloomShader = nullptr;
static sf::Shader * blurShader = nullptr;
static sf::Texture * whiteTex = nullptr;
static sf::Texture * murTex = nullptr;

#pragma region Creation des entites et de leurs boxs de collisions

sf::CircleShape hero(40.f, 4);
sf::CircleShape enemy(40.f, 4);
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

int heroLife = 10;
bool heroDead = false;
int enemyLife = 10;
bool enemyDead = false;

int main()
{
	#pragma region Pour les Shaders

	if (!sf::Shader::isAvailable())
	{
		printf("no shader avail\n");
	}

	simpleShader = new Shader();
	if (!simpleShader->loadFromFile("res/simple.vert", "res/simple.frag"))
	{
		printf("unable to load shaders\s");
	}

	whiteTex = new Texture();
	if (!whiteTex->create(1, 1)) printf("tex crea failed\n");
	whiteTex->setSmooth(true);
	unsigned int col = 0xffffffff;
	whiteTex->update((const sf::Uint8*)&col, 1, 1, 0, 0);

	murTex = new Texture();
	if (!murTex->loadFromFile("res/mur.jpg"))
	{
		printf("Rip le mur\s");
	}

	#pragma endregion

	sf::ContextSettings settings;
	settings.antialiasingLevel = 10;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!" /*, Style::Fullscreen*/);   // Taille de la fenetre

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
	hero.setTexture(whiteTex);	// Shader

	enemy.setPosition(400, 600);
	enemy.setFillColor(sf::Color(255, 146, 0));	// Couleur
	enemy.setOutlineThickness(4);
	enemy.setOutlineColor(sf::Color::Red);

	wallO.setPosition(0, 0);
	wallO.setFillColor(sf::Color::Black);	// Couleur
	wallO.setOutlineThickness(4);
	wallO.setOutlineColor(sf::Color(186, 184, 185));

	wallN.setPosition(0, 0);
	wallN.setFillColor(sf::Color::Black);	// Couleur
	wallN.setOutlineThickness(4);
	wallN.setOutlineColor(sf::Color(186, 184, 185));

	wallE.setPosition(1875, 0);
	wallE.setFillColor(sf::Color::Black);	// Couleur
	wallE.setOutlineThickness(4);
	wallE.setOutlineColor(sf::Color(186, 184, 185));

	wallS.setPosition(0, 1035);
	wallS.setFillColor(sf::Color::Black);	// Couleur
	wallS.setOutlineThickness(4);
	wallS.setOutlineColor(sf::Color(186, 184, 185));

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

		Vector2f lastGoodPosHero = hero.getPosition();
		Vector2f lastGoodPosEnemy = enemy.getPosition();

		// Pour les tirs
		playerCenter = Vector2f(hero.getPosition().x + hero.getRadius(), hero.getPosition().y + hero.getRadius());
		mousePos = Vector2f(Mouse::getPosition(window));
		aimDir = mousePos - playerCenter;
		aimDirNorm = aimDir / sqrt(pow(aimDir.x, 2) + pow(aimDir.y, 2));

		#pragma region Commandes Clavier/Souris (Hero/J1)

		if (Keyboard::isKeyPressed(Keyboard::Q))
		{
			hero.move(-10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::D))
		{
			hero.move(10.f, 0.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::Z))
		{
			hero.move(0.f, -10.f);
		}
		if (Keyboard::isKeyPressed(Keyboard::S))
		{
			hero.move(0.f, 10.f);
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

		#pragma endregion 

		// A FINIR !!!
		#pragma region Commandes Manette (Enemy/J2)

		sf::Clock clock;

		if (sf::Joystick::isConnected(0))   // SI le joystick numéro 0 est connecté
		{
			printf("Manette connectee \n");
		}
		else
		{
			printf("Manette NON connectee \n");
		}

		/*
		sf::Vector2f moveSpeed(sf::Joystick::getAxisPosition(0, sf::Joystick::X), sf::Joystick::getAxisPosition(0, sf::Joystick::Y));
		
		printf("VALS %f %f \n", moveSpeed.x, moveSpeed.y);

		if (moveSpeed.x > 0.2)
				//enemy.move(10.f, 0.f);
			printf("Go O \n");
		else if (moveSpeed.x < -0.2)
				//enemy.move(-10.f, 0.f);
			printf("Go E \n");
		else if (moveSpeed.y < -0.2)
				//enemy.move(0.f, -10.f);
			printf("Manette NON connectee \n");
		else if (moveSpeed.y > 0.2)
				//enemy.move(0.f, 10.f);
			printf("Manette NON connectee \n");

		enemy.move(moveSpeed.x * clock.getElapsedTime().asSeconds(), moveSpeed.y * clock.getElapsedTime().asSeconds());
		*/

		float x = sf::Joystick::getAxisPosition(0, sf::Joystick::X);
		float y = sf::Joystick::getAxisPosition(0, sf::Joystick::Y);
		enemy.move(x, y);

		#pragma endregion

		#pragma region Tests de collision des 4 murs Ouest, Nord, Est et Sud

		// Pour Hero/J1
		if (hero.getGlobalBounds().intersects(wallO.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPosHero);
		}
		if (hero.getGlobalBounds().intersects(wallN.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPosHero);
		}
		if (hero.getGlobalBounds().intersects(wallE.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPosHero);
		}
		if (hero.getGlobalBounds().intersects(wallS.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPosHero);
		}
		if (hero.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			hero.setPosition(lastGoodPosHero);
		}
		// Pour Enemy/J2
		if (enemy.getGlobalBounds().intersects(wallO.getGlobalBounds()))
		{
			enemy.setPosition(lastGoodPosEnemy);
		}
		if (enemy.getGlobalBounds().intersects(wallN.getGlobalBounds()))
		{
			enemy.setPosition(lastGoodPosEnemy);
		}
		if (enemy.getGlobalBounds().intersects(wallE.getGlobalBounds()))
		{
			enemy.setPosition(lastGoodPosEnemy);
		}
		if (enemy.getGlobalBounds().intersects(wallS.getGlobalBounds()))
		{
			enemy.setPosition(lastGoodPosEnemy);
		}
		if (enemy.getGlobalBounds().intersects(hero.getGlobalBounds()))
		{
			enemy.setPosition(lastGoodPosEnemy);
		}

		#pragma endregion 

		#pragma region Tests de collision des tirs

		if (hero.getGlobalBounds().intersects(enemy.getGlobalBounds()))
		{
			enemyDead = true;
			printf("OK");
		}

		#pragma endregion
		
		window.clear();   // Nettoie la frame

		if (heroDead == false)
		{
			window.draw(hero/*, simpleShader*/);
		}
		if (enemyDead == false)
		{
			window.draw(enemy);
		}

		for (size_t i = 0; i < tirs.size(); i++)
		{
			window.draw(tirs[i].shot);
		}

		window.draw(wallO);	window.draw(wallE);	window.draw(wallN); window.draw(wallS);

		window.display();   // Dessine et ça attend la vsync
	}

	return 0;
}