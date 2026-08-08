#include "Quit.h"

Quit::Quit(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : GameState::GameState(window, renderer, textures, prev_state) {
	Text& title = gui.emplace<Text>(Vec2(static_cast<float>(window_rect.w) * 0.5f, 0.f), 5 * 30, Colors::white, Alignment::CentreX);
	title.font = textures.getFont("Tiny5-Regular.ttf", 150);
	title.setText(renderer, &textures, "Are you sure?");

	gui.emplace<Button>(Vec2(window_rect.w * 0.35f, window_rect.h * 0.7f), textures.getTexture("yes_up.png"), textures.getTexture("yes_down.png"), [this] {next_state = Gamestates::QUIT; return; });
	gui.emplace<Button>(Vec2(window_rect.w * 0.65f, window_rect.h * 0.7f), textures.getTexture("no_up.png"), textures.getTexture("no_down.png"), [this] {next_state = this->prev_state; return; });
}

Quit::~Quit() {
}
