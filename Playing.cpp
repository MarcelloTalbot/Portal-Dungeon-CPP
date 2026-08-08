#include "Playing.h"

Playing::Playing(SDL_Window* window, SDL_Renderer* renderer, TextureManager& textures, Gamestates prev_state) : GameState::GameState(window, renderer, textures, prev_state) {
	Player& player = players.emplace<Player>(Vec2(100.f, 100.f), textures.getTexture("player.png"));

	//if (textures.getTexture("level_tex") != textures.base_texture) { this would work if make base_texture public but then would log error so dont want?
	loadLevelTileMap(player.level);

	level_tile_map.tex = textures.findTexture("level_tex");
	if (!level_tile_map.tex) {//or I could unload it every time you leave the Playing state? It could be quite a big image 
		makeLevelTexture();
	}
	//if (textures.isTexture("level_tex")) {
	//	textures.getTexture("level_tex");
	//}
	//else {
	//	makeLevelTexture();
	//}

	Zombie& zombie = entities.emplace<Zombie>(Vec2(190.f, 190.f), textures.getTexture("zombie.png"));
	zombie.target = &player;//remove when adding checking range for player
}

Playing::~Playing() {
}

void Playing::update(double dt, bool actions[ACTION_COUNT], Vec2& mouse_pos) {
	level_mouse_pos = mouse_pos + camera.offset;

	params.dt = dt;
	params.m_pos = level_mouse_pos;

	// Update sprites
	players.update(actions, params);//have player update first to make it easier or make attack pools and stuff
	entities.update(actions, params);
}

void Playing::render() {
	camera.render(renderer, &textures, level_tile_map, players, entities);

	GameState::render();
}

void Playing::handleInputs(bool actions[ACTION_COUNT], Vec2& mouse_pos) {
	// Polling for SDL events
	SDL_Event event;

	actions[LClick] = false;
	actions[Attack] = false;

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

			else if (event.key.keysym.scancode == SDL_SCANCODE_F11 && event.key.repeat == 0) {
				if (SDL_GetWindowFlags(window) & SDL_WINDOW_FULLSCREEN_DESKTOP) {
					SDL_SetWindowFullscreen(window, 0);
				}
				else {
					SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN_DESKTOP);
				}

			}
			else if (event.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
				next_state = prev_state;//change if I actually do want to go to prev state
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
				actions[Attack] = true;
			}
			//userInput = true;
			break;

		case SDL_MOUSEBUTTONUP:
			if (event.button.button == SDL_BUTTON_LEFT) {
				actions[LHold] = false;
			}
			//userInput = false;
			break;

		//case SDL_WINDOWEVENT:
		//	if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
		//		screenWidth = event.window.data1;
		//		screenHeight = event.window.data2;
		//	}

		case SDL_WINDOWEVENT:
			if (event.window.event == SDL_WINDOWEVENT_MAXIMIZED) {

			}
			else if (event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
				next_state = prev_state;//change if I actually do want to go to prev state
				return;
			}
			else if (event.window.event == SDL_WINDOWEVENT_MOVED) {
				next_state = prev_state;//change if I actually do want to go to prev state
				return;
			}
			//else if (event.window.event == SDL_WINDOWEVENT_LEAVE) {//and not fullscreen
			//	pausing();
			//	return;
			//}
			break;
		}
	}
}

void Playing::loadLevelTileMap(int8_t level) {
	std::string file = "assets/levels/test_level.txt";//"assets/levels/" + std::to_string(level) + ".txt";
	std::ifstream in(file);
	if (!in) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't open %s", file.c_str());//SDL_GetError?
	}

	std::vector<std::string> lines;
	std::string line;
	size_t max_width = 0;

	while (std::getline(in, line)) {
		if (!line.empty() && line.back() == '\r') {// Windows CRLF (doesn't work for old Mac OS?)
			line.pop_back();
		}
		max_width = std::max(max_width, line.size());
		lines.push_back(line);
	}

	const int w = static_cast<int>(max_width);
	const int h = static_cast<int>(lines.size());
	level_tile_map.resize(w, h);//could just pass in size_t's instead and change type in def

	for (int y = 0; y < h; y++) {
		const std::string& row = lines[y];
		for (int x = 0; x < static_cast<int>(row.size()); x++) {
			level_tile_map.setTile(x, y, charToTile(row[x]));
		}
		// Remaining cells in the row are already Empty
	}
}

void Playing::makeLevelTexture() {
	SDL_Texture* level_tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, level_tile_map.width * level_tile_map.tile_size, level_tile_map.height * level_tile_map.tile_size);
	if (!level_tex) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create level texture: %s", SDL_GetError());
		return;
	}

	SDL_SetRenderTarget(renderer, level_tex);
	SDL_RenderClear(renderer);

	SDL_Texture* tile_set = textures.getTexture("tiles.png");
	int w;
	SDL_QueryTexture(tile_set, nullptr, nullptr, &w, nullptr);
	int tiles_per_row = w / level_tile_map.tile_size;

	for (int y = 0; y < level_tile_map.height; y++) {
		for (int x = 0; x < level_tile_map.width; x++) {
			TileType tile = level_tile_map.getTile(x, y);
			int num = static_cast<int>(tile);

			SDL_Rect src{};
			src.x = ((num - 1) % tiles_per_row) * level_tile_map.tile_size;
			src.y = ((num - 1) / tiles_per_row) * level_tile_map.tile_size;
			src.w = level_tile_map.tile_size;
			src.h = level_tile_map.tile_size;

			SDL_Rect dst{};
			dst.x = x * level_tile_map.tile_size;
			dst.y = y * level_tile_map.tile_size;
			dst.w = level_tile_map.tile_size;
			dst.h = level_tile_map.tile_size;

			SDL_RenderCopy(renderer, tile_set, &src, &dst);
		}
	}

	SDL_SetRenderTarget(renderer, nullptr);

	textures.changeTexture("level_tex", level_tex);
	level_tile_map.tex = level_tex;// textures.getTexture("level_tex");
}

//void Playing::setLevelRect() {
//	level_rect.w = level_tile_map.width * textures.tile_size * 3.f;
//	level_rect.h = level_tile_map.height * textures.tile_size * 3.f;
//}

TileType Playing::charToTile(const char& c) {//maybe move to stand alone function or in tile type?
	switch (c) {
	case 'W': return TileType::Wall; break;
	case ' ': return TileType::Grass; break;
	case 'T': return TileType::Tree; break;
	case 'M': return TileType::Mud; break;
	case '.': return TileType::Snow; break;
	default: return TileType::Empty;
	}
}