#pragma once

#include <vector>
#include <memory>

#include "Common.h"

#include "Entity.h"
#include "EntityGroup.h"
//#include "PlayerGroup.h"
//#include "Player.h"
//#include "Zombie.h"
#include "TextureManager.h"
#include "Tile.h"

class Camera {
private:
	int update_dist{ 800 };

	//Vec2 offset{};
	
	//Vec2 window_centre{};
	Vec2 window_pos{};//could be int Vec
	Vec2 level_pos{};

	//add pointer to target entity and method for tracking them
	bool is_tracking{ true };
	Entity* target;//maybe just pointer to their position unless need more about them
	
public:
	Vec2 offset{};//maybe make private?

private:
	void centreOnPos(Vec2 pos);

public:
	Camera(int window_width, int window_height);

	void render(SDL_Renderer* renderer, TextureManager* textures, TileMap& level_tile_map, EntityGroup& players, EntityGroup& zombies);

	void setWindowPos(int window_width, int window_height);
	void setLevelPos(Vec2 pos);
	void setTarget(Entity* target);
};