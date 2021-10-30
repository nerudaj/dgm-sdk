/**
 *  \file 10_tileset.cpp
 *
 *  \details This example showcases dgm::Tileset as a way of drawing tileset based levels.
 *  Since dshlibs are included into DGM installation, it also showcases how to use LevelD
 *  class (and file format) to export and import levels. LevelD can do much more in terms
 *  of levels, it can store player, item and NPC informations, feel free to explore the
 *  data structure.
 *  You can move the yellow dot with the directional keys and test collisions with the 
 *  level for yourself.
 */

#include <DGM/dgm.hpp>
#include "Level.hpp"
#include "../ResourceDir.hpp"

class Player {
private:
	const float SPEED = 128.f;
	const float RADIUS = 20.f;

	dgm::Circle body = dgm::Circle(100.f, 100.f, RADIUS);
	dgm::Controller input;

public:
	enum {
		Up, Left, Right, Down
	};

	void draw(dgm::Window &window) {
		// Unless you have textured sprite, you
		// can use debugRender to quicky get started
		body.debugRender(window);
	}

	void update(const dgm::Time &time, const dgm::Mesh &level) {
		// Compute forward vector based on use input and multiply it by delta time
		sf::Vector2f forward = sf::Vector2f(
			input.keyPressed(Left) ? -SPEED : input.keyPressed(Right) ? SPEED : 0.f,
			input.keyPressed(Up) ? -SPEED : input.keyPressed(Down) ? SPEED : 0.f
		) * time.getDeltaTime();

		// If moving body forward would result in collision with the world,
		// forward will be adjusted to avoid collision
		dgm::Collision::advanced(level, body, forward);

		// So now it is safe to use forward to move
		body.move(forward);
	}

	Player() {
		input.bindKeyboardKey(Up, sf::Keyboard::Up);
		input.bindKeyboardKey(Left, sf::Keyboard::Left);
		input.bindKeyboardKey(Right, sf::Keyboard::Right);
		input.bindKeyboardKey(Down, sf::Keyboard::Down);
	}
};

void exportLevel() {
	LevelD lvld;

	// Once a certain attribute of lvld is initialized, it will become the part of export
	// You don't pay for modules you don't use
	lvld.metadata.author = "dgm-examples";
	lvld.metadata.description = "Basic level for example10";
	lvld.metadata.timestamp = time(NULL);
	lvld.metadata.id = "EXAMPLE_10";
	lvld.metadata.name = "Example Level";

	// This affects collision/render size of the tiles, disregarding texture resolution
	lvld.mesh.tileWidth = 64;
	lvld.mesh.tileHeight = 64;

	lvld.mesh.layerWidth = 10;
	lvld.mesh.layerHeight = 10;
	// Indices of tiles in tileset
	LevelD::TileLayer layer;
	layer.tiles = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 2, 2, 0, 0, 0, 0, 1,
		1, 0, 2, 3, 3, 2, 0, 0, 0, 1,
		1, 0, 0, 2, 2, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 2, 1,
		1, 0, 0, 0, 0, 0, 0, 2, 2, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	// Collision information
	layer.blocks = {
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 1, 1, 1, 1, 0, 0, 0, 1,
		1, 0, 0, 1, 1, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 0, 1,
		1, 0, 0, 0, 0, 0, 0, 0, 1, 1,
		1, 0, 0, 0, 0, 0, 0, 1, 1, 1,
		1, 1, 1, 1, 1, 1, 1, 1, 1, 1,
	};
	lvld.mesh.layers.push_back(layer);

	lvld.saveToFile("level.lvd");
}

int main() {
	exportLevel();

	dgm::Window window({1280, 720}, "Example 10", false);
	dgm::Time time;

	dgm::ResourceManager resmgr;
	resmgr.setPedantic(false);
	resmgr.loadResourceDir<sf::Texture>(RESOURCE_DIR);

	Level level(resmgr.get<sf::Texture>("tileset.png"));
	level.loadFromFile("level.lvd");

	Player player;

	sf::Event event;
	while (window.isOpen()) {
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				window.close();
			}

			// Player input is handled via dgm::Controller
		}
		
		/* LOGIC */
		time.reset();

		player.update(time, level.getMesh());
		
		/* DRAW */
		window.beginDraw();
		
		level.draw(window);
		player.draw(window);

		window.endDraw();
	}

	return 0;
}