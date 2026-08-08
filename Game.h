#pragma once
//#include <stdio.h>
#include <vector>
#include <memory>
#include <fstream>

#include "Common.h"

#include "TextureManager.h"
#include "GameState.h"
#include "MainMenu.h"
#include "Playing.h"
#include "Paused.h"
#include "Controls.h"
#include "Quit.h"

#include "GUI.h"
#include "GUIElement.h"
#include "Image.h"
#include "Text.h"
#include "Button.h"

//#include "ButtonGroup.h"//dont need anymore

#include "Camera.h"
#include "Tile.h"
#include "EntityGroup.h"
//#include "PlayerGroup.h"
//#include "Entity.h"
#include "Player.h"
#include "Zombie.h"

class Game {
private:
	Uint64 prev_time{};
	Uint64 current_time{};
	Uint64 freq{};
	double dt{};
	double target_fps{ 60.0 };
	double target_dt{ 1.0 / target_fps };

	bool game_running{ true };
	
	SDL_Window* window;
	SDL_Renderer* renderer;

	//int window_width;
	//int window_height;
	SDL_Rect window_rect;

	TextureManager textures;//* ?

	//Text title{ Vec2(640.f, 0.f), 5 * 30, Colors::white, Alignment::CentreX };
	//SDL_Rect main_title_rect{};

	//GUI gui;

	//enum class GameState { mainMenu, controls, playing, paused, quit };
	//GameState game_state = GameState::mainMenu;
	//GameState prev_state = game_state;
	std::unique_ptr<GameState> game_state;
	Gamestates current_state{ Gamestates::MainMenu };
	Gamestates prev_state{ Gamestates::NONE };

	//ButtonGroup buttons;
	//std::vector<std::unique_ptr<Button>> buttons;

	//Camera camera{ window_width, window_height };

	EntityGroup players;
	EntityGroup entities;

	
	//bool click{ false };
	//bool actions[ACTION_COUNT]{ false };//dont need now as its in update params
	
	//Vec2 level_mouse_pos{};

	//TileMap level_tile_map{};
	//std::unique_ptr<TileMap> tile_map;
	//SDL_FRect level_rect{};

	//bool userInput{ false };
	Vec2 mouse_pos{};//maybe make SDL_Point or FPoint0
	bool actions[ACTION_COUNT]{ false };//make it a bitset
	//UpdateParams update_params{ entities, level_tile_map };

public:

private:
	//void mainMenu();
	//void controls();
	//void playing();
	//void paused();
	//void quit();

	//void changeGameState(GameState next_state);
	//void toPreviousState();

	//void toMainMenu();
	//void pausing();
	//void resuming();
	//void toControls();
	//void checkInputs();

	//void loadLevelTileMap(int8_t level);
	//void makeLevelTexture();
	//void setLevelRect();
	//TileType charToTile(const char& c);

	//void updateButtons();

public:
	Game(SDL_Window* window, SDL_Renderer* renderer);
	~Game();

	//void load();
	void run();
	//void end();//remove?
};