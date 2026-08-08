#include "Zombie.h"
//#include "Player.h"

void Zombie::chaseTarget() {
	vel = target->pos - pos;
	
	//if (vel.x != 0 && vel.y != 0) {//always normalise?
	//	vel.normalize();
	//	vel *= speed;
	//}
	//if (vel.x == 0 && vel.y == 0) {}
	//else {
	//	vel.normalize();
	//	vel *= speed;
	//}
	vel.normalize();
	
	vel *= speed;

	rotateToPos(target->pos);
}

void Zombie::findTarget(EntityGroup& entities) {

}

Zombie::Zombie(Vec2 pos, SDL_Texture* tex) : Entity::Entity(pos, tex) {
}

Zombie::~Zombie() {
}

//void Zombie::update(double dt, std::vector<std::unique_ptr<Player>>& players, TileMap tile_map) {
void Zombie::update(bool actions[ACTION_COUNT], UpdateParams& params) {
	findCurrentTile(params.tile_map);
	chaseTarget();
	applyTileEffects();
	move(params.dt);
}