#pragma once

#include <DGM/dgm.hpp>
#include <TGUI/TGUI.hpp>
#include "core/AudioPlayer.hpp"

class GuiState {
protected:
	tgui::Gui gui;
	const dgm::ResourceManager& resmgr;
	AudioPlayer& audioPlayer;

	struct ButtonProps {
		std::string label;
		std::function<void(void)> callback;
	};

protected:
	tgui::Label::Ptr createOptionLabel(tgui::Layout2d position, tgui::Layout2d size, const std::string& text);
	void createCheckbox(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, bool checked, std::function<void(bool)> onChecked, const std::string& name);
	void createSlider(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, float value, std::function<void(void)> onChange, const std::string& name, float lo = 0.f, float hi = 100.f, float step = 1.f);
	void createDropdown(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, const std::vector<std::string>& items, const std::string& selected, std::function<void(void)> onSelect, const std::string& name);

	// Creates a button that can be later retrieved from gui using id std::string("Button" + label)
	void createButton(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, std::function<void(void)> onClick);

	/**
	 *  \brief Adds a list of buttons to layout
	 * 
	 *  \param layout        Pointer to existing horizontal or vertical layout which has been added to gui
	 *  \param properties    Vector of labels and callback functions for the buttons
	 *  \param gapSize       Specifies size of the space between buttons. This should be number between 0 and 1 and it denotes percentage of the layout size
	 *  \param textAutoSize  Whether the labels should have automatic text size. This finds the optimal text size which will be shared among all buttons
	 */
	void createButtonListInLayout(tgui::BoxLayoutRatios::Ptr layout, const std::vector<ButtonProps>& properties, const float gapSize = 0.1f, const bool textAutoSize = true, const unsigned textSize = 0);

	GuiState(const dgm::ResourceManager& resmgr, AudioPlayer &audioPlayer);
};