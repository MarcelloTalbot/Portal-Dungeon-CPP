#pragma once

#include "Common.h"

#include "GameState.h"

class MainMenu : public GameState {
public:
	MainMenu(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state = Gamestates::Quit);
	~MainMenu();
};