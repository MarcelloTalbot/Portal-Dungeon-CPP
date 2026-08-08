#include "TextureManager.h"

TextureManager::TextureManager(SDL_Renderer* renderer) {
	char* base_path = SDL_GetBasePath();
	if (!base_path) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "SDL_GetBasePath failed: %s", SDL_GetError());
	}
	else {
		std::string base_dir(base_path);
		SDL_free(base_path);
		
		img_dir = std::filesystem::path(base_dir) / "assets" / "images";
		font_dir = std::filesystem::path(base_dir) / "assets" / "fonts";
	}

	// Create base texture used when loading images fails
	SDL_Surface* base_surface = SDL_CreateRGBSurfaceWithFormat(0, 2, 2, 32, SDL_PIXELFORMAT_RGBA32);//depth?
	if (!base_surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create base surface: %s", SDL_GetError());
	}
	else {
		Uint32 green = SDL_MapRGBA(base_surface->format, 0x00, 0xFF, 0x00, 0xFF);
		Uint32 pink = SDL_MapRGBA(base_surface->format, 0xFF, 0x00, 0xFF, 0xFF);

		Uint32* pixels = static_cast<Uint32*>(base_surface->pixels);

		pixels[0] = green; pixels[1] = pink;
		pixels[2] = pink; pixels[3] = green;

		base_texture = SDL_CreateTextureFromSurface(renderer, base_surface);
		if (!base_texture) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create base texture: %s", SDL_GetError());
		}
	}

	loadAll(renderer);
	base_font = getFont("Tiny5-Regular.ttf", 50);

	makeFontTex(renderer, getFont("Tiny5-Regular.ttf", 50), "ERROR", Colors::white);
}

TextureManager::~TextureManager() {
	unloadAll();
}

SDL_Texture* TextureManager::findTexture(const std::string& name) {
	auto it = tex_cache.find(name);
	if (it != tex_cache.end()) { // If it does exist
		return it->second;
	}
	return nullptr;
}
//had isTexture before which returned bool instead of pointer or nullptr
//could make a different getTexture with noexcept to use when isTexture is used before just return tex_cache.find(name)->second;

SDL_Texture* TextureManager::getTexture(const std::string& name) { // Returns base texture if fails
	//std::string path = img_dir + name;
	auto it = tex_cache.find(name);
	if (it != tex_cache.end()) { // If it does exist
		return it->second;
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't find '%s'. Using base texture instead.", name.c_str());
	return base_texture;
}

void TextureManager::loadImage(SDL_Renderer* renderer, const std::string& name) {//maybe rename to loadTexture
	auto path = img_dir / name;
	auto it = tex_cache.find(name);
	if (it == tex_cache.end()) { // If it doesn't exist
		SDL_Texture* texture = IMG_LoadTexture(renderer, path.string().c_str());
		if (!texture) { // If it failed to load
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "IMG_LoadTexture failed: %s.", IMG_GetError());
			return;
		}
		tex_cache.emplace(path.filename().string(), texture);//maybe change to not include path and just name so just .stem()
	}
	else {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Image %s already exists as %s.", name.c_str(), path.string().c_str());
	}
}

// To check what format type it is
//Uint32 fmt;
//int access, w, h;
//
//SDL_QueryTexture(texture, &fmt, &access, &w, &h);
//
//SDL_Log("Texture format: %s", SDL_GetPixelFormatName(fmt));


//void TextureManager::loadTiles(SDL_Renderer* renderer) {
//	loadImage(renderer, img_dir + "tiles.png");
//	//SDL_Texture* player = IMG_LoadTexture(renderer, "assets/images/player.png");
//}



TTF_Font* TextureManager::getFont(const std::string& font, const int size) {
	std::string name = font + "_" + std::to_string(size);
	auto it = font_cache.find(name);
	if (it != font_cache.end()) { // If it does exist
		return it->second;
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Can't find font '%s' with size %i. Using base font instead.", font.c_str(), size);
	return font_cache.at("Tiny5-Regular.ttf_50");
}

SDL_Texture* TextureManager::getFontTexture(const std::string& name) {
	auto it = font_tex_cache.find(name);
	if (it != font_tex_cache.end()) { // If it does exist
		return it->second;
	}
	SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't find '%s' font texture. Using base text instead.", name.c_str());
	return font_tex_cache.at("ERROR");
}

void TextureManager::loadFont(const std::string& font, const int size) {
	auto path = font_dir / font;
	auto name = font + "_" + std::to_string(size);//could use .stem() instead
	auto it = font_cache.find(name);
	if (it == font_cache.end()) {
		TTF_Font* Font = TTF_OpenFont(path.string().c_str(), size);
		if (!Font) {
			SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "TTF_OpenFont failed: %s", TTF_GetError());
			return;
		}
		font_cache.emplace(name, Font);
	}
	//else {
	//	SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Font %s already exists as %s.", name.c_str(), path.c_str());
	//}
}

SDL_Texture* TextureManager::makeFontTex(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color) {//colors are not separated right now - could just make white always and color mod when needed
	auto it = font_tex_cache.find(text);
	if (it != font_tex_cache.end()) { // If it does exist
		return it->second;
	}
	//If it doesn't
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);//maybe change type of text for different fonts? As in Text_Solid in function name
	if (!surface) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't render surface from font: %s", TTF_GetError());
		return font_tex_cache.at("ERROR");
	}

	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);

	if (!texture) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create font texture: %s", SDL_GetError());
		return font_tex_cache.at("ERROR");
	}

	font_tex_cache.emplace(text, texture);
	
	return texture;
}

void TextureManager::loadAll(SDL_Renderer* renderer) {
	for (const auto& entry : std::filesystem::recursive_directory_iterator(img_dir)) {
		if (entry.path().extension() == ".png") {//could add check is_regular_file to be sure but is kinda useless
			loadImage(renderer, entry.path().lexically_relative(img_dir).string());//or could use std::filesystem::relative(entry.path(), img_dir)
		}
	}

	for (const auto& entry : std::filesystem::directory_iterator(font_dir)) {//change to not load all fonts at the start only the one being used
		if (entry.path().extension() == ".ttf") {
			loadFont(entry.path().filename().string(), 50);
			loadFont(entry.path().filename().string(), 150);
		}
	}
}

//void TextureManager::createTexture(SDL_Renderer* renderer, const std::string& name, int width, int height) {
//	SDL_Texture* tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
//
//	cache.emplace(name, tex);
//}

//SDL_Texture* TextureManager::get(SDL_Renderer* renderer, const std::string& path) {
//	auto it = cache.find(path);
//	if (it != cache.end()) { // If it already exists
//		return it->second;
//	}
//	SDL_Texture* tex = IMG_LoadTexture(renderer, path.c_str());
//	if (!tex) { // If it failed to load
//		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load %s: %s", path.c_str(), IMG_GetError());
//	}
//	cache.emplace(path, tex);
//	return tex;
//}

void TextureManager::addTexture(const std::string& name, SDL_Texture* tex) {
	tex_cache.try_emplace(name, tex);
	//add log if already exists
}

void TextureManager::changeTexture(const std::string& name, SDL_Texture* tex) {
	auto it = tex_cache.find(name);
	//if (it != tex_cache.end()) {
	//	if (it->second != tex) {
	//		SDL_DestroyTexture(it->second);
	//		it->second = tex;
	//	}
	//}
	//else {
	//	tex_cache.emplace(name, tex);
	//}

	if (it == tex_cache.end()) {
		tex_cache.emplace(name, tex);
	}
	else if (it->second != tex) {
		SDL_DestroyTexture(it->second);
		it->second = tex;
	}
	//tex_cache.insert_or_assign(name, tex);
}

void TextureManager::unloadTexture(const std::string& name) {
	auto it = tex_cache.find(name);
	if (it != tex_cache.end()) {
		SDL_DestroyTexture(it->second);
		tex_cache.erase(it);
	}
}

void TextureManager::unloadAll() {
	for (auto &item : tex_cache) {
		SDL_DestroyTexture(item.second);
	}
	tex_cache.clear();
	
	for (auto &item : font_cache) {
		TTF_CloseFont(item.second);
	}
	font_cache.clear();

	for (auto &item : font_tex_cache) {
		SDL_DestroyTexture(item.second);
	}
	font_tex_cache.clear();
}