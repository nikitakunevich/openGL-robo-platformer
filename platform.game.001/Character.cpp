#include "Character.h"
#include <ctime>

Character::Character()
{
	anim_frame_ = 0.f;
	horiz_speed_ = 0.f;
	vert_speed_ = 0.f;
	character_state_ = Stand;

}