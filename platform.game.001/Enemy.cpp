#include "Enemy.h"

Enemy::Enemy()
{
	Set_speed(0.275f);
	move_range_ = 4.f*kTextureSize;
	distance_ = 0.f;
	Set_lifes(1);
}