#include "Player.h"
#include "Coord.h"

Player::Player()
{
	Set_lifes(3);
	Set_speed(0.4f);
	Set_jump_power(1.9f);
	Set_hit_timer(0.f);
};