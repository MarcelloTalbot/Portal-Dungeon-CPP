#pragma once

#include "Common.h"
//this is only alignment in the rect not compared to window
enum class Alignment {//maybe have free (no alignment)
	Left,
	CentreX,
	Right,
	Top = 0,//or do nine for TopLeft, TopMiddle, TopRight, ... or a separate YAlignment enum
	CentreY,
	Bottom
};
//TopLeft
//MiddleLeft
//TopMiddle
//Centre
//or make alignment pos or int Vec2 and can use alignment in constructor

class GUIElement {
protected:
	Alignment x_alignment{};//maybe make theses public for get but not set?
	Alignment y_alignment{};
	Vec2 anchor_pos{};

public:
	SDL_FRect rect{};
	SDL_Color color{};
	//SDL_Texture* tex{};

private:

public:
	GUIElement(Vec2 anchor_pos, Alignment x_alignment = Alignment::CentreX, Alignment y_alignment = Alignment::CentreY, SDL_Color color = Colors::white);//put color before alignment
	~GUIElement();

	virtual void update(bool actions[ACTION_COUNT], Vec2 mouse_pos);

	virtual void render(SDL_Renderer* renderer) const;

	void align();
	void setAlignment(Alignment x_alignment, Alignment y_alignment);

	void setAnchor(Vec2 pos);

	void resize(Vec2 dim);
	void resize(float w, float h);
};