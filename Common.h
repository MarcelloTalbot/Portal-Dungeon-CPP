#pragma once

#include <numbers>

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_ttf.h"

#include "Vec2.h"

//int screenWidth = 1280;
//int screenHeight = 720;

constexpr double half_pi = std::numbers::pi / 2.0;
constexpr double to_deg = 180.0 / std::numbers::pi;
constexpr double toDegrees(double angle) { return angle * to_deg; }//dont need in C++23 or 26

namespace Colors {
	//constexpr SDL_Color NONE{ 0x00, 0x00, 0x00, 0x00 };
	constexpr SDL_Color white{ 0xFF, 0xFF, 0xFF, 0xFF };//I had 0 before but I think means invisible with blend mode so changed to 255
	constexpr SDL_Color grey{ 0x58, 0x58, 0x58, 0xFF };
	constexpr SDL_Color black{ 0x00, 0x00, 0x00, 0xFF };
	constexpr SDL_Color blue{ 0x00, 0x00, 0xFF, 0xFF };
	constexpr SDL_Color dark_blue{ 0x00, 0x00, 0x80, 0xFF };
	constexpr SDL_Color green{ 0x00, 0xFF, 0x00, 0xFF };
	constexpr SDL_Color dark_green{ 0x00, 0x80, 0x00, 0xFF };
	constexpr SDL_Color red{ 0xFF, 0x00, 0x00, 0xFF };
	constexpr SDL_Color dark_red{ 0x80, 0x00, 0x00, 0x00 };
	constexpr SDL_Color pink{ 0xFF, 0x00, 0xFF, 0xFF };
}

inline int setRenderDrawColor(SDL_Renderer* renderer, SDL_Color color) {
	return SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

//enum Inputs {
//	Click,
//	Hold,
//	INPUT_COUNT
//};

enum Actions {//maybe move to game.h or elsewhere like player.h?
	LClick,
	LHold,
	Up,
	Down,
	Left,
	Right,
	Attack,
	Sprint,
	ACTION_COUNT
};