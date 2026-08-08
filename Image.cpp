#include "Image.h"

Image::Image(Vec2 anchor_pos, SDL_Texture* tex, Alignment x_alignment, Alignment y_alignment) : GUIElement::GUIElement(anchor_pos, x_alignment, y_alignment), tex(tex) {
	int w, h;
	SDL_QueryTexture(tex, nullptr, nullptr, &w, &h);
	rect.w = static_cast<float>(w);
	rect.h = static_cast<float>(h);
	align();
}

Image::~Image() {
}

void Image::render(SDL_Renderer* renderer) const {
	SDL_RenderCopyF(renderer, tex, nullptr, &rect);
}
