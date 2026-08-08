#pragma once

#include <vector>

#include "Common.h"
//#include "Vec2.h"
//#include "SDL2/SDL.h"
//#include "SDL2/SDL_image.h"

//class Tile {
//private:
//
//public:
//	Vec2 pos;
//	SDL_Rect rect;
//	float friction;
//	float speed_mult;
//private:
//
//public:
//	Tile(Vec2 pos);// , SDL_Rect rect);//should use a table location as input for all the different tile type attributes
//	~Tile();
//};

enum class TileType : uint8_t {//maybe make int instead
	Empty,
	Wall,
	Grass,
	Tree,
	Mud,
	Snow,
	//Ice,
	//Water,
	COUNT
};

struct TileProperties {
	bool solid = false;
	float friction = 1.0f;
	float speed_mult = 1.0f;
	float damage = false;
};

struct TileMap {
	int width{};
	int height{};
	int tile_size{ 16 };
	std::vector<TileType> tiles{};
	Vec2 pos{};
	SDL_FRect rect{};
	SDL_Texture* tex{};

	TileMap(TileType fill = TileType::Empty);//remove fill

	inline int getTileIndex(int x, int y) const { return y * width + x; }

	TileType getTile(int x, int y);

	void setTile(int x, int y, TileType tile_type);

	void resize(int w, int h, TileType fill = TileType::Empty);

	void render(SDL_Renderer* renderer) const;

	void applyOffset(Vec2 offset);
};

const TileProperties& getTileProperties(TileType tile_type) noexcept;