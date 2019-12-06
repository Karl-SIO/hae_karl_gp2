#pragma once


#include <iostream>
#include <SFML/Graphics.hpp>
#include <direct.h>
#include <functional>

#include "Lib.hpp"
#include "Particle.h"
#include "Entity.hpp"
#include "Action.hpp"
#include <Box2D/Box2D.h>

using namespace sf;

class Game {
public:
	std::vector< Particle * > pvec;
	std::vector< Entity * > evec;

	Game() {

	}

	void init();
	void update(double dt);
	void draw(RenderWindow & win);
};