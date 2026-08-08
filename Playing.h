#pragma once

#include <vector>
#include <fstream>

#include "Common.h"

#include "GameState.h"

#include "Camera.h"
#include "Tile.h"

class Playing : public GameState {
public:
	Vec2 level_mouse_pos{};

	TileMap level_tile_map{};

	Camera camera{ window_rect.w / 2, window_rect.h / 2 };

	EntityGroup players{};
	EntityGroup entities{};

	UpdateParams params{ entities, level_tile_map };

public:
	Playing(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state = Gamestates::Paused);//change if I actually do want to go to prev state
	~Playing();

	void update(double dt, bool actions[ACTION_COUNT], Vec2& mouse_pos) override;

	void render() override;

	void handleInputs(bool actions[ACTION_COUNT], Vec2& mouse_pos) override;

private:
	void loadLevelTileMap(int8_t level);
	void makeLevelTexture();
	//void setLevelRect();
	TileType charToTile(const char& c);
};