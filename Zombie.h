#pragma once

#include <vector>
#include <memory>

#include "Common.h"

#include "EntityGroup.h"
#include "Player.h"//move to .cpp if zombie.h is needed in player (no cyclic)
//#include "Entity.h"

//class Player;

class Zombie : public Entity {
private:

public:
	float health{ 10.f };
	float max_health{ 100.f };
	float health_regen{ 0.f };

	float speed{ 80.f };
	Entity* target{};

private:
	void chaseTarget();

	void findTarget(EntityGroup& entities);

public:
	Zombie(Vec2 pos, SDL_Texture* tex);
	~Zombie();

	//void update(double dt, std::vector<std::unique_ptr<Player>>& players, TileMap tile_map);
	void update(bool actions[ACTION_COUNT], UpdateParams& params) override;
};