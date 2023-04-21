#pragma once

#include "core/AudioPlayer.hpp"
#include "core/Settings.hpp"
#include <DGM/dgm.hpp>

class AppStateResourceLoader : public dgm::AppState
{
private:
    Settings& settings;
    dgm::JsonLoader loader;
    dgm::ResourceManager resmgr = dgm::ResourceManager(loader);
    AudioPlayer audioPlayer = AudioPlayer(CHANNEL_COUNT, resmgr);

public:
    virtual void input() override;

    virtual void update() override {}

    virtual void draw() override {}

    virtual [[nodiscard]] bool isTransparent() const noexcept override
    {
        return false;
    }

    AppStateResourceLoader(dgm::App& app, Settings& settings);
};