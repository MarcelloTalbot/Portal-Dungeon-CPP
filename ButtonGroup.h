#pragma once

#include <vector>
#include <memory>

#include "Common.h"

#include "Button.h"

class ButtonGroup {
private:
	std::vector<std::unique_ptr<Button>> buttons;

public:

private:

public:
	void update(bool actions[ACTION_COUNT], Vec2 m_pos);

	void render(SDL_Renderer* renderer) const;

	void clear();

	void realign();

	template<typename... Args> //should it be template? I could just specify that parameters for the Button class?
	Button& emplace(Args&&... args) {
		auto ptr = std::make_unique<Button>(std::forward<Args>(args)...);
		Button& ref = *ptr;
		buttons.push_back(std::move(ptr));
		return ref;
	}

	//void add(Button button)
};