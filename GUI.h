#pragma once

#include <vector>
#include <memory>

#include "Common.h"

#include "GUIElement.h"

class GUI {
private:
	std::vector<std::unique_ptr<GUIElement>> elements;

public:

private:

public:
	GUI();
	~GUI();

	void update(bool actions[ACTION_COUNT], Vec2 mouse_pos);

	void render(SDL_Renderer* renderer) const;

	void add(std::unique_ptr<GUIElement> element); // Adds a unique entity pointer from elsewhere to the end of vector

	std::size_t getSize() const;

	GUIElement& getElement(int index);//hmmm a bit odd with & and unique

	void clear();

	//void checkEntityCollisions();

	//void move(double dt);//for now

	template<typename T, typename... Args> // Adds a new unique pointer to the end of vector
	T& emplace(Args&&... args) {
		static_assert(std::is_base_of_v<GUIElement, T>, "T must derive from Entity");

		auto ptr = std::make_unique<T>(std::forward<Args>(args)...);
		T& ref = *ptr;
		elements.push_back(std::move(ptr));
		return ref;
	}
};