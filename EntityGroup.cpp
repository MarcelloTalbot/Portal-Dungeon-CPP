#include "EntityGroup.h"

EntityGroup::EntityGroup() {
}

EntityGroup::~EntityGroup() {
}

void EntityGroup::update(bool actions[ACTION_COUNT], UpdateParams& params) {
	for (auto& entity : entities) {
		entity->update(actions, params);
	}
}//would be faster to have render in update?

//void EntityGroup::update(double dt, EntityGroup& entities, TileMap tile_map) {}

void EntityGroup::render(SDL_Renderer* renderer) const {//maybe combine this and applyOffset as no need to loop twice but remove const
	for (const auto& entity : entities) {
		entity->render(renderer);
	}
}

void EntityGroup::add(std::unique_ptr<Entity> entity) {
	entities.push_back(std::move(entity));//maybe do && on parameter
}

std::size_t EntityGroup::getSize() const {
	return entities.size();
}

Entity& EntityGroup::getEntity(int index) {
	return *entities[index];
}

void EntityGroup::applyOffset(Vec2 offset) {
	for (auto& entity : entities) {//should make entities own applyOffset method
		entity->applyOffset(offset);
	}
}

void EntityGroup::clear() {
	entities.clear();
}

//void EntityGroup::checkEntityCollisions() {
//	for (auto& entity : entities) {
//		for (auto& other : entities) {
//			if (entity != other) {
//				if (SDL_HasIntersectionF(&entity->hitbox, &other->hitbox)) {
//					//Vec2 dir = other->pos - entity->pos;
//					//dir.normalize();
//					Vec2 dir_before = (entity->pos - entity->vel) - (other->pos - other->vel);
//					float dist_before = std::sqrtf(dir_before.x * dir_before.x + dir_before.y * dir_before.y);
//					entity->vel = entity->vel * -dist_before;//this should change
//					//other->vel -= other->vel * -1;
//				}
//			}
//		}
//	}
//}

//void EntityGroup::move(double dt) {
//	for (auto& entity : entities) {
//		entity->move(dt);
//	}
//}
