#include "Button.h"

Button::Button(Vec2 anchor_pos, SDL_Texture* up_tex, SDL_Texture* down_tex, std::function<void()> action, Alignment x_alignment, Alignment y_alignment) : Image::Image(anchor_pos, up_tex, x_alignment, y_alignment), up_tex(up_tex), down_tex(down_tex), action(action) {
}

Button::~Button() {
}

void Button::update(bool actions[ACTION_COUNT], Vec2 mouse_pos) {//return bool before
	SDL_FPoint point(mouse_pos.x, mouse_pos.y);
	if (SDL_PointInFRect(&point, &rect)) {
		tex = down_tex;
		//return click;
		if (actions[LClick]) {
			if (action) {// dont need?
				action();
			}
		}
	}
	else {
		tex = up_tex;
	}
	//return false;
}