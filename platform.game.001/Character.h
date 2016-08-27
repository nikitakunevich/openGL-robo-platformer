#ifndef CHARACTER_H
#define CHARACTER_H

#include "Coord.h"
#include "Texture.h"
#include <cmath>

enum CharState 
{
	Stand,
	Jump,
};

class Character
{
	CoordF character_coord_;
	CharState character_state_;
	float speed_;
	int lifes_;
	float anim_frame_;
	float vert_speed_;
	float horiz_speed_;
	static float frame_speed_;
public:
	Character();
	static float frame_speed() { return frame_speed_; };

	CoordF character_coord() const { return character_coord_; };
	void Set_character_coord(int x, int y) { character_coord_ = { x, y }; };
	void Set_character_coord(CoordF char_coord){ character_coord_ = char_coord; };

	float vert_speed() const { return vert_speed_; };
	void Set_vert_speed(float vert_speed) { vert_speed_ = vert_speed; };

	float horiz_speed() const { return horiz_speed_; };
	void Set_horiz_speed(float horiz_speed) { horiz_speed_ = horiz_speed; };

	float anim_frame() const { return anim_frame_; };
	void Set_anim_frame(float frame){ anim_frame_ = frame; };

	float speed() const { return speed_; };
	void Set_speed(float speed){ speed_ = speed; };

	int lifes() const { return lifes_; };
	void Set_lifes(int lifes) { lifes_ = lifes; };

	CharState character_state() const {return character_state_; };
	void Set_character_state(CharState character_state) { character_state_ = character_state; };
};

#endif