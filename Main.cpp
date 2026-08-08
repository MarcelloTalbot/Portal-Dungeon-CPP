//#include <cstdlib>

#include "Game.h"

int main(int argc, char* argv[]) {

	// Initialize SDL video subsystem
	if (SDL_Init(SDL_INIT_VIDEO)) {//maybe do if (SDL_Init(SDL_INIT_VIDEO) != 0) {
		// There was an error initializing SDL
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest");

	// Initialise IMG system
	if (!IMG_Init(IMG_INIT_PNG)) {//only ! if one flag
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize IMG: %s", IMG_GetError());
		return EXIT_FAILURE;
	}

	// Initialise TTF for text
	if (TTF_Init()) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialise TTF: %s", TTF_GetError());
		return EXIT_FAILURE;
	}

	// Window size if display info not found
	int window_width = 1280;
	int window_height = 720;

	// Getting display information
	SDL_DisplayMode dm;
	if (!SDL_GetDesktopDisplayMode(0, &dm)) {
		window_width = static_cast<int>(dm.w * 0.8);
		window_height = static_cast<int>(dm.h * 0.8);
	}
	else {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't find desktop size as SDL_GetDesktopDisplayMode failed: %s", SDL_GetError());
	}
	
	// Create window
	SDL_Window* window = SDL_CreateWindow("Portal Dungeon", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP);
	if (!window) { // If window couldn't be created, log error and exit
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create window: %s", SDL_GetError());
		return EXIT_FAILURE;
	}//icon doesnt appear at top left when set to fullscreen immediately?

	
	//SDL_SetWindowMinimumSize(window, window_width, window_height);
	
	// EXE path
	char* base_path = SDL_GetBasePath();
	if (!base_path) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetBasePath failed: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	// Set window icon
	std::string icon_path = std::string(base_path) + "assets/images/icon.png";
	SDL_free(base_path);

	SDL_Surface* icon = IMG_Load(icon_path.c_str());
	if (!icon) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't load icon image 'assets/images/icon.png': %s", SDL_GetError());
	}
	else {
		SDL_SetWindowIcon(window, icon);
		SDL_FreeSurface(icon);
	}

	// Initialise renderer
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!renderer) { // If renderer couldn't be created, log error and exit
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create renderer: %s", SDL_GetError());
		return EXIT_FAILURE;
	}

	{
		Game game(window, renderer);
		
		game.run();
	}

	// Cleanup SDL components and quit
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);

	TTF_Quit();
	IMG_Quit();
	SDL_Quit();

	return EXIT_SUCCESS;
}