#include "Character.h"
#include "Texture2D.h"
#include <iostream>
using namespace std;

Character::Character(SDL_Renderer* renderer, std::string imagePath, Vector2D start_position, Levelmap* map)
{
	m_moving_left = false, m_moving_right = false, m_jumping = false, m_can_jump = true, m_jump_force = 0.0f;
	m_renderer = renderer;
	m_position = start_position;
	m_facing_direction = FACING_RIGHT;
	m_collision_radius = 15.0f;
	m_current_level_map = map;
	m_alive = true;
	m_texture = new Texture2D(m_renderer);
	if (!m_texture->LoadFromFile(imagePath))
	{
		cout << "Failed to load texture!" << endl;
	}
}
Character::~Character()
{
	m_renderer = nullptr;
}
void Character::Render()
{
	m_texture->Render(m_position, SDL_FLIP_NONE);
	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(m_position, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(m_position, SDL_FLIP_HORIZONTAL);
	}
}
void Character::Update(float deltaTime, SDL_Event e)
{
	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_texture->GetHeight())) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 1 && jumpDelay <= 0)
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}

	if (jumpDelay > 0)
	{
		jumpDelay -= deltaTime;
	}
	//deal with jumping first
	if (m_jumping)
	{
		//adjust position
		m_position.y -= m_jump_force * deltaTime;

		//reduce jump force
		m_jump_force -= JUMP_FORCE_DECREMENT * deltaTime;

		//is jump force 0?
		if (m_jump_force <= 0.0f)
			m_jumping = false;
	}
	if (m_moving_left)
	{
		MoveLeft(deltaTime);
	}
	else if (m_moving_right)
	{
		MoveRight(deltaTime);
	}
}
void Character::SetPosition(Vector2D new_position)
{
	m_position = new_position;
}
Vector2D Character::GetPosition()
{
	return m_position;
}
void Character::MoveLeft(float deltaTime)
{
	m_facing_direction = FACING_LEFT;
	m_position.x -= deltaTime * MOVEMENTSPEED;
}
void Character::MoveRight(float deltaTime)
{
	m_facing_direction = FACING_RIGHT;
	m_position.x += deltaTime * MOVEMENTSPEED;
}
void Character::AddGravity(float deltaTime)
{
	if (m_position.y + 64 <= SCREEN_HEIGHT)
	{
		m_position.y += GRAVITY * deltaTime;
	}
	else
	{
		m_can_jump = true;
	}
}
void Character::Jump()
{
	if (!m_jumping)
	{
		jumpDelay = JUMP_DELAY;
		m_jump_force = INITIAL_JUMP_FORCE;
		m_jumping = true;
		m_can_jump = false;
	}
}
float Character::GetCollisionRadius()
{
	return m_collision_radius;
}
void Character::SetAlive(bool isAlive)
{
	bool m_alive = isAlive;
	if (!m_alive)
	{
	
	}
}
bool Character::GetAlive()
{
	return m_alive;
}
bool Character::IsJumping()
{
	return m_jumping;
}
void Character::CancelJump(bool m_jumping)
{
	m_jump_force = 0;
	m_jumping = false;
}
void Character::KoopaUpdate(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		m_position.x -= deltaTime * GOOMBA_SPEED;
	}
	else if (m_moving_right)
	{
		m_position.x += deltaTime * GOOMBA_SPEED;
	}

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth() * 0.5)) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_texture->GetHeight())) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}
}
void Character::GoombaUpdate(float deltaTime, SDL_Event e)
{
	if (m_moving_left)
	{
		m_position.x -= deltaTime * KOOPA_SPEED;
	}
	else if (m_moving_right)
	{
		m_position.x += deltaTime * KOOPA_SPEED;
	}

	//collision position variables
	int centralX_position = (int)(m_position.x + (m_texture->GetWidth())) / TILE_WIDTH;
	int foot_position = (int)(m_position.y + (m_texture->GetHeight() * 0.5)) / TILE_HEIGHT;

	//deal with gravity
	if (m_current_level_map->GetTileAt(foot_position, centralX_position) == 0)
	{
		AddGravity(deltaTime);
	}
	else
	{
		//collided with ground so we can jump again
		m_can_jump = true;
	}
}