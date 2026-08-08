#pragma once

#include "Common.h"

#include "GameState.h"

class Paused : public GameState {
public:
	Paused(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state = Gamestates::Playing);
	~Paused();
};