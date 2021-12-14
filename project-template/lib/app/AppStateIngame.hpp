#pragma once

#include <DGM\dgm.hpp>
#include "core/Settings.hpp"
#include "events/Events.hpp"

class Actor {
private:
	sf::Sprite sprite;
	dgm::Animation animation;

public:
	void draw(dgm::Window& window) {
		window.draw(sprite);
	}

	void update(const dgm::Time& time) {
		animation.update(time);
	}

	void setAnimationState(const std::string& state) {
		animation.setState(state);
	}

	void setTexture(sf::Texture& texture) {
		sprite.setTexture(texture);
	}

	void setAnimationStates(std::shared_ptr<dgm::AnimationStates>& states) {
		animation = dgm::Animation(states, 15);
		animation.bindSprite(sprite);
		animation.setState("idle-left");
	}

	[[nodiscard]] sf::Vector2f getPosition() const {
		return sprite.getPosition();
	}

	Actor() {
		sprite.setPosition(100.f, 300.f);
	}
};

class AppStateIngame : public dgm::AppState {
private:
	const dgm::ResourceManager &resmgr;
	Settings &settings;
	AudioPlayer& audioPlayer;

	EntityTable entityTable = {
		audioPlayer
	};
	EventProcessor eventProcessor = EventProcessor(entityTable);
	sf::View worldView, hudView;
	dgm::Camera camera = dgm::Camera(worldView);

#ifdef _DEBUG
	sf::Text fpsCounterText;
#endif
	sf::Text text;
	Actor actor;

protected:
	void setupViews();

public:
	virtual void input() override;
	virtual void update() override;
	virtual void draw() override;
	virtual [[nodiscard]] bool isTransparent() const noexcept override {
		return false;
	}

	virtual void restoreFocus() override {
		setupViews();
	}

	AppStateIngame(dgm::App &app, const dgm::ResourceManager& resmgr, Settings& settings, AudioPlayer& audioPlayer);
};