#include "Controls.h"

Controls::Controls(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : GameState::GameState(window, renderer, textures, prev_state) {
	Text& title = gui.emplace<Text>(Vec2(static_cast<float>(window_rect.w) * 0.5f, 0.f), 5 * 30, Colors::white, Alignment::CentreX);
	title.font = textures.getFont("Tiny5-Regular.ttf", 150);
	title.setText(renderer, &textures, "Controls");

	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.84f), textures.getTexture("back_up.png"), textures.getTexture("back_down.png"), [this] {next_state = this->prev_state; return; });
}

Controls::~Controls() {
}
