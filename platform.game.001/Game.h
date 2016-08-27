#ifndef GAME_H
#define GAME_H

#include "Character.h"
#include "Player.h"
#include "OpenGL.h"
#include "Texture.h"
#include "Level.h"
#include "Camera.h"
#include "Enemy.h"
#include <vector>
#include <cmath>
#include <ctime>
#include <iostream>
#include <string>

const int kScreenWidth = 800;
const int kScreenHeight = 600;
const int kScreenFPS = 60;
const float kGForce = 0.012f;
const int kYellowScore = 250;
const int kGreenScore = 500;
const int kCoinScore = 25;
const int kBlinkTime = 4;
const float kTimePerFrame = 1000 / kScreenFPS;

struct Keys
{
	bool LeftKeyPressed;
	bool RightKeyPressed;
	bool SpaceKeyPressed;
};

enum GameState
{
	InGame,
	StartMenu,
	NextLevel,
	End
};

class Game
{
	static Keys keys_;
	static GameState game_state_;
	static int level_num_;
	static GLsizei screen_width_;
	static GLsizei screen_height_;
	static int screen_fps_;
	static Player player_;
	static std::vector<Texture> textures_;
	static Level level_; 
	static Camera camera_;
	static std::vector<Enemy> enemies_;
	static int score_;
	static float offset_x, offset_y;
	static float text_blink_;
	static bool next_level_;
public:
	Game(int screen_width,int screen_height);

	bool	LoadMedia();
	bool	InitGL();

	static	GLsizei screen_width()	{return screen_width_;};
	static  GLsizei	screen_height() {return screen_height_;};
	static  int	screen_fps()	{return screen_fps_;};
	static	int Score(){ return score_; };
	static	void ShowNextLevel();
	static  void ShowCharacters();
	static	void ShowBackground();
	static  void ShowEnemies();
	static	void ShowPlayer();
	static	void ShowLevel();
	static	void Update();
	static	void UpdateEnemy();
	static	void UpdatePlayer();
	static	void Render();
	static	bool SetNewLevel();
	static	void ShowMenu();
	static	void ShowGameOver();
	static	void MainLoop(int val);
	static	void KeyboardKeyPress(unsigned char,int,int);
	static	void KeyboardKeyRelease(unsigned char, int, int);
	static	bool SetLevel();

	static void CheckPlayerCollision(int);
};



#endif