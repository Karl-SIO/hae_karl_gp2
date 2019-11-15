// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include <direct.h>

using namespace sf;

sf::CircleShape shape(300.f, 2 * 3.141569 * 100);
sf::CircleShape cube(300.f, 4);
sf::CircleShape hexagone(300.f, 6);

sf::CircleShape lignFollower(25.f, 12);

sf::CircleShape hero(20.f, 4);

void drawCurve(sf::RenderWindow & win, sf::Clock &Timer)
{
	float now = Timer.getElapsedTime().asSeconds();
	sf::VertexArray va(sf::LineStrip);
	sf::Color red = sf::Color::Red;
	sf::Color blue = sf::Color::Blue;
	int nb = 100;
	float stride = 1280.0 / nb;

	int ofsX = 0;

	for (int i = 0; i < nb + 1; i++)
	{
		double ratio = 1.0 * i / nb;
		double x = 10 * ofsX + stride * i;
		double y = 390;

		//y += ratio * sin(ratio * 20.0 + now * 1000) * 50;
		y += sin(ratio * 20.0 + now * 1000) * 50;

		// Faire bouger les formes	
		shape.move(0.01, 0.f);
		cube.move(0.01, 0.f);
		hexagone.move(0.01, 0.f);
		
		//sf::Vertex vertex(Vector2f(ofsX + stride * i, 350), i % 2 == 0 ? blue : red);
		sf::Vertex vertex(Vector2f(x, y), i % 2 == 0 ? blue : red);
		va.append(vertex);
	}
	win.draw(va);
}

float lerp(float a, float b, float r) {
	return a + (b - a) * r;
}

float rd() {
	return 1.0 * rand() / RAND_MAX;
}

//// hue: 0-360°; sat: 0.f-1.f; val: 0.f-1.f 
sf::Color hsv(int hue, float sat, float val)
{
	hue %= 360;
	while (hue < 0) hue += 360;

	if (sat < 0.f) sat = 0.f;
	if (sat > 1.f) sat = 1.f;

	if (val < 0.f) val = 0.f;
	if (val > 1.f) val = 1.f;

	int h = hue / 60;
	float f = float(hue) / 60 - h;
	float p = val * (1.f - sat);
	float q = val * (1.f - sat * f);
	float t = val * (1.f - sat * (1 - f));

	switch (h)
	{
	default:
	case 0:
	case 6: return sf::Color(val * 255, t * 255, p * 255);
	case 1: return sf::Color(q * 255, val * 255, p * 255);
	case 2: return sf::Color(p * 255, val * 255, t * 255);
	case 3: return sf::Color(p * 255, q * 255, val * 255);
	case 4: return sf::Color(t * 255, p * 255, val * 255);
	case 5: return sf::Color(val * 255, p * 255, q * 255);
	}
}

void drawCatmull(sf::RenderWindow &win, float now) {
	sf::VertexArray va(sf::LineStrip);
	sf::Color yellow = sf::Color::Yellow;
	sf::Color green = sf::Color::Green;
	int nb = 350;
	float stride = 1280.0 / nb;

	lignFollower.setPosition(0, 0);
	lignFollower.setFillColor(sf::Color::Black);	// Couleur
	lignFollower.setOutlineThickness(4);
	lignFollower.setOutlineColor(sf::Color::Yellow);

	std::vector<Vector2f> points;

	for (int j = 0; j < 8; ++j) {
		Vector2f v(j * 100, j * 100);
		if (j == 0)v.x += 100;
		if (j == 3)v.x += 200;
		points.push_back(v);
	}

	for (int i = 0; i < nb + 1; ++i) {
		double ratio = 1.0 * i / nb;
		double x = 0.0;
		double y = 0.0;
		sf::Color c = hsv(ratio * 360, 0.9, 0.9);

		Vector2f pos = Lib::plot2(ratio, points);
		x = pos.x;
		y = pos.y;

		sf::Vertex vertex(Vector2f(x, y), c);
		va.append(vertex);
	}

	static float cRatio = 0;
	//static bool invert = false;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Vector2i posMouse = sf::Mouse::getPosition(win);
		printf("Position souris :  %f\n", posMouse);
	}

	Vector2f pos = Lib::plot2(cRatio, points);
	lignFollower.setPosition(pos);

	cRatio += 0.01;
	/*
	if (cRatio > 1.0)
	{
		cRatio = 0.0;
		invert = !invert;
	}
	*/
	win.draw(va);
	win.draw(lignFollower);
}
/*
void drawMovingSquare(sf::RenderWindow &win)
{
	sh->setOrigin(48, 48);
	sh.setFillColor(Color(0x55b87Eff));
	sh.setOutlineColor(Color(0xB34139ff));
	win.draw(*sh);
}
*/
//static initMoving

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1280, 800), "SFML works!");   // Taille de la fenetre
	
	//sf::CircleShape shape(300.f, 2 * 3.141569 * 100);   // Forme
	shape.setPosition(-300, 90);
	shape.setFillColor(sf::Color::Black);	// Couleur
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::Red);

	//sf::CircleShape cube(300.f, 4);   // Forme
	cube.setPosition(-300, 90);
	cube.setFillColor(sf::Color::Black);	// Couleur
	cube.setOutlineThickness(4);
	cube.setOutlineColor(sf::Color::Red);

	//sf::CircleShape hexagone(300.f, 6);   // Forme
	hexagone.setPosition(-300, 90);
	hexagone.setFillColor(sf::Color::Black);	// Couleur
	hexagone.setOutlineThickness(4);
	hexagone.setOutlineColor(sf::Color::Red);
	
	sf::CircleShape lignFollower(25.f, 12);
	lignFollower.setPosition(0.f, 0.f);
	lignFollower.setFillColor(sf::Color::Black);	// Couleur
	lignFollower.setOutlineThickness(4);
	lignFollower.setOutlineColor(sf::Color::Yellow);

	hero.setPosition(600, 400);
	hero.setFillColor(sf::Color::Cyan);	// Couleur
	hero.setOutlineThickness(4);
	hero.setOutlineColor(sf::Color::Blue);

	window.setVerticalSyncEnabled(true);

	sf::Clock clock;
	sf::Time appStart = clock.getElapsedTime();
	sf::Time prevFrameStart = clock.getElapsedTime();
	sf::Time frameStart = clock.getElapsedTime();
	sf::Time prevFrameEnd = clock.getElapsedTime();
	sf::Time displayDuration = clock.getElapsedTime();

	float fps[4] = { 0.f, 0.f, 0.f, 0.f };
	int step = 0;

	sf::Font * font = new sf::Font();
	MemFile f;
	if (font->loadFromFile("Res/DejaVuSans.ttf") == false) {
		printf("no such font\n");
	}

	sf::Text myFpsCounter;
	int every = 0;
	
	//Vector2f mousePoint[4] = {(0, 0), (0, 0), (0, 0), (0, 0)};

	while (window.isOpen())   // Tant que la fenetre est ouverte DEBUT DE LA FRAME
	{
		sf::Event event;   // Recup les evenements clavier/souris
		frameStart = clock.getElapsedTime();

		while (window.pollEvent(event))
		{
			switch (event.type)
			{
				case sf::Event::KeyReleased :
					/*
					if (event.key.code == sf::Keyboard::A)
						printf("Display duration :  %f\n", displayDuration.asMilliseconds());
					if (event.key.code == sf::Keyboard::Z)
						printf("Current time :  %f\n", frameStart.asMilliseconds());
					if (event.key.code == sf::Keyboard::E)
						printf("FPS :  %f\n",  0.25f * (fps[0] + fps[1] + fps[2] + fps[3]));
					*/
					if (event.key.code == sf::Keyboard::A)
						printf("Instant FPS :  %f\n", fps[(step - 1) % 4]);
					if (event.key.code == sf::Keyboard::E)
						printf("FPS :  %f\n", 0.25f * (fps[0] + fps[1] + fps[2] + fps[3]));
					break;

				case sf::Event::KeyPressed :
					//if (event.key.code == sf::Keyboard::F1)
						//sf::Vector2i posMouse = sf::Mouse::getPosition(windows);
					if (event.key.code == sf::Keyboard::Q)
						//hero.x -= SquareSpeed;
						hero.move(-10.f, 0.f);
					if (event.key.code == sf::Keyboard::D)
						//hero.x += SquareSpeed;
						hero.move(10.f, 0.f);
					if (event.key.code == sf::Keyboard::Z)
						//hero.y -= SquareSpeed;
						hero.move(0.f, -10.f);
					if (event.key.code == sf::Keyboard::S)
						//hero.y += SquareSpeed;
						hero.move(0.f, 10.f);
					break;

				case sf::Event::Closed :
					window.close();
					break;
				default:
					break;
			}			
		}

		myFpsCounter.setPosition(8, 8);
		myFpsCounter.setFillColor(sf::Color::Red);
		myFpsCounter.setFont(*font);

		if (every == 0) {
			myFpsCounter.setString(std::string("FPS : ") + std::to_string(fps[(step - 1) % 4]));
			every = 30;
		}
		every--;

		window.clear();   // Nettoie la frame
		//window.draw(shape);   // On demande le dessin d'une forme
		//window.draw(hexagone);   // On demande le dessin d'une forme
		//window.draw(cube);   // On demande le dessin d'une forme
		//window.draw(lignFollower);
		window.draw(hero);
		window.draw(myFpsCounter);
		//drawCurve(window, clock);
		//drawCatmull(window, clock.getElapsedTime().asSeconds());
		window.display();   // Dessine et ça attend la vsync

		fps[step % 4] = 1.0 / (frameStart - prevFrameStart).asSeconds();
		prevFrameStart = frameStart;
		step++;
	}

	return 0;
}

// Exécuter le programme : Ctrl+F5 ou menu Déboguer > Exécuter sans débogage
// Déboguer le programme : F5 ou menu Déboguer > Démarrer le débogage

// Conseils pour bien démarrer : 
//   1. Utilisez la fenêtre Explorateur de solutions pour ajouter des fichiers et les gérer.
//   2. Utilisez la fenêtre Team Explorer pour vous connecter au contrôle de code source.
//   3. Utilisez la fenêtre Sortie pour voir la sortie de la génération et d'autres messages.
//   4. Utilisez la fenêtre Liste d'erreurs pour voir les erreurs.
//   5. Accédez à Projet > Ajouter un nouvel élément pour créer des fichiers de code, ou à Projet > Ajouter un élément existant pour ajouter des fichiers de code existants au projet.
//   6. Pour rouvrir ce projet plus tard, accédez à Fichier > Ouvrir > Projet et sélectionnez le fichier .sln.
