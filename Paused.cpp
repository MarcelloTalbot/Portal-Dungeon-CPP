#include "Paused.h"

Paused::Paused(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : GameState::GameState(window, renderer, textures, prev_state) {
	Text& title = gui.emplace<Text>(Vec2(static_cast<float>(window_rect.w) * 0.5f, 0.f), 5 * 30, Colors::white, Alignment::CentreX);
	title.font = textures.getFont("Tiny5-Regular.ttf", 150);
	title.setText(renderer, &textures, "Paused");

	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.5f), textures.getTexture("continue_up.png"), textures.getTexture("continue_down.png"), [this] {next_state = Gamestates::Playing; return; });
	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.67f), textures.getTexture("main_up.png"), textures.getTexture("main_down.png"), [this] {next_state = Gamestates::MainMenu; return; });
	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.84f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {next_state = Gamestates::Quit; return; });
}

Paused::~Paused() {
}
