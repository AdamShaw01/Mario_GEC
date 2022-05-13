#pragma once
#ifndef _CHARACTERLUIGI_H
#define _CHARACTERLUIGI_H
#include "Character.h"
#include "Texture2D.h"

class CharacterLuigi : public Character
{
public:
	CharacterLuigi(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Levelmap* map);
	~CharacterLuigi();
	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
};

#endif