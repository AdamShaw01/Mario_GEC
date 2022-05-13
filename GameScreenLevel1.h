#pragma once
#ifndef _GAMESCREENLEVEL1_H
#define _GAMESCREENLEVEL1_H
#include "GameScreen.h"
#include "Commons.h"
#include "Character.h"
#include "CharacterMario.h"
#include "CharacterLuigi.h"
#include "CharacterKoopa.h"
#include "Texture2D.h"
#include <iostream>
#include <vector>

class Texture2D;
class Character;
class Levelmap;
class PowBlock;
class CharacterMario;
class CharacterLuigi;
class CharacterKoopa;
class CharacterGoomba;

class GameScreenLevel1 : GameScreen
{
public:
	GameScreenLevel1(SDL_Renderer* renderer);
	~GameScreenLevel1();

	void Render() override;
	void Update(float deltaTime, SDL_Event e) override;
	void UpdatePowBlock();

private:
	Texture2D* m_background_texture;
	CharacterMario* Mario;
	CharacterLuigi* Luigi;
	CharacterKoopa* Koopa;
	CharacterGoomba* Goomba;
	Levelmap* m_level_map;
	PowBlock* m_pow_block;
	vector<CharacterKoopa*> m_koopas;
	vector<CharacterGoomba*> m_goombas;

	bool m_screenshake;
	float m_shake_time;
	float m_wobble;
	float m_background_yPos;
	float m_koopa_timer;
	float m_goomba_timer;

	bool SetUpLevel();
	void SetLevelMap();
	void DoScreenshake();
	void UpdateEnemies(float deltaTime, SDL_Event e);
	void CreateKoopa(Vector2D position, FACING direction, float speed);
	void CreateGoomba(Vector2D position, FACING direction, float speed);
};

#endif