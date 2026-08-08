#include "GUIElement.h"

GUIElement::GUIElement(Vec2 anchor_pos, Alignment x_alignment, Alignment y_alignment, SDL_Color color) : anchor_pos(anchor_pos), x_alignment(x_alignment), y_alignment(y_alignment), color(color), rect(anchor_pos.x, anchor_pos.y) {
	//align();
}

GUIElement::~GUIElement() {
}

void GUIElement::update(bool actions[ACTION_COUNT], Vec2 mouse_pos) {
}

void GUIElement::render(SDL_Renderer* renderer) const {
	setRenderDrawColor(renderer, color);
	SDL_RenderFillRectF(renderer, &rect);
}

void GUIElement::align() {
	//rect.x = anchor_pos.x - rect.w / alignment;//works if not for / 0 from Lefted. Only works for Lefted, Righted, Centred (int)
	rect.x = anchor_pos.x - (rect.w * 0.5f) * static_cast<float>(x_alignment);//works for Lefted, Centred, Righted (int)
	rect.y = anchor_pos.y - (rect.h * 0.5f) * static_cast<float>(y_alignment);
	//rect.x = anchor_pos.x - rect.w * alignment;// if Lefted = 0, Centred = 0.5, Righted = 1 but no float enums :( maybe try struct?

	//switch (alignment) {//maybe set y
	//case Lefted:
	//	rect.x = anchor_pos.x;
	//	break;
	//case Righted:
	//	rect.x = anchor_pos.x - rect.w;
	//	break;
	//case Centred:
	//	rect.x = anchor_pos.x - rect.w / 2;
	//	break;
	//}//need default?
}

void GUIElement::setAlignment(Alignment x_alignment, Alignment y_alignment) {
	this->x_alignment = x_alignment;
	this->y_alignment = y_alignment;
	align();
}

void GUIElement::setAnchor(Vec2 pos) {
	anchor_pos = pos;
	align();
}

void GUIElement::resize(Vec2 dim) {
	rect.w = dim.x;
	rect.h = dim.y;
	align();
}

void GUIElement::resize(float w, float h) {
	rect.w = w;
	rect.h = h;
	align();
}
