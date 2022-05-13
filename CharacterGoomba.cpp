#include "CharacterGoomba.h"
#include "Character.h"

CharacterGoomba::CharacterGoomba(SDL_Renderer* renderer, string imagePath, Vector2D start_position, Levelmap* map, FACING start_facing, float movement_speed)
	: Character(renderer, imagePath, start_position, map)
{
	m_facing_direction = start_facing;
	m_movement_speed = movement_speed;
	m_position = start_position;

	m_single_sprite_w = m_texture->GetWidth();
	m_single_sprite_h = m_texture->GetHeight() / 2;
}
CharacterGoomba::~CharacterGoomba()
{

}
void CharacterGoomba::TakeDamage()
{

}
void CharacterGoomba::Update(float deltaTime, SDL_Event e)
{
	Character::GoombaUpdate(deltaTime, e);

	if (!m_injured)
	{
		//enemy is not injured so move
		if (m_facing_direction == FACING_LEFT)
		{
			m_moving_left = true;
			m_moving_right = false;
		}
		if (m_facing_direction == FACING_RIGHT)
		{
			m_moving_right = true;
			m_moving_left = false;
		}
	}
}
void CharacterGoomba::Render()
{
	int height = 0;

	if (m_moving_left || m_moving_right)
		height = m_single_sprite_h;

	SDL_Rect portion_of_sprite = { 0, height, m_single_sprite_w, m_single_sprite_h };

	//determine where you want it drawn
	SDL_Rect destRect = { (int)(m_position.x), (int)(m_position.y), m_single_sprite_w, m_single_sprite_h };

	if (m_facing_direction == FACING_RIGHT)
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_NONE);
	}
	else
	{
		m_texture->Render(portion_of_sprite, destRect, SDL_FLIP_HORIZONTAL);
	}
}