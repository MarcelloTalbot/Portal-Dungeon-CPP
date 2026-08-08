#pragma once

#include "Common.h"

#include "GameState.h"

class Quit : public GameState {
public:
	Quit(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state);
	~Quit();
};
