#include "Tile.h"

//Tile::Tile(Vec2 pos) : pos(pos) {//, SDL_Rect rect) : pos(pos), rect(rect) {
//}

//Tile::~Tile()
//{
//}

TileMap::TileMap(TileType fill) {}//, tiles(w* h, fill) {}

TileType TileMap::getTile(int x, int y) {
	return tiles[getTileIndex(x, y)];
}

void TileMap::setTile(int x, int y, TileType tile_type) {
	int loc = getTileIndex(x, y);
	tiles[loc] = tile_type;
}

void TileMap::resize(int w, int h, TileType fill) {
	width = w;
	height = h;
	rect.w = w * tile_size * 3.f;
	rect.h = h * tile_size * 3.f;
	tiles.resize(w * h, fill);//cast needed if it goes past integer limit
}

void TileMap::render(SDL_Renderer* renderer) const {
	SDL_RenderCopyF(renderer, tex, nullptr, &rect);
}

void TileMap::applyOffset(Vec2 offset) {
	rect.x = pos.x - offset.x;
	rect.y = pos.y - offset.y;
}

const TileProperties& getTileProperties(TileType tile_type) noexcept {
	static const TileProperties tile_properties[static_cast<size_t>(TileType::COUNT)] = {
		//	solid,	friction,	speed_mult,	damage
		{	false,	1.0f,		1.0f,		false}, // Empty
		{	true,	1.0f,		1.0f,		false}, // Wall
		{	false,	1.0f,		1.0f,		false}, // Grass
		{	true,	1.0f,		1.0f,		false}, // Tree
		{	false,	1.0f,		0.5f,		false}, // Mud
		{	false,	1.0f,		0.7f,		false}, // Snow
		//{	false,	0.5f,		0.5f,		false}, // Ice
		//{	false,	1.0f,		0.6f,		false}, // Water
	};
	return tile_properties[static_cast<size_t>(tile_type)];
}
