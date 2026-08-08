#pragma once

#include <functional>

#include "Common.h"

#include "Image.h"

//enum class Game::GameState;
//
//struct ButtonValues {
//	Game::GameState game_state{};
//};
//
//enum class ButtonType { gameState };

class Button : public Image{
private:

public:
	SDL_Texture* up_tex{};
	SDL_Texture* down_tex{};

	SDL_FRect hitbox{};
	//ButtonValues value;
	//ButtonType type;
	std::function<void()> action;

private:

public:
	Button(Vec2 anchor_pos, SDL_Texture* up_tex, SDL_Texture* down_tex, std::function<void()> action = {}, Alignment x_alignment = Alignment::CentreX, Alignment y_alignment = Alignment::CentreY);
	~Button();

	void update(bool actions[ACTION_COUNT], Vec2 mouse_pos) override;
};