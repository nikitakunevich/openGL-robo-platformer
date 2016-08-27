#include "Coord.h"
#include <vector>
#include "Enemy.h"
#ifndef LEVEL_H
#define LEVEL_H

struct EnemyPos
{
	EnemyType type;
	Coord position;
};

class Level
{
	int level_width_;
	int level_height_;
	int level_num_;

	Coord level_exit_;
	Coord level_enter_;

	std::vector<EnemyPos> enemy_pos_;
	std::vector<std::string> level_;

public:
	std::vector<EnemyPos> enemy_pos(){ return enemy_pos_; };

	bool LoadLevel(const char * level_name);
	Level();
	~Level();

	int level_width()	const { return level_width_; };
	int level_height()	const { return level_height_; };

	int level_num()		const { return level_num_; };

	Coord level_enter()	const { return level_enter_; };
	Coord level_exit()	const { return level_exit_; };

	std::vector<std::string> level() const {return level_;};
	void Set_level_elemt(Coord coord, char elemt){ level_[coord.x][coord.y] = elemt; };

	void Set_level_width(int level_width)	{ level_width_ = level_width; };
	void Set_level_height(int level_height)	{ level_height_ = level_height; };

	void Set_level_enter(int x, int y)		{ level_enter_ = { x, y }; };
	void Set_level_exit(int x, int y)		{ level_exit_ = { x, y }; };
	
	void Set_level_num(int num)				{ level_num_ = num; };
};

#endif // !LEVEL_H