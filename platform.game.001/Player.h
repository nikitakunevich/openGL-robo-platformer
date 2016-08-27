#ifndef PLAYER_H
#define PLAYER_H

#include "Character.h"

const float kMaxHitTimer = 10.f;

class Player : public Character
{
	float jump_power_;
	bool hit_;
	float hit_timer_;
public:
	float jump_power() const { return jump_power_; };
	void Set_jump_power(float jump_power) { jump_power_ = jump_power; };

	void Set_hit(bool hit) { hit_ = hit; };
	bool hit(){ return hit_; };
	
	void Set_hit_timer(float hit_timer){ hit_timer_ = hit_timer; };
	float hit_timer(){ return hit_timer_; };
	Player();
};

#endif