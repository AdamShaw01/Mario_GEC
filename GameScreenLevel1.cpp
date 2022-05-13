#include "GameScreenLevel1.h"
#include "Texture2D.h"
#include "Collisions.h"
#include "Levelmap.h"
#include "PowBlock.h"
#include "CharacterKoopa.h"
#include "CharacterGoomba.h"
#include <vector>

GameScreenLevel1::GameScreenLevel1(SDL_Renderer* renderer) : GameScreen(renderer)
{
	m_level_map = nullptr;
	m_koopa_timer = KOOPA_SPAWN;
	m_goomba_timer = GOOMBA_SPAWN;
	SetUpLevel();
}
void GameScreenLevel1::Render()
{
	//draw the enemies
	for (int i = 0; i < m_koopas.size(); i++)
	{
		m_koopas[i]->Render();
	}
	for (int i = 0; i < m_goombas.size(); i++)
	{
		m_goombas[i]->Render();
	}
	//draw the background and character
	Mario->Render();
	Luigi->Render();
	m_pow_block->Render();
	m_background_texture->Render(Vector2D(0, m_background_yPos), SDL_FLIP_NONE);
}
void GameScreenLevel1::Update(float deltaTime, SDL_Event e)
{
	m_koopa_timer--;
	if (m_koopa_timer <= 0)
	{
		CreateKoopa(Vector2D(20, 32), FACING_RIGHT, KOOPA_SPEED);
		m_koopa_timer = KOOPA_SPAWN;
	}
	m_goomba_timer--;
	if (m_goomba_timer <= 0)
	{
		CreateGoomba(Vector2D(400, 32), FACING_LEFT, GOOMBA_SPEED);
		m_goomba_timer = GOOMBA_SPAWN;
	}
	//do the screenshake if required
	if (m_screenshake)
	{
		m_shake_time -= deltaTime;
		m_wobble++;
		m_background_yPos = sin(m_wobble);
		m_background_yPos *= 3.0f;

		//end shake after duration
		if (m_shake_time <= 0.0f)
		{
			m_shake_time = false;
			m_background_yPos = 0.0f;
		}
	}
	//update character
	Mario->Update(deltaTime, e);
	Luigi->Update(deltaTime, e);

	if (Collisions::Instance()->Circle(Mario, Luigi))
	{
		std::cout << "Circle hit!" << std::endl;
	}
	if (Collisions::Instance()->Box(Mario->GetCollisionBox(), Luigi->GetCollisionBox()))
	{
		std::cout << "Box hit!" << std::endl;
	}
	UpdatePowBlock();
	UpdateEnemies(deltaTime, e);
}
bool GameScreenLevel1::SetUpLevel()
{
	//load texture
	m_background_texture = new Texture2D(m_renderer);
	if (!m_background_texture->LoadFromFile("Images/BackgroundMB.png"))
	{
		std::cout << "Failed to load background texture!" << std::endl;
		return false;
	}
	//set up levelmap
	SetLevelMap();
	//set up player character
	Mario = new CharacterMario(m_renderer, "Images/Mario2.png", Vector2D(64, 330), m_level_map);
	Luigi = new CharacterLuigi(m_renderer, "Images/Luigi2.png", Vector2D(100, 330), m_level_map);
	//set up enemies
	CreateKoopa(Vector2D(20, 32), FACING_RIGHT, KOOPA_SPEED);
	CreateGoomba(Vector2D(400, 32), FACING_LEFT, GOOMBA_SPEED);
	//set up pow block
	m_pow_block = new PowBlock(m_renderer, m_level_map);
	m_screenshake = false;
	m_background_yPos = 0.0f;

	return true;
}
GameScreenLevel1::~GameScreenLevel1()
{
	delete m_background_texture;
	m_background_texture = nullptr;
	delete Mario;
	Mario = nullptr;
	delete Luigi;
	Luigi = nullptr;
	delete m_pow_block;
	m_pow_block = nullptr;
	m_koopas.clear();
	m_goombas.clear();
}
void GameScreenLevel1::SetLevelMap()
{
	int map[MAP_HEIGHT][MAP_WIDTH] = { {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,1,1,1,1,1,1,1,1,0,0,0,0},
										{1,1,0,0,0,0,0,0,0,0,0,0,0,0,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,0,0,0,0,1,1,1,1,1,1},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
										{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1} };
	//clear any old maps
	if (m_level_map != nullptr)
	{
		delete m_level_map;
	}
	//set the new one
	m_level_map = new Levelmap(map);
}
void GameScreenLevel1::UpdatePowBlock()
{
	bool mario_collide = Collisions::Instance()->Box(Mario->GetCollisionBox(), m_pow_block->GetCollisionBox());
	bool luigi_collide = Collisions::Instance()->Box(Luigi->GetCollisionBox(), m_pow_block->GetCollisionBox());
	if (mario_collide && m_pow_block->IsAvailable() && Mario->IsJumping())
	{
		std::cout << "Pow block hit!" << std::endl;
		DoScreenshake();
		m_pow_block->TakeHit();
		Mario->CancelJump(true);
	}
	if (luigi_collide && m_pow_block->IsAvailable() && Luigi->IsJumping())
	{
		std::cout << "Pow block hit!" << std::endl;
		DoScreenshake();
		m_pow_block->TakeHit();
		Luigi->CancelJump(true);
	}
}
void GameScreenLevel1::DoScreenshake()
{
	m_screenshake = true;
	m_shake_time = SHAKE_DURATION;
	m_wobble = 0.0f;

	for (int i = 0; i < m_koopas.size() ; i++)
	{
		m_koopas[i]->TakeDamage();
	}
	for (int i = 0; i < m_goombas.size(); i++)
	{
		m_goombas[i]->TakeDamage();
	}
}
void GameScreenLevel1::UpdateEnemies(float deltaTime, SDL_Event e)
{
	if (!m_koopas.empty())
	{
		int enemyIndexToDelete = -1;
		for (unsigned int i = 0; i < m_koopas.size() ; i++)
		{
			//is the enemy off screen to the left or right?
			if (m_koopas[i]->GetPosition().x == 512)
				m_koopas[i]->m_facing_direction = FACING_LEFT;
			if (m_koopas[i]->GetPosition().x == 0)
				m_koopas[i]->m_facing_direction = FACING_LEFT;
			//check if the enemy is on the bottom row of tiles
			if (m_koopas[i]->GetPosition().y > 300.0f)
			{
				//is the enemy off screen to the left or right?
				if (m_koopas[i]->GetPosition().x < (float)(-m_koopas[i]->GetCollisionBox().width * 0.5f) ||
					m_koopas[i]->GetPosition().x == 512)
					m_koopas[i]->SetAlive(false);
			}
			//now do the update
			m_koopas[i]->Update(deltaTime, e);

			//check to see if enemy collides with player
			if ((m_koopas[i]->GetPosition().y > 300.0f || m_koopas[i]->GetPosition().y <= 64.0f) &&
				(m_koopas[i]->GetPosition().x < 64.0f || m_koopas[i]->GetPosition().x > SCREEN_WIDTH - 96.0f))
			{
				//ignore collisions if behind pipe
			}
			else
			{
				if (Collisions::Instance()->Circle(m_koopas[i], Mario))
				{
					if (m_koopas[i]->GetInjured())
					{
						m_koopas[i]->SetAlive(false);
					}
					else
					{
						
					}
				}
				if (Collisions::Instance()->Circle(m_koopas[i], Luigi))
				{
					if (m_koopas[i]->GetInjured())
					{
						m_koopas[i]->SetAlive(false);
					}
					else
					{
						
					}
				}
			}
			//if the enemy is no longer alive then schedule it for deletion
			if (!m_koopas[i]->GetAlive())
			{
				enemyIndexToDelete = i;
			}
		}
		//remove dead enemies -1 each update
		if (enemyIndexToDelete != -1)
		{
			m_koopas.erase(m_koopas.begin() + enemyIndexToDelete);
		}
	}
}
void GameScreenLevel1::CreateKoopa(Vector2D position, FACING direction, float speed)
{
	CharacterKoopa* Koopa1 = new CharacterKoopa(m_renderer, "Images/Koopa.png", position, m_level_map, direction, KOOPA_SPEED);
	m_koopas.push_back(Koopa1);
}
void GameScreenLevel1::CreateGoomba(Vector2D position, FACING direction, float speed)
{
	CharacterGoomba* Goomba1 = new CharacterGoomba(m_renderer, "Images/Goomba.png", position, m_level_map, direction, GOOMBA_SPEED);
	m_goombas.push_back(Goomba1);
}