#include "GUI.h"

GUI::GUI() {
}

GUI::~GUI() {
}

void GUI::update(bool actions[ACTION_COUNT], Vec2 mouse_pos) {
	for (const auto& element : elements) {
		element->update(actions, mouse_pos);
	}
}

void GUI::render(SDL_Renderer* renderer) const {
	for (const auto& element : elements) {
		element->render(renderer);
	}
}

void GUI::add(std::unique_ptr<GUIElement> element) {
	elements.push_back(std::move(element));//maybe do && on parameter
}

std::size_t GUI::getSize() const {
	return elements.size();
}

GUIElement& GUI::getElement(int index) {
	return *elements[index];
}

void GUI::clear() {
	elements.clear();
}
