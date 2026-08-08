#include "PlayerGroup.h"

PlayerGroup::PlayerGroup() {
}

PlayerGroup::~PlayerGroup() {
}

void PlayerGroup::update(bool actions[ACTION_COUNT], UpdateParams& params) {
	for (auto& player : players) {
		player->update(actions, params);
	}
}

void PlayerGroup::render(SDL_Renderer* renderer) const {
	for (const auto& player : players) {
		player->render(renderer);
	}
}

void PlayerGroup::add(std::unique_ptr<Player> player) {
	players.push_back(std::move(player));
}

std::size_t PlayerGroup::getSize() {
	return players.size();
}

std::unique_ptr<Player>& PlayerGroup::getPlayer(int index) {
	return players[index];
}

void PlayerGroup::applyOffset(Vec2 offset) {
	for (std::unique_ptr<Player>& player : players) {
		player->rect.x = (player->pos.x - player->rect.w / 2) - offset.x;
		player->rect.y = (player->pos.y - player->rect.h / 2) - offset.y;
	}
}

Player& PlayerGroup::emplace(Vec2 pos, SDL_Texture* texture) {
	auto ptr = std::make_unique<Player>(pos, texture);
	Player& ref = *ptr;
	players.push_back(std::move(ptr));
	return ref;
}
