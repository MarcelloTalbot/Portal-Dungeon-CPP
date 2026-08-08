#include "ButtonGroup.h"

void ButtonGroup::update(bool actions[ACTION_COUNT], Vec2 mouse_pos) {
	for (const auto& button : buttons) {
		button->update(actions, mouse_pos);
	}
}

void ButtonGroup::render(SDL_Renderer* renderer) const {
	for (const auto& button : buttons) {
		button->render(renderer);
	}
}

void ButtonGroup::clear() {
	buttons.clear();
}

void ButtonGroup::realign() {

}
