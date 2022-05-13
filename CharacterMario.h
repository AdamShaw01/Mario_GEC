#pragma once
#ifndef _CHARACTERMARIO_H
#define _CHARACTERMARIO_H
#include "Character.h"
#include "Texture2D.h"

class CharacterMario : public Character
{
public:
	CharacterMario(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Levelmap* map);
	~CharacterMario();
	void Update(float deltaTime, SDL_Event e);
	void Render();

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
};

#endif