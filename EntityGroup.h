#pragma once

#include <vector>
#include <memory>

#include "Common.h"

#include "Entity.h"
//#include "PlayerGroup.h"

class EntityGroup {
private:
	std::vector<std::unique_ptr<Entity>> entities;

public:

private:

public:
	EntityGroup();
	~EntityGroup();

	void update(bool actions[ACTION_COUNT], UpdateParams& params);

	void render(SDL_Renderer* renderer) const;

	void add(std::unique_ptr<Entity> entity); // Adds a unique entity pointer from elsewhere to the end of vector

	std::size_t getSize() const;

	Entity& getEntity(int index);//hmmm a bit odd with & and unique

	void applyOffset(Vec2 offset);

	void clear();

	//void checkEntityCollisions();

	//void move(double dt);//for now

	template<typename T, typename... Args> // Adds a new unique pointer to the end of vector
	T& emplace(Args&&... args) {
		static_assert(std::is_base_of_v<Entity, T>, "T must derive from Entity");

		auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
		T& ref = *ptr;
		entities.push_back(std::move(ptr));
		return ref;
	}
};