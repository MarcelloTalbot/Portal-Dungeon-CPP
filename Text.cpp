#include "Text.h"

Text::Text(Vec2 anchor_pos, int size, SDL_Color color, Alignment x_alignment, Alignment y_alignment) : GUIElement::GUIElement(anchor_pos, x_alignment, y_alignment, color), size(size) {//, rect(anchor_pos.x, anchor_pos.y, 0.f, 0.f) {
}

Text::~Text() {
}

void Text::setText(SDL_Renderer* renderer, TextureManager* textures, const std::string& text) {
	tex = textures->makeFontTex(renderer, font, text, color);

	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.w = static_cast<float>(w);
	rect.h = static_cast<float>(h);

	align();
}

void Text::setText(SDL_Texture* tex) {
	this->tex = tex;
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.w = static_cast<float>(w);
	rect.h = static_cast<float>(h);

	align();
}

void Text::setText(TextureManager* textures, const std::string& text) {
	tex = textures->getFontTexture(text);

	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.w = static_cast<float>(w);
	rect.h = static_cast<float>(h);

	align();
}

void Text::render(SDL_Renderer* renderer) const {
	SDL_RenderCopyF(renderer, tex, nullptr, &rect);
}
