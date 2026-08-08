#pragma once
//dont need anymore
#include <vector>
#include <memory>

#include "Common.h"

//#include "Entity.h"
#include "Player.h"

class PlayerGroup {//should inherit from entity group
private:
	std::vector<std::unique_ptr<Player>> players{};

public:

private:

public:
	PlayerGroup();
	~PlayerGroup();

	void update(bool actions[ACTION_COUNT], UpdateParams& params);

	void render(SDL_Renderer* renderer) const;

	void add(std::unique_ptr<Player> player);

	std::size_t getSize();

	std::unique_ptr<Player>& getPlayer(int index);//hmmm a bit odd with & and unique

	void applyOffset(Vec2 offset);

	//template<typename T, typename... Args>//change to be just Player
	//T& emplace(Args&&... args) {
	//	static_assert(std::is_base_of_v<Entity, T>, "T must derive from Entity");

	//	auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
	//	T& ref = *ptr;
	//	entities.push_back(std::move(ptr));
	//	return ref;
	//}

	Player& emplace(Vec2 pos, SDL_Texture* texture);
};