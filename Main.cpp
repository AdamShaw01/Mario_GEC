#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
//#include <SDL_ttf.h>
#include "Constants.h"
#include "Texture2D.h"
#include "Commons.h"
#include "GameScreenManager.h"
#include <iostream>
using namespace std;
//globals
SDL_Window* g_window = nullptr;
SDL_Renderer* g_renderer = nullptr;
GameScreenManager* game_screen_manager;
Uint32 g_old_time;
Mix_Music* g_music = nullptr;
int score;
//function prototypes
bool InitSDL();
bool Update();
void CloseSDL();
void Render();
void LoadMusic(string path);

int main(int argc, char* args[])
{
	//check if SDL was setup correctly
	if (InitSDL())
	{
		LoadMusic("Music/Mario.mp3");
		if (Mix_PlayingMusic() == 0)
		{
			Mix_PlayMusic(g_music, -1);
		}

		game_screen_manager = new GameScreenManager(g_renderer, SCREEN_LEVEL1);
		//set the time
		g_old_time = SDL_GetTicks();
		//flag to check if we wish to quit
		bool quit = false;
		//game loop
		while (!quit)
		{
			Render();
			quit = Update();
		}
	}
	CloseSDL();
	return 0;
}
bool InitSDL()
{
	//setup SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		cout << "SDL did not initialise. Error: " << SDL_GetError();
		return false;
	}
	else
	{
		//initialise the mixer
		if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		{
			cout << "Mixer could not init. Error: " << Mix_GetError();
			return false;
		}
		//setup passed so create window
		g_window = SDL_CreateWindow("Games Engine Creation",
			SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED,
			SCREEN_WIDTH,
			SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);
		g_renderer = SDL_CreateRenderer(g_window, -1, SDL_RENDERER_ACCELERATED);
		if (g_renderer != nullptr)
		{
			//init PNG loading
			int imageFlags = IMG_INIT_PNG;
			if (!(IMG_Init(imageFlags) & imageFlags))
			{
				cout << "SDL_Image could not initialise. Error: " << IMG_GetError();
				return false;
			}
		}
		else
		{
			cout << "Renderer could not initialse. Error: " << SDL_GetError();
			return false;
		}

		//did the window get created?
		if (g_window == nullptr)
		{
			//window failed
			cout << "Window was not created. Error: " << SDL_GetError();
			return false;
		}
		return true;
	}
}
void CloseSDL()
{
	//clear up music
	Mix_FreeMusic(g_music);
	g_music = nullptr;
	//release the renderer
	SDL_DestroyRenderer(g_renderer);
	g_renderer = nullptr;
	//release the window
	SDL_DestroyWindow(g_window);
	g_window = nullptr;
	//destroy the game screen manager
	delete game_screen_manager;
	game_screen_manager = nullptr;
	//quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}
bool Update()
{
	Uint32 new_time = SDL_GetTicks();
	//event handler
	SDL_Event e;
	//get events
	SDL_PollEvent(&e);
	//handle the events
	switch (e.type)
	{
		//click the 'X' to quit
	case SDL_QUIT:
		return true;
		break;
	}
	game_screen_manager->Update((float)(new_time - g_old_time) / 1000.0f, e);
	g_old_time = new_time;
	return false;
}
void Render()
{
	//clear the screen
	SDL_SetRenderDrawColor(g_renderer, 0x00, 0x00, 0x00, 0x00);
	SDL_RenderClear(g_renderer);
	game_screen_manager->Render();
	//update the screen
	SDL_RenderPresent(g_renderer);
}
void LoadMusic(string path)
{
	g_music = Mix_LoadMUS(path.c_str());
	if (g_music == nullptr)
	{
		cout << "Failed to load music. Error: " << Mix_GetError() << endl;
	}
}
//void LoadText()
//{
//	std::string score_text = "score: " + std::to_string(score);
//	SDL_Color textColor = { 255, 255, 255, 0 };
//	font = TTF_OpenFont("Times.ttf", 20);
//	SDL_Surface* textSurface = TTF_RenderText_Solid(font, score_text.c_str(), textColor);
//	SDL_Texture* text = SDL_CreateTextureFromSurface(renderer, textSurface);
//	int text_width = textSurface->w;
//	int text_height = textSurface->h;
//	SDL_FreeSurface(textSurface);
//	SDL_Rect renderQuad = { 20, SCREEN_HEIGHT - 30, text_width, text_height };
//	SDL_RenderCopy(renderer, text, NULL, &renderQuad);
//	SDL_DestroyTexture(text);
//}