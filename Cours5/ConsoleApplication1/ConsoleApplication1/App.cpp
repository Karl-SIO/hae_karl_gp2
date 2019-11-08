// ConsoleApplication1.cpp : Ce fichier contient la fonction 'main'. L'exécution du programme commence et se termine à cet endroit.
//

#include "pch.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include "Lib.hpp"
#include <direct.h>

using namespace sf;

int main()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 2;

	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!");   // Taille de la fenetre
	
	sf::CircleShape shape(300.f, 2 * 3.141569 * 100);   // Forme
	shape.setPosition(35, 35);
	shape.setFillColor(sf::Color::Black);	// Couleur
	shape.setOutlineThickness(4);
	shape.setOutlineColor(sf::Color::Red);

	sf::CircleShape cube(300.f, 4);   // Forme
	cube.setPosition(35, 35);
	cube.setFillColor(sf::Color::Black);	// Couleur
	cube.setOutlineThickness(4);
	cube.setOutlineColor(sf::Color::Red);

	sf::CircleShape hexagone(300.f, 6);   // Forme
	hexagone.setPosition(35, 35);
	hexagone.setFillColor(sf::Color::Black);	// Couleur
	hexagone.setOutlineThickness(4);
	hexagone.setOutlineColor(sf::Color::Red);
	
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
					if (event.key.code == sf::Keyboard::Z)
						printf("FPS :  %f\n", 0.25f * (fps[0] + fps[1] + fps[2] + fps[3]));
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
		window.draw(shape);   // ON demande le dessin d'une forme
		window.draw(hexagone);   // ON demande le dessin d'une forme
		window.draw(cube);   // ON demande le dessin d'une forme
		window.draw(myFpsCounter);
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
