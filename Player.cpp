#include "Player.h"
//#include "Zombie.h"

Player::Player(Vec2 pos, SDL_Texture* tex) : Entity::Entity(pos, tex) {}

Player::~Player() {}

void Player::update(bool actions[ACTION_COUNT], UpdateParams& params) {
	findCurrentTile(params.tile_map);
	setVelocity(actions);
	applyTileEffects();
	// checkTileCollisions(params.tile_map);
	//checkEntityCollisions();
	move(params.dt);
	rotateToPos(params.m_pos);
	update_bars();
}

void Player::render(SDL_Renderer* renderer) const {
	SDL_RenderCopyExF(renderer, tex, nullptr, &rect, toDegrees(angle), nullptr, SDL_FLIP_NONE);

	setRenderDrawColor(renderer, Colors::dark_blue);
	SDL_RenderFillRectF(renderer, &energy_bar_border);

	setRenderDrawColor(renderer, Colors::blue);
	SDL_RenderFillRectF(renderer, &energy_bar);
}

void Player::applyOffset(Vec2 offset) {
	rect.x = (pos.x - rect.w * 0.5f) - offset.x;
	rect.y = (pos.y - rect.h * 0.5f) - offset.y;
}

void Player::setVelocity(bool actions[]) {
	vel.x = vel.y = 0.0;

	if (actions[Up]) {
		vel.y -= speed;
	}
	if (actions[Down]) {
		vel.y += speed;
	}
	if (actions[Left]) {
		vel.x -= speed;
	}
	if (actions[Right]) {
		vel.x += speed;
	}
	
	if (vel.x != 0 && vel.y != 0) {
		vel.normalize();
		vel *= speed;
	}

	sprint(actions);
}

void Player::sprint(bool actions[]) {
	if (actions[Sprint]) {
		if (energy > sprint_cost) {
			vel *= sprint_vel_mult;
			energy -= sprint_cost;
			if (energy < 0) {
				energy = 0;
			}
		}
		else {//can add recharge delay here by delaying when it becomes false
			actions[Sprint] = false;
			//or
			//energy += energy_regen;
			//if (energy > max_energy) {
			//	energy = max_energy;
			//}
		}
	}
	//and or this with not the // above this separates regen and cost so they dont fight
	//else {
	//	energy += energy_regen;
	//	if (energy > max_energy) {
	//		energy = max_energy;
	//	}
	//}
	energy += energy_regen;
	if (energy > max_energy) {
		energy = max_energy;
	}
	//or
	//if (energy > max_energy) {
	//	energy = max_energy;
	//}
	//else {
	//	energy += energy_regen;
	//}
	//energy = energy + trunc((max_energy - energy)/energy_regen) + fmodf() //hmmm trying to do it mathy without any ifs idk
}

void Player::update_bars() {
	health_bar.w = (health / max_health) * health_bar_border.w;
	energy_bar.w = (energy / max_energy) * energy_bar_border.w;
}
