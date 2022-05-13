#pragma once
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <SDL.h>
#include "Commons.h"
#include "Constants.h"
#include "Texture2D.h"
#include "Levelmap.h"
using namespace std;

class Texture2D;

class Character
{
public:
	Character(SDL_Renderer* renderer, string imagePath, Vector2D start_position, Levelmap* map);
	~Character();

	virtual void Render();
	virtual void Update(float deltaTime, SDL_Event e);
	virtual void KoopaUpdate(float deltaTime, SDL_Event e);
	virtual void GoombaUpdate(float deltaTime, SDL_Event e);
	void SetPosition(Vector2D new_position);
	Vector2D GetPosition();
	float GetCollisionRadius();
	Rect2D GetCollisionBox() { return Rect2D(m_position.x, m_position.y, m_texture->GetWidth(), m_texture->GetHeight()); }
	bool IsJumping();
	void CancelJump(bool m_jumping);
	void SetAlive(bool isAlive);
	bool GetAlive();

	FACING m_facing_direction;
private:
	Levelmap* m_current_level_map;
protected:
	SDL_Renderer* m_renderer;
	Vector2D m_position;
	Texture2D* m_texture;
	bool m_moving_left;
	bool m_moving_right;
	bool m_jumping;
	bool m_can_jump;
	float m_jump_force;
	float m_collision_radius;
	bool m_alive;
	float jumpDelay;

	virtual void MoveLeft(float deltaTime);
	virtual void MoveRight(float deltaTime);
	virtual void AddGravity(float deltaTime);
	virtual void Jump();
};

#endif