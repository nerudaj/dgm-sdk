#include "GuiState.hpp"
#include <algorithm>

tgui::Label::Ptr GuiState::createOptionLabel(tgui::Layout2d position, tgui::Layout2d size, const std::string& text) {
	tgui::Label::Ptr label = tgui::Label::create(text);
	label->setAutoSize(true);
	label->setSize(size);
	label->setPosition(position);
	label->setHorizontalAlignment(tgui::Label::HorizontalAlignment::Left);
	label->setVerticalAlignment(tgui::Label::VerticalAlignment::Center);
	return label;
}

void GuiState::createCheckbox(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, bool checked, std::function<void(bool)> onChange, const std::string& name) {
	auto labelPtr = createOptionLabel({ "0%", "0%" }, { "50%", "100%" }, label);

	tgui::CheckBox::Ptr checkbox = tgui::CheckBox::create();
	checkbox->setSize("10%", "100%");
	checkbox->setPosition("50%", "0%");
	checkbox->setChecked(checked);
	checkbox->connect("Changed", onChange);

	tgui::Panel::Ptr panel = tgui::Panel::create(size);
	panel->setPosition(position);
	panel->add(checkbox, name);
	panel->add(labelPtr);
	gui.add(panel);
}

void GuiState::createSlider(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, float value, std::function<void(void)> onChange, const std::string& name, float lo, float hi, float step) {
	auto labelPtr = createOptionLabel({ "0%", "0%" }, { "50%", "100%" }, label);

	tgui::Slider::Ptr slider = tgui::Slider::create(lo, hi);
	slider->setSize("50%", "60%");
	slider->setPosition("50%", "20%");
	slider->setStep(step);
	slider->setValue(value);
	slider->connect("ValueChanged", onChange);

	tgui::Panel::Ptr panel = tgui::Panel::create(size);
	panel->setPosition(position);
	panel->add(slider, name);
	panel->add(labelPtr);
	gui.add(panel);
}

void GuiState::createDropdown(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, const std::vector<std::string>& items, const std::string& selected, std::function<void(void)> onSelect, const std::string& name) {
	auto labelPtr = createOptionLabel({ "0%", "0%" }, { "50%", "100%" }, label);

	// Dropdown for selecting resolution
	tgui::ComboBox::Ptr dropdown = tgui::ComboBox::create();
	dropdown->setSize("50%", "100%");
	dropdown->setPosition("50%", "0%");
	for (auto& item : items) {
		dropdown->addItem(item, item);
	}
	dropdown->setSelectedItem(selected);
	dropdown->connect("ItemSelected", onSelect);

	tgui::Panel::Ptr panel = tgui::Panel::create(size);
	panel->setPosition(position);
	panel->add(dropdown, name);
	panel->add(labelPtr);
	gui.add(panel);
}

void GuiState::createButton(const std::string& label, tgui::Layout2d position, tgui::Layout2d size, std::function<void(void)> onClick) {
	tgui::Button::Ptr button = tgui::Button::create(label);
	button->setSize(size);
	button->setPosition(position);
	button->connect("pressed", [this, onClick]() {
		audioPlayer.playSoundOnChannel("click.wav", 0);
		onClick();
	});
	gui.add(button, "Button" + label);
}

void GuiState::createButtonListInLayout(tgui::BoxLayoutRatios::Ptr layout, const std::vector<ButtonProps>& properties, const float gapSize, const bool textAutoSize, const unsigned textSize) {
	auto removeSpaces = [] (std::string str) -> std::string {
		std::erase(str, '\s');
		return str;
	};

	for (auto& prop : properties) {
		auto btn = tgui::Button::create(prop.label);
		btn->connect("pressed", [this, prop] () {
			audioPlayer.playSoundOnChannel("click.wav", 0);
			prop.callback();
		});

		btn->setTextSize(textSize);
		layout->add(btn, "Button" + removeSpaces(prop.label));
	}

	// What the next formula means:
	// Each button has ratio of 1 and each space needs ratio of its own
	// All ratios are then summed up and percentage size of a given widget is ratio / sum
	// The formula below simply computes the ratio for given percentage size
	const float gapSizeTimesButtonCount = gapSize * properties.size();
	const float spaceRatio = gapSizeTimesButtonCount / (-gapSizeTimesButtonCount + gapSize + 1.f);
	for (unsigned i = 0; i < properties.size() - 1; i++) {
		// Inserting new space creates new widget and shifts all subsequent indices
		// thats why we need more complicated index formula
		layout->insertSpace(i * 2 + 1, spaceRatio);
	}

	if (textAutoSize) {
		unsigned minTextSize = -1;

		// In first pass, loop over all buttons and get their font sizes (already sanitized to correct value)
		// Find the smallest value
		for (auto&& prop : properties) {
			auto btn = gui.get<tgui::Button>("Button" + removeSpaces(prop.label));
			minTextSize = std::min(btn->getTextSize(), minTextSize);
		}

		// Set the smallest value to all buttons
		for (auto&& prop : properties) {
			auto btn = gui.get<tgui::Button>("Button" + removeSpaces(prop.label));
			btn->setTextSize(minTextSize);
		}
	}
}

GuiState::GuiState(const dgm::ResourceManager& resmgr, AudioPlayer& audioPlayer) : resmgr(resmgr), audioPlayer(audioPlayer) {
	gui.setFont(resmgr.get<sf::Font>("cruft.ttf"));
}
