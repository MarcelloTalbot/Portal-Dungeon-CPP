#pragma once

#include <algorithm>

#include "Common.h"
#include "Tile.h"

class EntityGroup;//could just have a higher Group.h that is included and use that instead or just move UpdateParams and don't need this

//maybe move update params?
struct UpdateParams {//or just make handling inputs in player outside update and call before
	EntityGroup& entities;
	TileMap& tile_map;
	//bool actions[ACTION_COUNT];//make it a bitset
	double dt{};
	Vec2 m_pos{};//maybe should be called level_mouse_pos
};

class Entity {
private:

public:
	Vec2 pos{};
	Vec2 vel{};
	Vec2 corrected_vel{};
	double angle{};

	SDL_Texture* tex{};
	SDL_FRect hitbox{};
	SDL_FRect rect{};

	TileType current_tile{};
	
	float health{ 100.f };
	float max_health{ 100.f };
	float health_regen{ 0.f };
	SDL_FRect health_bar{};
	SDL_FRect health_bar_border{};

	float speed{ 100.f };
	
private:

public:
	Entity(Vec2 pos, SDL_Texture* tex);
	virtual ~Entity();

	virtual void update(bool actions[ACTION_COUNT], UpdateParams& params);

	virtual void render(SDL_Renderer* renderer) const;//make const?

	virtual void applyOffset(Vec2 offset);
	//below could be private?
	virtual void move(double dt);

	virtual void rotateToPos(Vec2 other);//maybe make private

	virtual void findCurrentTile(TileMap& tile_map);

	virtual void applyTileEffects();

	virtual void checkEntityCollisions(Entity& entity);

	// virtual void checkTileCollisions(TileMap& tile_map);

	virtual void update_bars();
};
