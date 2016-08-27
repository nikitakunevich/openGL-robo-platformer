#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

//Screen parameters
GLsizei Game::screen_width_;
GLsizei Game::screen_height_;
int Game::screen_fps_;

//Game variables
std::vector<Texture> Game::textures_;
Level Game::level_;
Camera Game::camera_;
Player Game::player_;
Keys Game::keys_;
float Game::offset_x;
float Game::offset_y;
int Game::score_;
bool Game::next_level_ = true;
float Game::text_blink_ = kBlinkTime;

int Game::level_num_;
GameState Game::game_state_;
std::vector<Enemy> Game::enemies_;

float Player::frame_speed_ = 0.0025f*kScreenFPS;

void renderBitmapString(float x, float y, void *font, const char *string,float * color)
{
	glLoadIdentity();
	glRasterPos2i(x,y);
	
	glColor4f(color[0], color[1], color[2],color[3]);
	while (*string)
	{
		glutBitmapCharacter(font, *string++);
	}
	glLoadIdentity();
	glColor3f(1.f, 1.f, 1.f);
}

Game::Game(int screen_width = kScreenWidth, int screen_height = kScreenHeight)
{
	game_state_ = StartMenu;
	offset_x = offset_y = 0.f;
	keys_ = { false, false, false };
	screen_width_ = screen_width;
	screen_height_ = screen_height;
	screen_fps_ = kScreenFPS;
	level_num_ = 1;
	score_ = 0;

	camera_.Set_camera_coord({ screen_width_ / 2, screen_height_ / 2 });
	camera_.Set_camera_size( screen_width_, screen_height_);

	if (!SetLevel())
	{
		printf("Error loading level\n");
		exit(1);
	}
};

bool Game::InitGL()
{
	//Set the viewport
	glViewport(0.f, 0.f, screen_width_, screen_height_);

	//Initialize Projection Matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0, screen_width_, screen_height_, 0.0, 1.0, -1.0);

	//Initialize Modelview Matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//Initialize clear color
	glClearColor(32 / 255.f, 188 / 255.f, 225 / 255.f, 0.f);

	//Enable texturing
	glEnable(GL_TEXTURE_2D);
	//Enable blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Check for error
	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
	{
		printf("Error initializing OpenGL! %s\n", gluErrorString(error));
		return false;
	}
	//Initialize DevIL
	ilInit();
	ilClearColour(255, 255, 255, 000);

	//Check for error
	ILenum ilError = ilGetError();
	if (ilError != IL_NO_ERROR)
	{
		printf("Error initializing DevIL! %s\n", iluErrorString(ilError));
		return false;
	}

	return true;
}

void Game::KeyboardKeyRelease(unsigned char key, int x, int y)
{
	switch (key)
	{
		case 'd':
			keys_.RightKeyPressed = false;
			player_.Set_horiz_speed(0.f);
			break;
		case 'a':
			keys_.LeftKeyPressed = false;
			player_.Set_horiz_speed(0.f);
			break;
		case VK_SPACE:
			keys_.SpaceKeyPressed = false;
	}
}

void Game::KeyboardKeyPress(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:
			exit(EXIT_SUCCESS);
			break;
		case 'd':
		case 'D':
			keys_.RightKeyPressed = true;
			break;
		case 'a':
		case 'A':
			keys_.LeftKeyPressed = true;
			break;
		case VK_SPACE:
			if (game_state_ == StartMenu)
			{
				game_state_ = InGame;
				break;
			}
			else if (game_state_ == NextLevel)
			{
				game_state_ = InGame;
				break;
			}
			else if (game_state_ == End)
				exit(EXIT_SUCCESS);
			else
				keys_.SpaceKeyPressed = true;
				break;
		default:
			player_.Set_character_state(Stand);
	}
}

bool Game::LoadMedia()
{
	//Load texture
	Texture field_texture, player_texture, enemy_texture, cloud_texture,
		sun_texture, coin_texture, heart_texture, medKit_texture, door_texture,
		start_texture,end_texture, victory_texture, press_sp_texture, next_lv_texture;

	textures_ = { field_texture, player_texture, enemy_texture, cloud_texture,
		sun_texture, coin_texture, heart_texture, medKit_texture, door_texture,
		start_texture, end_texture, victory_texture, press_sp_texture, next_lv_texture };

	if (!textures_[0].LoadTextureFromFile("Resources\\LvlTiles.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[1].LoadTextureFromFile("Resources\\playerTiles.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[2].LoadTextureFromFile("Resources\\enemyTiles.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[3].LoadTextureFromFile("Resources\\cloud.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[4].LoadTextureFromFile("Resources\\sun.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[5].LoadTextureFromFile("Resources\\coin.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[6].LoadTextureFromFile("Resources\\heart.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[7].LoadTextureFromFile("Resources\\medKit.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	}
	if (!textures_[8].LoadTextureFromFile("Resources\\door.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	if (!textures_[9].LoadTextureFromFile("Resources\\Start.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	if (!textures_[10].LoadTextureFromFile("Resources\\GameOver.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	if (!textures_[11].LoadTextureFromFile("Resources\\Victory.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	if (!textures_[12].LoadTextureFromFile("Resources\\PressSpace.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	if (!textures_[13].LoadTextureFromFile("Resources\\NextLevel.png"))
	{
		printf("Unable to load file texture!\n");
		return false;
	};
	
	return true;
}

bool Game::SetLevel()
{
	char temp[3];
	std::string level_number("level_");
	level_number += _itoa(level_num_, temp, 10);
	level_number += ".txt";
	Level temp_level;
	level_ = temp_level; 
	if (!level_.LoadLevel(level_number.c_str()))
	{
		printf("Error loading %s\n", level_number.c_str());
		return false;
	}
	player_.Set_character_coord(level_.level_enter().x*kTextureSize, level_.level_enter().y*kTextureSize);

	for (int i = 0; i < level_.enemy_pos().size(); i++)
	{
		Enemy temp_enemy;
		temp_enemy.Set_character_coord
			(
			level_.enemy_pos()[i].position.x*kTextureSize,
			level_.enemy_pos()[i].position.y*kTextureSize
			);
		temp_enemy.Set_enemy_type
			(level_.enemy_pos()[i].type);
		enemies_.push_back(temp_enemy);
	}
	return true;
}
bool Game::SetNewLevel()
{
	level_num_++;
	enemies_.clear();
	if (!SetLevel())
		return false;
	camera_.Set_camera_coord({ screen_width_ / 2, screen_height_ / 2 });
	camera_.Set_camera_size(screen_width_, screen_height_);
	offset_x = offset_y = 0;
	return true;
}

void Game::MainLoop( int val )
{
    //Frame logic
    Update();
    Render();
	
    //Run frame one more time
    glutTimerFunc( 1000 / screen_fps_, MainLoop, val );
}


void Game::Update()
{
	if (game_state_ == InGame)
	{
		UpdatePlayer();
		UpdateEnemy();
	}
}


void Game::UpdatePlayer()
{
	if (player_.lifes() <= 0)
		game_state_ = End;
	if (keys_.LeftKeyPressed)
		player_.Set_horiz_speed(-player_.speed());

	if (keys_.RightKeyPressed)
		player_.Set_horiz_speed(player_.speed());

	if (keys_.SpaceKeyPressed)
	{
		if (player_.character_state() != Jump)
		{
			player_.Set_character_state(Jump);
			player_.Set_vert_speed(-player_.jump_power());
		}
	}

	if (player_.character_state() == Jump)
		player_.Set_vert_speed(player_.vert_speed() + kTimePerFrame*kGForce);

	player_.Set_character_coord({ player_.character_coord().x, player_.character_coord().y + player_.vert_speed()*kTimePerFrame });

	CheckPlayerCollision(0);

	player_.Set_character_coord({ player_.character_coord().x + player_.horiz_speed()*kTimePerFrame,
		player_.character_coord().y });

	CheckPlayerCollision(1);

	if (player_.character_coord().x > (float)(screen_width_ / 2) && player_.character_coord().x < level_.level_width()*kTextureSize - (float)(screen_width_ / 2))
		camera_.Set_camera_coord({ player_.character_coord().x, camera_.camera_coord().y });

	if (player_.character_coord().y >(float)(screen_width_ / 2) && player_.character_coord().y < level_.level_height()*kTextureSize - (float)(screen_height_ / 2))
		camera_.Set_camera_coord({ player_.character_coord().x, camera_.camera_coord().y });

	offset_x = -camera_.camera_coord().x + screen_width_ / 2;
	offset_y = -camera_.camera_coord().y + screen_height_ / 2;

	if (player_.horiz_speed() < 0)
	{
		if (player_.anim_frame() <= 4.1f)
			player_.Set_anim_frame(7.999f);
		player_.Set_anim_frame(player_.anim_frame() - player_.frame_speed());
	}
	if (player_.horiz_speed() == 0)
	{
		if (player_.anim_frame() < 4.f)
			player_.Set_anim_frame(0.f);
		else
			player_.Set_anim_frame(7.999f);
	}
	if (player_.horiz_speed() > 0)
	{
		if (player_.anim_frame() >= 3.9f)
			player_.Set_anim_frame(0.f);
		player_.Set_anim_frame(player_.anim_frame() + player_.frame_speed());
	}

	if (player_.hit())
	{
		player_.Set_hit_timer(player_.hit_timer() - player_.speed());
		if (player_.hit_timer() <= 0)
		{
			player_.Set_hit(false);
			player_.Set_hit_timer(0.f);
		}
	}
}

void Game::CheckPlayerCollision(int dir)
{
	//check colision with level
	if (player_.character_coord().x > level_.level_width()*kTextureSize - kTextureSize)
		player_.Set_character_coord({ level_.level_width()*kTextureSize - kTextureSize, player_.character_coord().y });

	else if (player_.character_coord().x < 0)
		player_.Set_character_coord({ 0, player_.character_coord().y });

	if (player_.character_coord().y > level_.level_height()*kTextureSize)
		player_.Set_character_coord({ player_.character_coord().x, level_.level_height()*kTextureSize });

	else if (player_.character_coord().y  < 0)
		player_.Set_character_coord({ player_.character_coord().x, 0 });

	for (int i = player_.character_coord().y / kTextureSize; i < (player_.character_coord().y + kTextureSize) / kTextureSize; i++)
	for (int j = player_.character_coord().x / kTextureSize; j < (player_.character_coord().x + kTextureSize) / kTextureSize; j++)
	{
		if (level_.level()[i][j] == 'C')
		{
			level_.Set_level_elemt({ i, j }, ' ');
			score_ += kCoinScore;
		}
		else
		if (level_.level()[i][j] == 'E')
		{
			if (player_.character_coord().x + kTextureSize / 2 >= level_.level_exit().x*kTextureSize
				&& player_.character_coord().y + kTextureSize / 2 >= level_.level_exit().y*kTextureSize)
			{
				score_ += 1000;
				game_state_ = End;
			}
		}
		else
		if (level_.level()[i][j] == 'M')
		{
			level_.Set_level_elemt({ i, j }, ' ');
			player_.Set_lifes(player_.lifes() + 1);
		}
		else
		if (level_.level()[i][j] == 'B')
		{
			if (player_.vert_speed() > 0 && !dir)
			{
				player_.Set_character_state(Stand);
				player_.Set_character_coord({ player_.character_coord().x, i*kTextureSize - kTextureSize });
				player_.Set_vert_speed(0.f);
			}
			else
			if (player_.vert_speed() < 0 && !dir)
			{
				player_.Set_character_coord({ player_.character_coord().x, i*kTextureSize + kTextureSize });
				player_.Set_vert_speed(0.f);
			}
			else
			if (player_.horiz_speed() < 0 && dir)
			{
				player_.Set_character_coord({ j*kTextureSize + kTextureSize, player_.character_coord().y });
			}
			else
			if (player_.horiz_speed() > 0 && dir)
			{
				player_.Set_character_coord({ j*kTextureSize - kTextureSize, player_.character_coord().y });
			}
		}
	}

	//enemy colission
	for (Enemy &enemy : enemies_)
	{
		if ((int)enemy.character_coord().x / 64 == (int)player_.character_coord().x / 64)
		{
			if (enemy.character_coord().y <= player_.character_coord().y)
			{
				if (player_.character_coord().y < enemy.character_coord().y + kTextureSize && !player_.hit())
				{
					player_.Set_lifes(player_.lifes() - 1);
					player_.Set_hit(true);
					player_.Set_hit_timer(kMaxHitTimer);
				}
			}
			else if (player_.character_coord().y > enemy.character_coord().y - kTextureSize && !player_.hit())
			{
				enemy.Set_lifes(0.f);
				player_.Set_vert_speed(- player_.jump_power()*1.05f);
				if (enemy.enemy_type() == Yellow)
					score_ += kYellowScore;
				else
					score_ += kGreenScore;
			}
		}
	}

	//fall if is not standing on ground
	if (player_.character_coord().y < level_.level_height()*kTextureSize &&
		level_.level()[player_.character_coord().y / kTextureSize + 1][player_.character_coord().x / kTextureSize + 0.5f] != 'B' &&
		player_.character_state() != Jump)
	{
		player_.Set_character_state(Jump);
	}
}


void Game::UpdateEnemy()
{
	for (auto enemy = enemies_.begin(); enemy < enemies_.end(); enemy++)
	{

		if (enemy->distance() <= 0)
		{
			enemy->Set_horiz_speed(enemy->speed());
			enemy->Set_anim_frame(0.0f);
		}
		else
		if (enemy->distance() >= enemy->move_range())
		{
			enemy->Set_horiz_speed(-enemy->speed());
			enemy->Set_anim_frame(0.5f);
		}

		enemy->Set_distance(enemy->distance() + enemy->horiz_speed()*kTimePerFrame);
		enemy->Set_character_coord({ enemy->character_coord().x + enemy->horiz_speed()*kTimePerFrame, enemy->character_coord().y });

		if (enemy->lifes() == 0)
		{
			auto temp_iter = enemy;
			temp_iter--;
			enemies_.erase(enemy);
			enemy = temp_iter;
		}
	}
}

void Game::Render()
{
	//Clear color buffer
	glClear(GL_COLOR_BUFFER_BIT);
	if (game_state_ == StartMenu)
		ShowMenu();
	else
	{
		if (game_state_ == InGame)
		{
			ShowBackground();
			ShowLevel();
			ShowCharacters();
		}
		else
		if (game_state_ == NextLevel)
			ShowNextLevel();
		if (game_state_ == End)
		{
			if (next_level_ && player_.lifes())
				if (SetNewLevel())
				{
					game_state_ = NextLevel;
				}
			if (game_state_ == End)
			{
				ShowGameOver();
				next_level_ = false;
			}
		}
	}
	glutSwapBuffers();
};

void Game::ShowNextLevel()
{
	textures_[13].Render
		((screen_width_ - textures_[13].texture_width()) / 2, (screen_height_ - textures_[13].texture_height()) / 2,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f
		);

	if (text_blink_ > 0)
	{
		textures_[12].Render
			((screen_width_ - textures_[12].texture_width()) / 2, (screen_height_ - textures_[12].texture_height()) / 2 + 75,
			0.f, 0.f,
			1.f, 1.f,
			1.f, 1.f
			);
		if (text_blink_ > kBlinkTime)
			text_blink_ = -kBlinkTime;
	}
	text_blink_ += kBlinkTime*0.1 ;
}

void Game::ShowMenu()
{
	textures_[9].Render
		(
		(screen_width_ - textures_[9].texture_width()) / 2, (screen_height_ - textures_[9].texture_height()) / 2,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f
		);
}

void Game::ShowGameOver()
{
	//show gameOver 
	if (!player_.lifes())
	textures_[10].Render
		(
		(screen_width_ - textures_[10].texture_width()) / 2, (screen_height_ - textures_[10].texture_height()) / 2,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f
		);
	//show victory message
	else
		textures_[11].Render
		(
		(screen_width_ - textures_[11].texture_width()) / 2, (screen_height_ - textures_[10].texture_height()) / 2,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f
		);

}

void Game::ShowBackground()
{
	
	//sun
	textures_[4].Render
		(
		kScreenWidth / 2.f,
		0,
		0.f, 0.f,
		1.f, 1.f,
		3.f, 3.f
		);
	//clouds
	textures_[3].Render
		(
		0,
		kScreenWidth / 6.5f,
		0.f, 0.f,
		1.f, 1.f,
		1.5f, 1.5f
		);

	textures_[3].Render
		(
		kScreenWidth / 2.1f,
		kScreenWidth * 1 / 4.5f,
		0.f, 0.f,
		1.f, 1.f,
		1.5f, 1.5f
		);

	textures_[3].Render
		(
		kScreenWidth * 5 / 6.f,
		kScreenWidth / 5.5f,
		0.f, 0.f,
		1.f, 1.f,
		1.5f, 1.5f
		);
	//score
	char *temp_char = new char[5];
	std::string temp_str = "SCORE:  ";
	temp_str += _itoa(score_, temp_char, 10);
	delete temp_char;
	float color[4] = { 1.f, 0.5f, 0.f,1.f };
	renderBitmapString(screen_width() - 200.f, 25.f, GLUT_BITMAP_TIMES_ROMAN_24, temp_str.c_str(), color);
}

void Game::ShowLevel()
{
	for (int i = 0; i < level_.level_height(); i++)
	{
		for (int j = 0; j < level_.level_width(); j++)
		{
			char temp = level_.level()[i][j];
			switch (temp)
			{
			case 'E':textures_[8].Render
				(textures_[8].texture_width()* j + offset_x,
				screen_height_ - textures_[8].texture_height()*(level_.level_height() - i) + offset_y,
				0.f, 0.f,
				1.f, 1.f, 1.f, 1.f);
				break;
			case 'M':
				textures_[7].Render
					(textures_[7].texture_width()* j + offset_x,
					screen_height_ - textures_[7].texture_height()*(level_.level_height() - i) + offset_y,
					0.f, 0.f,
					1.f, 1.f, 1.f, 1.f);
				break;
			case 'B':textures_[0].Render
				(textures_[0].texture_width() / 18 * j + offset_x,
				screen_height_ - textures_[0].texture_height()*(level_.level_height() - i) + offset_y,
				0.f, 0.f,
				1.f / 18, 1.f, 1.f, 1.f);
				break;

			case 'C':textures_[5].Render
				(textures_[5].texture_width() * j + offset_x,
				screen_height_ - textures_[5].texture_height()*(level_.level_height() - i) + offset_y,
				0., 0.f,
				1.f, 1.f, 1.f, 1.f);
				break;
			}
		}
	}

}

void Game::ShowCharacters()
{
	ShowEnemies();
	ShowPlayer();
}


void Game::ShowPlayer()
{
	if (player_.hit())
		glColor3f(1.f, 0.f, 0.f);
	int temp = floor(player_.anim_frame());
	textures_[1].Render
				(
					player_.character_coord().x + offset_x,
					screen_height_ -  (level_.level_height()*kTextureSize - player_.character_coord().y) + offset_y,
					temp/8.f,0.f,
					1.f / 8,1.f,
					1.f, 1.f
				);
	if (player_.hit())
		glColor3f(1.f, 1.f, 1.f);
	//hp
	for (int i = 0; i < player_.lifes(); i++)
		textures_[6].Render
		(
		i*(screen_width_ / 32 + textures_[6].texture_width()),
		screen_height_ / 25,
		0.f, 0.f,
		1.f, 1.f,
		1.f, 1.f
		);

}

void Game::ShowEnemies()
{
	for (Enemy enemy : enemies_)
	{
		textures_[2].Render
			(
				enemy.character_coord().x + offset_x,
				screen_height_ - (level_.level_height()*kTextureSize - enemy.character_coord().y) + offset_y,
				enemy.enemy_type()/4.f+enemy.anim_frame(),0.f,
				1.f / 4, 1.f,
				1.f, 1.f
			);
	}
}