#pragma once

#include <DGM/dgm.hpp>
#include <include/LevelD.hpp>

class Level
{
protected:
	dgm::Mesh mesh;
	dgm::TileMap tilemap;

public:
	void draw(dgm::Window& window)
	{
		window.draw(tilemap);
	}

	const dgm::Mesh& getMesh() const
	{
		return mesh;
	}

	void changeTileToVoid(unsigned x, unsigned y)
	{
		tilemap.changeTile(x, y, 0);
		mesh[y * mesh.getDataSize().x + x] = 0;
	}

	void loadFromFile(const std::string& filename)
	{
		LevelD lvld;
		lvld.loadFromFile(filename);

		mesh = dgm::Mesh(
			lvld.mesh.layers[0].blocks,
			sf::Vector2u(lvld.mesh.layerWidth, lvld.mesh.layerHeight),
			sf::Vector2u(lvld.mesh.tileWidth, lvld.mesh.tileHeight));

		tilemap.build(
			sf::Vector2u(lvld.mesh.tileWidth, lvld.mesh.tileHeight),
			std::vector<int>(lvld.mesh.layers[0].tiles.begin(), lvld.mesh.layers[0].tiles.end()),
			sf::Vector2u(lvld.mesh.layerWidth, lvld.mesh.layerHeight));
	}

	Level(sf::Texture& texture)
	{
		constexpr unsigned TILE_SIZE = 32;
		auto clip = dgm::Clip({ TILE_SIZE, TILE_SIZE },
			{ 0, 0, int(texture.getSize().x), int(texture.getSize().y) });

		tilemap = dgm::TileMap(texture, std::move(clip));
	}
};
