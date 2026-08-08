#pragma once

#include "Common.h"

#include "GUI.h"
#include "GUIElement.h"
#include "Image.h"
#include "Text.h"
#include "Button.h"

#include "Entity.h"
#include "EntityGroup.h"
#include "Player.h"
#include "Zombie.h"

enum class Gamestates { NONE, QUIT, MainMenu, Controls, Playing, Paused, Quit };

class GameState {
private:

public:
	SDL_Window* window;
	SDL_Renderer* renderer;
	TextureManager& textures;

	GUI gui;

	SDL_Rect window_rect{};

	Gamestates next_state{ Gamestates::NONE };
	Gamestates prev_state;

private:

public:
	GameState(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state = Gamestates::NONE);
	virtual ~GameState();

	virtual void update(double dt, bool actions[ACTION_COUNT], Vec2& mouse_pos);

	virtual void render();

	virtual void handleInputs(bool actions[ACTION_COUNT], Vec2& mouse_pos);
};