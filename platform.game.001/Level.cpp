#include "Level.h"
#include <iostream>
#include <fstream>
#include <string>

bool Level::LoadLevel(const char * level_name)
{
	std::string str;
	std::fstream file(level_name);

	if (!file.is_open())
	{
		return false;
	}

	std::getline(file,str);
	Level::level_width_ =  str.size();
	file.seekg(std::ios_base::beg,0);

	while(!file.eof())
	{
		std::getline(file,str);
		level_.push_back(str);                        
	}

	for(int i = 0; i < level_.size();i++)
	{
		for (int j = 0; j < level_[i].size(); j++)
		{
			if (level_[i][j] == 'E')		//looking for exit
			{
				level_exit_ = { j, i };
			}
			if (level_[i][j] == 'e')		//looking for entrance
			{
				level_enter_ = { j, i };
			}
			if (level_[i][j] == 'Y')
			{
				enemy_pos_.push_back({ Yellow, { j, i } });
			}
			if (level_[i][j] == 'G')
			{
				enemy_pos_.push_back({ Green, { j, i } });
			}
		}
	}
	level_height_ = level_.size();
	return true;
};

Level::Level()
{
	level_height_ = 0;
	level_width_ = 0;
	level_enter_ = { 0, 0 };
	level_exit_ = { 0, 0 };
}

Level::~Level()
{

};