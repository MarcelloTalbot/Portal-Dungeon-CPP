#pragma once

#include "Common.h"
#include "Entity.h"

//class Zombie;

class Player : public Entity {
private:

public:
	int8_t level{ 0 };//maybe int

	float health{ 100.f };
	float max_health{ 100.f };
	float health_regen{ 0.f };

	float speed{ 100.f };
	float sprint_vel_mult{ 2.f };
	float sprint_cost{ 0.5f };

	float energy{ 50.f };
	float max_energy{ 50.f };
	float energy_regen{ 0.2f };
	SDL_FRect energy_bar{ 300, 900, 1000, 10 };//will set with window size and stuff
	SDL_FRect energy_bar_border{ 300, 900, 1000, 10 };

private:
	void setVelocity(bool actions[]); // Sets the velocity based on inputs.

	void sprint(bool actions[]);

	void update_bars() override;

public:
	Player(Vec2 pos, SDL_Texture* tex);
	~Player();

	void update(bool actions[ACTION_COUNT], UpdateParams& params) override;

	void render(SDL_Renderer* renderer) const override;

	void applyOffset(Vec2 offset) override;
};