#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "Common.h"

class TextureManager {
private:
	SDL_Texture* base_texture{};//maybe make public
	TTF_Font* base_font{};//maybe make public
	std::unordered_map<std::string, SDL_Texture*> tex_cache;// change to different map and maybe should be unique_ptr cos no one else should own
	std::unordered_map<std::string, TTF_Font*> font_cache;
	std::unordered_map < std::string, SDL_Texture*> font_tex_cache;

public:
	static inline const std::string assets_dir = "assets/";//dont need?
	//static inline std::string img_dir;
	//static inline std::string font_dir;
	static inline std::filesystem::path img_dir;
	static inline std::filesystem::path font_dir;

	//const int tile_size{ 16 };

public://might want to change types of name?
	TextureManager(SDL_Renderer* renderer);
	~TextureManager();

	SDL_Texture* findTexture(const std::string& name);
	SDL_Texture* getTexture(const std::string& name);

	void loadImage(SDL_Renderer* renderer, const std::string& name);
	//void loadTiles(SDL_Renderer* renderer);
	void loadAll(SDL_Renderer* renderer);

	TTF_Font* getFont(const std::string& font, const int size);
	SDL_Texture* getFontTexture(const std::string& name);
	void loadFont(const std::string& font, const int size);
	SDL_Texture* makeFontTex(SDL_Renderer* renderer, TTF_Font* font, const std::string& text, SDL_Color color);

	//void createTexture(SDL_Renderer* renderer, const std::string& name, int width, int height);
	void addTexture(const std::string& name, SDL_Texture* tex);
	void changeTexture(const std::string& name, SDL_Texture* tex);

	void unloadTexture(const std::string& name);
	void unloadAll();
};