#pragma once

#include <DGM/dgm.hpp>

#include <game/EntityTable.hpp>
#include <game/FpsCounter.hpp>

class Game
{
public:
	Game(
		dgm::Camera& camera);

public:
	void update(const dgm::Time& time);

	[[nodiscard]]
	constexpr auto getFpsCounter() const noexcept
		-> FpsCounter const&
	{
		return fpsCounter;
	}

	[[nodiscard]]
	EntityTable& getEntities() noexcept
	{
		return entityTable;
	}

protected:
	// Dependencies
	dgm::Camera& camera;

	// Attributes
	FpsCounter fpsCounter;
	EntityTable entityTable = {};
};
