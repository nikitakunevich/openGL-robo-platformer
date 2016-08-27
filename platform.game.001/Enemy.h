#include "Character.h"

#ifndef ENEMY_H
#define ENEMY_H

enum EnemyType { Yellow, Green };

class Enemy : public Character
{
	EnemyType enemy_type_;
	float move_range_;

	float distance_;

public:
	Enemy();
	void Set_distance(float distance){ distance_ = distance; };
	float distance(){ return distance_; }

	void Set_move_range(float move_range){ move_range_ = move_range; };
	float move_range(){ return move_range_; }

	void Set_enemy_type(EnemyType enemy_type){ enemy_type_ = enemy_type; };
	EnemyType enemy_type(){ return enemy_type_; };
};

#endif