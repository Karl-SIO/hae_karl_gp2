#include "Game.hpp"
#include "Entity.hpp"
#include <SFML/Graphics.hpp>

using namespace sf;

void Game::init()
{
	RectangleShape *sh = new RectangleShape(Vector2f(12, 24));
	sh->setFillColor(sf::Color::Magenta);
	sh->setOrigin(6, 24);

	Entity * ent = new Entity(sh);
	ent->setPos(100, 100);
	evec.push_back(ent);
}

void Game::update(double dt)
{
	for (auto it = evec.begin(); it != evec.end();)
	{
		Entity * ent = *it;
		ent->update(dt);
		it++;
	}
}

void Game::draw(RenderWindow & win)
{
	for (auto it = evec.begin(); it != evec.end();)
	{
		Entity * ent = *it;
		ent->draw(win);
		it++;
	}

	for (auto it = pvec.begin(); it != pvec.end();) 
	{
		Particle * p = *it;
		p->update();
		if (p->killed) {
			it = pvec.erase(it);
		}
		else {
			p->draw(win);
			it++;
		}
	}

	RectangleShape line(Vector2f(1000, 1));
	line.setPosition(100, 100);
	line.setFillColor(sf::Color::Red);
	win.draw(line);
}
