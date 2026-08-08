#pragma once

#include "Common.h"//dont really need cos its in GUI.h

#include "GUIElement.h"

class Image : public GUIElement {
private:

public:
	SDL_Texture* tex{};

private:

public:
	Image(Vec2 anchor_pos, SDL_Texture* tex, Alignment x_alignment = Alignment::CentreX, Alignment y_alignment = Alignment::CentreY);
	~Image();

	void render(SDL_Renderer* renderer) const override;
};