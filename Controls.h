#pragma once

#include "Common.h"

#include "GameState.h"

class Controls : public GameState {
public:
	Controls(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state);
	~Controls();
};