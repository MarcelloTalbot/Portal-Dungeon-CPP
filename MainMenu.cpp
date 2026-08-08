#include "MainMenu.h"

MainMenu::MainMenu(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : GameState::GameState(window, renderer, textures, prev_state) {
	gui.emplace<Image>(Vec2(window_rect.w * 0.5f, 50.f), textures.getTexture("title.png"), Alignment::CentreX, Alignment::Top);
	GUIElement& portal_box = gui.emplace<GUIElement>(Vec2(window_rect.w * 0.5f, window_rect.h * 50.f), Alignment::CentreX, Alignment::CentreY, Colors::white);
	portal_box.resize(22.f, 24.f);

	GUIElement& sprint_bar = gui.emplace<GUIElement>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.46f + 8.f), Alignment::CentreX, Alignment::CentreY, Colors::blue);
	Button& play_btn = gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.46f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {next_state = Gamestates::Playing; return; });//probably can remove the returns

	sprint_bar.resize(play_btn.rect.w - 16.f, play_btn.rect.h - 32.f);

	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.64f), textures.getTexture("control_up.png"), textures.getTexture("control_down.png"), [this] {next_state = Gamestates::Controls; return; });
	gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.82f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {next_state = Gamestates::Quit; return; });

}

MainMenu::~MainMenu() {
}
