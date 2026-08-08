#include "Game.h"

Game::Game(SDL_Window* window, SDL_Renderer* renderer) : window(window), renderer(renderer), textures(renderer) {
	//textures.loadFont("Tiny5-Regular.ttf", 5 * 10);
	//textures.makeFontTex(renderer, textures.getFont("Tiny5-Regular.ttf", 5 * 10), "ERROR", white);

	//textures.loadFont("Tiny5-Regular.ttf", 5 * 30);
	//title.font = textures.getFont("Jersey10-Regular.ttf", 5 * 30);//magic num tut tut

	//textures.loadImage(renderer, "base_texture.png");
	//textures.loadImage(renderer, "player.png");
	//textures.loadImage(renderer, "tiles.png");
	//textures.loadImage(renderer, "zombie.png");
	//textures.loadAll();

	SDL_GetWindowPosition(window, &window_rect.x, &window_rect.y);
	SDL_GetWindowSize(window, &window_rect.w, &window_rect.h);
	//camera.setWindowCentre(window_width, window_height);//dont need now cos its in resuming/starting

	//title.setAnchor(Vec2(window_width * 0.5f, 0.f));
	//title.setText(textures.getFontTexture("ERROR"));

	//int w, h;
	//SDL_QueryTexture(textures.getTexture("title.png"), nullptr, nullptr, &w, &h);
	//main_title_rect.w = w;
	//main_title_rect.h = h;
	//main_title_rect.x = static_cast<int>((window_width - w) * 0.5);
	//main_title_rect.y = 30;// window_height * 0.2 - h * 0.5;

	//buttons.push_back(std::make_unique<Button>(Vec2(window_width * 0.5, 500.f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {game_state = GameState::playing; return; }));
	//buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.5f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {changeGameState(GameState::playing); return; });// { resuming(); return; });
	//buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.67f), textures.getTexture("control_up.png"), textures.getTexture("control_down.png"), [this] {changeGameState(GameState::controls); return; });// { toControls(); return; });
	//buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.84f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {changeGameState(GameState::quit); return; });// { game_state = GameState::playing; return; });
	//changeGameState(game_state);
	game_state = std::make_unique<MainMenu>(window, renderer, textures);
	
	//players.push_back(std::make_unique<Player>(Vec2(10.f, 10.f), textures.getTexture("player.png")));
	//players.add(std::make_unique<Player>(Vec2(10.f, 10.f), textures.getTexture("Player.png")));
	//Player& player = entities.emplace<Player>(Vec2(100.f, 100.f), textures.getTexture("player.png"));
	//loadLevelTileMap(player.level);
	//
	//Zombie& zombie = entities.emplace<Zombie>(Vec2(190.f, 190.f), textures.getTexture("zombie.png"));
	//zombie.target = &player;//remove when adding checking range for player
	//zombies = std::make_unique<Zombie>(Vec2(90.f, 90.f), textures.getTexture("zombie.png"));
	// 
	//tile_map = std::make_unique<TileMap>(textures.get("assets/images/base_texture.png"));
	//level_tile_map.tex = textures.get("assets/images/base_texture.png");

	//title.setText(renderer, &textures, "Main");

}

Game::~Game() {}

void Game::run() {
	prev_time = SDL_GetPerformanceCounter();
	freq = SDL_GetPerformanceFrequency();

	//loadLevelTileMap(players[0]->level);
	//makeLevelTexture();
	//setLevelRect();

	while (game_running) { //
		//SDL_GetWindowSize(window, &window_width, &window_height);

		current_time = SDL_GetPerformanceCounter();
		dt = static_cast<double>(current_time - prev_time) / static_cast<double>(freq);

		if (dt < target_dt) {
			SDL_Delay((Uint32)((target_dt - dt) * 1000.0));

			current_time = SDL_GetPerformanceCounter();
			dt = static_cast<double>(current_time - prev_time) / static_cast<double>(freq);
		}
		prev_time = current_time;
		
		//maybe put input detection here instead of per game state
		//maybe also have update_params update here

		// Set background color
		setRenderDrawColor(renderer, Colors::grey);//put in the GameState class

		// Clear the renderer with the current render color
		SDL_RenderClear(renderer);
		
		//switch (game_state) {
		//case GameState::playing: playing(); break;
		//case GameState::paused: paused(); break;
		//case GameState::mainMenu: mainMenu(); break;
		//case GameState::controls: controls(); break;
		//case GameState::quit: quit(); break;
		//}

		game_state->handleInputs(actions, mouse_pos);

		game_state->gui.update(actions, mouse_pos);// slightly fairer doing it here maybe and continuing when changing state but not noticeable really

		if (game_state->next_state != Gamestates::NONE) {
			prev_state = current_state;
			current_state = game_state->next_state;

			switch (game_state->next_state) {
			case Gamestates::QUIT: game_running = false; break;
			case Gamestates::MainMenu: game_state = std::make_unique<MainMenu>(window, renderer, textures); break;//change if I actually do want to go to prev state
			case Gamestates::Playing: game_state = std::make_unique<Playing>(window, renderer, textures); break;//change if I actually do want to go to prev state
			case Gamestates::Controls: game_state = std::make_unique<Controls>(window, renderer, textures, prev_state); break;
			case Gamestates::Paused: game_state = std::make_unique<Paused>(window, renderer, textures); break;//maybe not do and have as pop up or smth and change if I actually do want to go to prev state
			case Gamestates::Quit: game_state = std::make_unique<Quit>(window, renderer, textures, prev_state); break;
			}
			// maybe add a game_state->render(); here as well
			continue;
		}

		game_state->update(dt, actions, mouse_pos);

		game_state->render();

		//gui.update(update_params.actions[Click], update_params.actions[Hold], mouse_pos);
		//gui.render(renderer);

		// Render everything to the screen
		SDL_RenderPresent(renderer);
	}
}

//void Game::end() { // Can just be in the destructor I think
//	//textures.unloadAll();
//
//	// Cleanup SDL components and quit
//	SDL_DestroyRenderer(renderer);
//	SDL_DestroyWindow(window);
//	SDL_Quit();
//}

//void Game::mainMenu() {
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[LClick] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;//maybe make GameState::quit?
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//
//		case SDL_KEYDOWN://can just do fullscreen in KEYUP to remove repeat checking
//			if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				changeGameState(GameState::quit);
//				//resuming();//should make a starting function if anything different occurs
//				return;
//			}
//			userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LClick] = true;
//				//click = true;
//			}
//			userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				//update_params.actions[Click] = false;
//				//click = false;
//			}
//			userInput = false;
//			break;
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				window_rect.w = event.window.data1;
//				window_rect.h = event.window.data2;
//			}
//			break;
//		}
//	}
//	
//	// Set background color
//	//SDL_SetRenderDrawColor(renderer, 0x58, 0x58, 0x58, 0x00);
//
//	// Clear the renderer with the current render color
//	//SDL_RenderClear(renderer);
//
//	//for (auto& item : gui) {
//	//	item.render(renderer);
//	//}
//	//gui.at(0).render(renderer);
//	//Image img{ Vec2(window_width * 0.5f, 0.f), textures.getTexture("title.png"), CentreX, Upped };
//	//img.render(renderer);
//
//	//gui.render(renderer);
//	//buttons.update(update_params.actions[Click], mouse_pos);
//	//buttons.render(renderer);
//	
//	//SDL_RenderCopy(renderer, textures.getTexture("title.png"), nullptr, &main_title_rect);
//	//title.render(renderer);
//}

//void Game::controls() {
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[LClick] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//
//		case SDL_KEYDOWN://can just do fullscreen in KEYUP to remove repeat checking
//			if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				changeGameState(prev_state);
//				//resuming();
//				return;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			//userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LClick] = true;
//				//click = true;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				//update_params.actions[Click] = false;
//				//click = false;
//			}
//			//userInput = false;
//			break;
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				window_rect.w = event.window.data1;
//				window_rect.h = event.window.data2;
//			}
//			break;
//		}
//	}
//
//	// Set background color
//	//SDL_SetRenderDrawColor(renderer, 0x58, 0x58, 0x58, 0x00);
//
//	// Clear the renderer with the current render color
//	//SDL_RenderClear(renderer);
//	
//	title.render(renderer);
//	
//	//buttons.update(update_params.actions[Click], mouse_pos);
//	//buttons.render(renderer);
//}

//void Game::playing() {
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[Attack] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//			
//		case SDL_KEYDOWN:
//			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
//				actions[Up] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
//				actions[Down] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
//				actions[Left] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
//				actions[Right] = true;
//			}
//
//			else if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT && event.key.repeat == 0) {
//				actions[Sprint] = true;
//			}
//
//			else if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) {
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				//pausing();
//				changeGameState(GameState::paused);
//				return;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
//				actions[Up] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
//				actions[Down] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
//				actions[Left] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
//				actions[Right] = false;
//			}
//
//			else if (event.key.keysym.scancode == SDL_SCANCODE_LSHIFT) {
//				actions[Sprint] = false;
//			}
//
//			//userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[Attack] = true;
//				actions[LHold] = true;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LHold] = false;
//			}
//			//userInput = false;
//			break;
//
//			/*case SDL_WINDOWEVENT:
//				if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
//					screenWidth = event.window.data1;
//					screenHeight = event.window.data2;
//				}*/
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
//				
//			}
//			else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				//pausing();
//				changeGameState(GameState::paused);
//				return;
//			}
//			else if (event.window.event == SDL_WINDOWEVENT_MOVED) {
//				//pausing();
//				changeGameState(GameState::paused);
//				return;
//			}
//			//else if (event.window.event == SDL_WINDOWEVENT_LEAVE) {//and not fullscreen
//			//	pausing();
//			//	return;
//			//}
//			break;
//		}
//
//
//	}
//
//	//level_mouse_pos.x = mouse_pos.x + camera.offset.x;//only if offset is public
//	//level_mouse_pos.y = mouse_pos.y + camera.offset.y;
//	level_mouse_pos = mouse_pos + camera.offset;
//	//SDL_GetMouseState(&mouse_pos.x, &mouse_pos.y);
//
//	// Set background color
//	//SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
//
//	// Clear the renderer with the current render color
//	//SDL_RenderClear(renderer);
//
//	//if (userInput) {
//	//	SDL_SetTextureColorMod(players[0]->tex, 0x80, 0xFF, 0x80);
//	//}
//	//else {
//	//	SDL_SetTextureColorMod(players[0]->tex, 0xFF, 0xFF, 0xFF);
//	//}
//	
//	update_params.dt = dt;
//	//for (int i = 0; i < ACTION_COUNT; i++) {//change this to below (maybe remove game.actions for just update params actions
//	//	update_params.actions[i] = actions[i];
//	//}
//	//update_params.actions = actions;
//
//	update_params.m_pos = level_mouse_pos;
//
//	// Update sprites
//	players.update(update_params);//have player update first to make it easier or make attack pools and stuff
//	entities.update(update_params);
//	//entities.checkEntityCollisions();
//	//entities.move(dt);
//
//	// Render sprites
//	//camera.render(renderer, &textures, players, level_rect);
//	camera.render(renderer, &textures, level_tile_map, players, entities);
//}

//void Game::paused() {//make states classes
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[LClick] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//
//		case SDL_KEYDOWN://maybe add movement stuff so you can be holding keys before you resume
//			if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				//resuming();
//				changeGameState(GameState::playing);
//				return;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			//userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LClick] = true;
//				//click = true;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				//update_params.actions[Click] = false;
//				//click = false;
//			}
//			//userInput = false;
//			break;
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				window_rect.w = event.window.data1;
//				window_rect.h = event.window.data2;
//				title.setAnchor(Vec2(window_rect.w * 0.5f, 0.f));
//			}
//			break;
//		}
//	}
//
//	// Set background color
//	//SDL_SetRenderDrawColor(renderer, 0xFF, 0x00, 0x00, 0x00);
//
//	// Clear the renderer with the current render color
//	//SDL_RenderClear(renderer);
//
//	//SDL_RenderCopy(renderer, text_tex, nullptr, &text_rect);
//	title.render(renderer);
//
//	//buttons.update(update_params.actions[Click], mouse_pos);
//	//buttons.render(renderer);
//}

//void Game::quit() {
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[LClick] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//
//		case SDL_KEYDOWN://can just do fullscreen in KEYUP to remove repeat checking
//			if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				changeGameState(prev_state);
//				return;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			//userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LClick] = true;
//				//click = true;
//			}
//			//userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				//update_params.actions[Click] = false;
//				//click = false;
//			}
//			//userInput = false;
//			break;
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				window_rect.w = event.window.data1;
//				window_rect.h = event.window.data2;
//			}
//			break;
//		}
//	}
//
//	// Set background color
//	//SDL_SetRenderDrawColor(renderer, 0x58, 0x58, 0x58, 0x00);
//
//	// Clear the renderer with the current render color
//	//SDL_RenderClear(renderer);
//
//	title.render(renderer);
//
//	//buttons.update(update_params.actions[Click], mouse_pos);
//	//buttons.render(renderer);
//}

//void Game::changeGameState(GameState next_state) {
//	prev_state = game_state;
//	game_state = next_state;
//	//buttons.clear();
//	//gui.clear();
//
//	switch (next_state) {
//	case GameState::mainMenu: {
//		gui.emplace<Image>(Vec2(window_rect.w * 0.5f, 50.f), textures.getTexture("title.png"), Alignment::CentreX, Alignment::Top);
//		GUIElement& portal_box = gui.emplace<GUIElement>(Vec2(window_rect.w * 0.5f, window_rect.h * 50.f), Alignment::CentreX, Alignment::CentreY, Colors::white);
//		portal_box.resize(22.f, 24.f);
//
//		GUIElement& sprint_bar = gui.emplace<GUIElement>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.46f + 8.f), Alignment::CentreX, Alignment::CentreY, Colors::blue);
//		Button& play_btn = gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.46f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {changeGameState(GameState::playing); return; });//probably can remove the returns
//
//		sprint_bar.resize(play_btn.rect.w - 16.f, play_btn.rect.h - 32.f);
//
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.64f), textures.getTexture("control_up.png"), textures.getTexture("control_down.png"), [this] {changeGameState(GameState::controls); return; });
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.82f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {changeGameState(GameState::quit); return; });
//		break;
//	}
//	case GameState::loading:
//		break;
//
//	case GameState::playing: {
//		players.clear();
//		entities.clear();
//
//		SDL_GetWindowSize(window, &window_rect.w, &window_rect.h);//probably dont need here
//		camera.setWindowCentre(window_rect.w, window_rect.h);
//
//		Player& player = players.emplace<Player>(Vec2(100.f, 100.f), textures.getTexture("player.png"));
//		loadLevelTileMap(player.level);
//		makeLevelTexture();
//
//		Zombie& zombie = entities.emplace<Zombie>(Vec2(190.f, 190.f), textures.getTexture("zombie.png"));
//		zombie.target = &player;//remove when adding checking range for player
//		break;
//	}
//	case GameState::paused:
//		SDL_GetWindowSize(window, &window_rect.w, &window_rect.h);
//		title.setAnchor(Vec2(window_rect.w * 0.5f, 0.f));
//		title.setText(renderer, &textures, "Paused");
//		std::fill(std::begin(actions), std::end(actions), false);//can remove if put actions in paused
//
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.5f), textures.getTexture("continue_up.png"), textures.getTexture("continue_down.png"), [this] {changeGameState(GameState::playing); return; });
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.67f), textures.getTexture("main_up.png"), textures.getTexture("main_down.png"), [this] {changeGameState(GameState::mainMenu); return; });
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.84f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {changeGameState(GameState::quit); return; });
//		break;
//
//	case GameState::controls:
//		title.setText(renderer, &textures, "Controls");
//		gui.emplace<Button>(Vec2(window_rect.w * 0.5f, window_rect.h * 0.84f), textures.getTexture("back_up.png"), textures.getTexture("back_down.png"), [this] {changeGameState(prev_state); return; });
//		break;
//
//	case GameState::quit:
//		title.setText(renderer, &textures, "Are you sure?");
//		gui.emplace<Button>(Vec2(window_rect.w * 0.35f, window_rect.h * 0.7f), textures.getTexture("yes_up.png"), textures.getTexture("yes_down.png"), [this] {game_running = false; return; });
//		gui.emplace<Button>(Vec2(window_rect.w * 0.65f, window_rect.h * 0.7f), textures.getTexture("no_up.png"), textures.getTexture("no_down.png"), [this] {changeGameState(prev_state); return; });
//		break;
//	}
//}

//void Game::toPreviousState() {
//	//GameState temp = game_state;
//
//	switch (prev_state) {
//	case GameState::mainMenu: toMainMenu(); break;
//	case GameState::paused: pausing(); break;
//	}
//	
//	//game_state = prev_state;
//	//prev_state = temp;
//}
//
//void Game::toMainMenu() {
//	buttons.clear();
//	//buttons.push_back(std::make_unique<Button>(Vec2(window_width * 0.5, 500.f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {game_state = GameState::playing; return; }));
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.5f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {resuming(); return; });
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.67f), textures.getTexture("control_up.png"), textures.getTexture("control_down.png"), [this] {toControls(); return; });
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.84f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {game_state = GameState::playing; return; });
//
//	prev_state = game_state;
//	game_state = GameState::mainMenu;
//}
//
//void Game::pausing() {
//	SDL_GetWindowSize(window, &window_width, &window_height);
//	title.moveAnchor(Vec2(window_width * 0.5f, 0.f));
//	title.setText(renderer, &textures, "Paused");
//	std::fill(std::begin(update_params.actions), std::end(update_params.actions), false);//can remove if put actions in paused
//
//	buttons.clear();
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.5f), textures.getTexture("play_up.png"), textures.getTexture("play_down.png"), [this] {resuming(); return; });
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.67f), textures.getTexture("menu_up.png"), textures.getTexture("menu_down.png"), [this] {toMainMenu(); return; });
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.84f), textures.getTexture("quit_up.png"), textures.getTexture("quit_down.png"), [this] {game_state = GameState::playing; return; });
//
//	prev_state = game_state;
//	game_state = GameState::paused;
//}
//
//void Game::resuming() {
//	makeLevelTexture();
//	SDL_GetWindowSize(window, &window_width, &window_height);
//	camera.setWindowCentre(window_width, window_height);
//
//	prev_state = game_state;
//	game_state = GameState::playing;
//}
//
//void Game::toControls() {
//	buttons.clear();
//	buttons.emplace(Vec2(window_width * 0.5f, window_height * 0.84f), textures.getTexture("back_up.png"), textures.getTexture("back_down.png"), [this] {toPreviousState(); return; });
//
//	prev_state = game_state;
//	game_state = GameState::controls;
//}

//void Game::checkInputs() {
//	// Polling for SDL events
//	SDL_Event event;
//
//	actions[LClick] = false;
//
//	// Loop until there are no more pending events to process
//	while (SDL_PollEvent(&event) != 0) {
//		switch (event.type) {
//		case SDL_QUIT:
//			game_running = false; // Stop running if the window is closed
//			return;
//
//		case SDL_MOUSEMOTION:
//			mouse_pos.x = static_cast<float>(event.motion.x);
//			mouse_pos.y = static_cast<float>(event.motion.y);
//			break;
//
//		case SDL_KEYDOWN:
//			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
//				actions[Up] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
//				actions[Down] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
//				actions[Left] = true;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
//				actions[Right] = true;
//			}
//
//			//can just do fullscreen in KEYUP to remove repeat checking
//			else if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) { // For fullscreen
//				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
//					SDL_SetWindowFullscreen(window, 0);
//				}
//				else {
//					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
//				}
//			}
//
//			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
//				//something like a function that stores the specific escape mapping (previous state for most, quit for main menu, and paused for playing)
//				// like escape_mapping(); and its set in changeGameState()? or have switch cases for game_states
//				//changeGameState(prev_state);
//				switch (game_state) {
//				case GameState::mainMenu: changeGameState(GameState::quit); break;
//				case GameState::playing: changeGameState(GameState::paused); break;
//				default: changeGameState(prev_state);
//				}
//				return;
//			}
//			userInput = true;
//			break;
//
//		case SDL_KEYUP:
//			if (event.key.keysym.scancode == SDL_SCANCODE_W) {
//				actions[Up] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_S) {
//				actions[Down] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_A) {
//				actions[Left] = false;
//			}
//			else if (event.key.keysym.scancode == SDL_SCANCODE_D) {
//				actions[Right] = false;
//			}
//			userInput = false;
//			break;
//
//		case SDL_MOUSEBUTTONDOWN:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LClick] = true;
//				actions[LHold] = true;
//				//click = true;
//			}
//			userInput = true;
//			break;
//
//		case SDL_MOUSEBUTTONUP:
//			if (event.button.button == SDL_BUTTON_LEFT) {
//				actions[LHold] = false;
//				//update_params.actions[Click] = false;
//				//click = false;
//			}
//			userInput = false;
//			break;
//
//		case SDL_WINDOWEVENT:
//			if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//				window_rect.w = event.window.data1;
//				window_rect.h = event.window.data2;
//				title.setAnchor(Vec2(window_rect.w * 0.5f, 0.f));
//				//add realignment to GUI stuff and make a GUI class encompassing them
//			}
//			//if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {
//
//			//}
//			//else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
//			//	//pausing();
//			//	changeGameState(GameState::paused);
//			//	return;
//			//}
//			//else if (event.window.event == SDL_WINDOWEVENT_MOVED) {
//			//	//pausing();
//			//	changeGameState(GameState::paused);
//			//	return;
//			break;
//		}
//	}
//}

//void Game::loadLevelTileMap(int8_t level) {
//	std::string file = "assets/levels/test_level.txt";//"assets/levels/" + std::to_string(level) + ".txt";
//	std::ifstream in(file);
//	if (!in) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open %s", file.c_str());//SDL_GetError?
//	}
//
//	std::vector<std::string> lines;
//	std::string line;
//	size_t max_width = 0;
//
//	while (std::getline(in, line)) {
//		if (!line.empty() && line.back() == '\r') {// Windows CRLF (doesn't work for old Mac OS?)
//			line.pop_back();
//		}
//		max_width = std::max(max_width, line.size());
//		lines.push_back(line);
//	}
//
//	const int w = static_cast<int>(max_width);
//	const int h = static_cast<int>(lines.size());
//	level_tile_map.resize(w, h);//could just pass in size_t's instead and change type in def
//	
//	for (int y = 0; y < h; y++) {
//		const std::string& row = lines[y];
//		for (int x = 0; x < static_cast<int>(row.size()); x++) {
//			level_tile_map.setTile(x, y, charToTile(row[x]));
//		}
//		// Remaining cells in the row are already Empty
//	}
//}

//void Game::makeLevelTexture() {
//	SDL_Texture* level_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, level_tile_map.width * level_tile_map.tile_size, level_tile_map.height * level_tile_map.tile_size);
//	if (!level_tex) {
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create level texture: %s", SDL_GetError());
//		return;
//	}
//
//	SDL_SetRenderTarget(renderer, level_tex);
//	SDL_RenderClear(renderer);
//
//	SDL_Texture* tile_set = textures.getTexture("tiles.png");
//	int w;
//	SDL_QueryTexture(tile_set, nullptr, nullptr, &w, nullptr);
//	int tiles_per_row = w / level_tile_map.tile_size;
//	
//	for (int y = 0; y < level_tile_map.height; y++) {
//		for (int x = 0; x < level_tile_map.width; x++) {
//			TileType tile = level_tile_map.getTile(x, y);
//			int num = static_cast<int>(tile);
//
//			SDL_Rect src{};
//			src.x = ((num - 1) % tiles_per_row) * level_tile_map.tile_size;
//			src.y = ((num - 1) / tiles_per_row) * level_tile_map.tile_size;
//			src.w = level_tile_map.tile_size;
//			src.h = level_tile_map.tile_size;
//
//			SDL_Rect dst{};
//			dst.x = x * level_tile_map.tile_size;
//			dst.y = y * level_tile_map.tile_size;
//			dst.w = level_tile_map.tile_size;
//			dst.h = level_tile_map.tile_size;
//
//			SDL_RenderCopy(renderer, tile_set, &src, &dst);
//		}
//	}
//
//	SDL_SetRenderTarget(renderer, nullptr);
//
//	textures.changeTexture("level_tex", level_tex);
//	level_tile_map.tex = level_tex;// textures.getTexture("level_tex");
//}

//void Game::setLevelRect() {
//	level_rect.w = level_tile_map.width * textures.tile_size * 3.f;
//	level_rect.h = level_tile_map.height * textures.tile_size * 3.f;
//}

//TileType Game::charToTile(const char& c) {//maybe move to stand alone function or in tile type?
//	switch (c) {
//	case 'W': return TileType::Wall; break;
//	case ' ': return TileType::Grass; break;
//	case 'T': return TileType::Tree; break;
//	case 'M': return TileType::Mud; break;
//	case '.': return TileType::Snow; break;
//	default: return TileType::Empty;
//	}
//}

//void Game::updateButtons() {
//	for (const auto& button : buttons) {
//		if (button->update(update_params.actions[Click], mouse_pos)) {
//			switch (button->type) {
//			case ButtonType::gameState: game_state = button->value.game_state; return;
//			}
//		}
//		button->render(renderer);
//	}
//}
//void Game::updateButtons() {
//	for (const auto& button : buttons) {
//		button->update(update_params.actions[Click], mouse_pos);
//		button->render(renderer);
//	}
//}

//void Game::loadLevel(int level) {
//	int tile_size = 16;
//	int texW, texH;
//	SDL_QueryTexture(textures.get("assets/images/tiles.png"), 0, 0, &texW, &texH);//have error check
//	int cols = texW / tile_size;
//	int rows = texH / tile_size;
//	for (int c = 0; c < cols; c++) {
//		for (int r = 0; r < rows; r++) {
//			Tile tile(Vec2(c * tile_size, r * tile_size));
//		}
//	}
//}