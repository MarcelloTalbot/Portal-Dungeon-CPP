#include "GameState.h"

GameState::GameState(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : window(window), renderer(renderer), textures(textures), prev_state(prev_state) {
	SDL_GetWindowPosition(window, &window_rect.x, &window_rect.y);
	SDL_GetWindowSize(window, &window_rect.w, &window_rect.h);
}

GameState::~GameState() {
}

void GameState::update(double dt, bool inputsactions[ACTION_COUNT], Vec2& mouse_pos) {
	//gui.update(inputs, mouse_pos);
}

void GameState::render() {
	gui.render(renderer);
}

void GameState::handleInputs(bool actions[ACTION_COUNT], Vec2& mouse_pos) {
	// Polling for SDL events
	SDL_Event event;

	actions[LClick] = false;

	// Loop until there are no more pending events to process
	while (SDL_PollEvent(&event) != 0) {
		switch (event.type) {
		case SDL_QUIT:
			//game_running = false; // Stop running if the window is closed
			next_state = Gamestates::QUIT;
			return;

		case SDL_MOUSEMOTION:
			mouse_pos.x = static_cast<float>(event.motion.x);
			mouse_pos.y = static_cast<float>(event.motion.y);
			break;

		case SDL_KEYDOWN:
			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
				actions[Up] = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
				actions[Down] = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
				actions[Left] = true;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
				actions[Right] = true;
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT && event.key.repeat == 0) {
				actions[Sprint] = true;
			}

			//can just do fullscreen in KEYUP to remove repeat checking
			else if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
					SDL_SetWindowFullscreen(window, 0);
				}
				else {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				//something like a function that stores the specific escape mapping (previous state for most, quit for main menu, and paused for playing)
				// like escape_mapping(); and its set in changeGameState()? or have switch cases for game_states
				//changeGameState(prev_state);
				//switch (game_state) {
				//case GameState::mainMenu: changeGameState(GameState::quit); break;
				//case GameState::playing: changeGameState(GameState::paused); break;
				//default: changeGameState(prev_state);
				//}
				//return;
				// 
				//if (prev_state != Gamestates::NONE) {}
				next_state = prev_state;
				return;
			}
			//userInput = true;
			break;

		case SDL_KEYUP:
			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
				actions[Up] = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
				actions[Down] = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
				actions[Left] = false;
			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
				actions[Right] = false;
			}

			else if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT) {
				actions[Sprint] = false;
			}

			//userInput = false;
			break;

		case SDL_MOUSEBUTTONDOWN:
			if (event.button.button == SDL_BUTTON_LEFT) {
				actions[LClick] = true;
				actions[LHold] = true;
				//click = true;
			}
			//userInput = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				actions[LHold] = false;
				//update_params.actions[Click] = false;
				//click = false;
			}
			//userInput = false;
			break;

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				window_rect.w = event.window.data1;
				window_rect.h = event.window.data2;
				//title.setAnchor(Vec2(window_width * 0.5f, 0.f));
				//add realignment to GUI stuff and make a GUI class encompassing them
			}
			//if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {

			//}
			//else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
			//	//pausing();
			//	changeGameState(GameState::paused);
			//	return;
			//}
			//else if (event.window.event == SDL_WINDOWEVENT_MOVED) {
			//	//pausing();
			//	changeGameState(GameState::paused);
			//	return;
			break;
		}
	}
}
