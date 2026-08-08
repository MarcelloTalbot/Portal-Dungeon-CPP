#pragma once

#include <string>

#include "Common.h"

#include "TextureManager.h"
#include "GUIElement.h"

class Text : public GUIElement {
private:

public:
	int size{};
	TTF_Font* font{};//maybe make the whole game the same font
	SDL_Texture* tex{};

private:

public:
	Text(Vec2 anchor_pos, int size, SDL_Color color = Colors::white, Alignment x_alignment = Alignment::Left, Alignment y_alignment = Alignment::Top);
	~Text();

	void setText(SDL_Renderer* renderer, TextureManager* textures, const std::string& text);//probably dont need
	void setText(SDL_Texture* tex);
	void setText(TextureManager* textures, const std::string& text);

	void render(SDL_Renderer* renderer) const override;
};