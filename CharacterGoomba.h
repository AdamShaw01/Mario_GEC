#pragma once
#ifndef _CHARACTERGOOMBA_H
#define _CHARACTERGOOMBA_H
#include "Character.h"

class CharacterGoomba : public Character
{
public:
	CharacterGoomba(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Levelmap* map, FACING start_facing, float movement_speed);
	~CharacterGoomba();
	void TakeDamage();
	void Update(float deltaTime, SDL_Event e) override;
	void Render() override;

private:
	float m_single_sprite_w;
	float m_single_sprite_h;
	float m_movement_speed;
	bool m_injured;
};

#endif