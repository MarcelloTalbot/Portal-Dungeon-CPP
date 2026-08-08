#include "Camera.h"

void Camera::centreOnPos(Vec2 pos) {
	offset = pos - window_pos;
}

Camera::Camera(int window_width, int window_height) {
	setWindowPos(window_width, window_height);
}

void Camera::render(SDL_Renderer* renderer, TextureManager* textures, TileMap& level_tile_map, EntityGroup& players, EntityGroup& entities) {//check * and & are all correct
	//if (is_tracking) {
	//	level_pos = target->pos;
	//}
	//is_tracking ? level_pos = target->pos : 0;
	level_pos = players.getEntity(0).pos;// Vec2((players[0]->rect.x + players[0]->rect.w / 2), (players[0]->rect.y + players[0]->rect.h / 2));
	centreOnPos(level_pos);

	//level_tile_map.rect.x = level_tile_map.pos.x - offset.x;
	//level_tile_map.rect.y = level_tile_map.pos.y - offset.y;
	level_tile_map.applyOffset(offset);

	level_tile_map.render(renderer);

	//zombie->rect.x = (zombie->pos.x - zombie->rect.w / 2) - offset.x;
	//zombie->rect.y = (zombie->pos.y - zombie->rect.h / 2) - offset.y;

	//zombie->render(renderer);

	entities.applyOffset(offset);

	entities.render(renderer);

	//players[0]->rect.x = (players[0]->pos.x - players[0]->rect.w / 2) - offset.x;
	//players[0]->rect.y = (players[0]->pos.y - players[0]->rect.h / 2) - offset.y;
	//
	//players[0]->render(renderer);

	//for (std::unique_ptr<Player>& player : players) {
	//	player->rect.x = (player->pos.x - player->rect.w / 2) - offset.x;
	//	player->rect.y = (player->pos.y - player->rect.h / 2) - offset.y;
	//}

	//for (int i = 0; i < players.getSize(); i++) {
	//	std::unique_ptr<Entity>& entity = players.getEntity(i);
	//	entity->rect.x = (entity->pos.x - entity->rect.w / 2) - offset.x;
	//	entity->rect.y = (entity->pos.y - entity->rect.h / 2) - offset.y;
	//}
	players.applyOffset(offset);

	players.render(renderer);

}

void Camera::setWindowPos(int x, int y) {
	window_pos.x = static_cast<float>(x);
	window_pos.y = static_cast<float>(y);
}

void Camera::setLevelPos(Vec2 pos) {
	level_pos = pos;
}

void Camera::setTarget(Entity* target) {
	this->target = target;
}
