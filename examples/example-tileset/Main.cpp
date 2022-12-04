/**
 *  This example showcases dgm::Tileset as a way of drawing tileset based levels.
 *  Since dshlibs are included into DGM installation, it also showcases how to use LevelD
 *  class (and file format) to export and import levels. LevelD can do much more in terms
 *  of levels, it can store player, item and NPC informations, feel free to explore the
 *  data structure.
 *  You can move the yellow dot with the directional keys and test collisions with the
 *  level for yourself.
 */

#include <DGM/dgm.hpp>
#include "../shared/Level.hpp"
#include "../shared/DemoData.hpp"
#include "../ResourceDir.hpp"

class Player
{
private:
	const float SPEED = 128.f;
	const float RADIUS = 20.f;

	dgm::Circle body = dgm::Circle(100.f, 100.f, RADIUS);
	dgm::Controller input;

public:
	enum
	{
		Up, Left, Right, Down
	};

	void draw(dgm::Window& window)
	{
		// Unless you have textured sprite, you
		// can use debugRender to quicky get started
		body.debugRender(window);
	}

	void update(const dgm::Time& time, const dgm::Mesh& level)
	{
		// Compute forward vector based on use input and multiply it by delta time
		sf::Vector2f forward = sf::Vector2f(
			input.isToggled(Left) ? -SPEED : input.isToggled(Right) ? SPEED : 0.f,
			input.isToggled(Up) ? -SPEED : input.isToggled(Down) ? SPEED : 0.f
		) * time.getDeltaTime();

		// If moving body forward would result in collision with the world,
		// forward will be adjusted to avoid collision
		dgm::Collision::advanced(level, body, forward);

		// So now it is safe to use forward to move
		body.move(forward);
	}

	Player()
	{
		input.bindInput(Up, sf::Keyboard::Up);
		input.bindInput(Left, sf::Keyboard::Left);
		input.bindInput(Right, sf::Keyboard::Right);
		input.bindInput(Down, sf::Keyboard::Down);
	}
};

int main()
{
	dgm::Window window({ 1280, 720 }, "Example: Tileset", false);
	dgm::Time time;

	dgm::JsonLoader loader;
	dgm::ResourceManager resmgr(loader);
	resmgr.loadResourceDir<sf::Texture>(RESOURCE_DIR, { ".png" });

	Level level(resmgr.get<sf::Texture>("tileset.png"));
	level.loadFromLvd(DemoData::createDemoLevel2());

	Player player;

	sf::Event event;
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
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