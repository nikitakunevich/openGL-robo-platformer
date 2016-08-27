#include "OpenGL.h"
#include "Coord.h"

class Camera
{
	CoordF camera_coord_;
	GLfloat camera_width_;
	GLfloat camera_height_;
public:
	Camera(){};
	~Camera(){};
	void Set_camera_coord(CoordF camera_coord) { camera_coord_ = camera_coord; };
	CoordF camera_coord() const {return camera_coord_;};
	void Set_camera_size(GLfloat camera_width, GLfloat camera_height)
	{
		camera_width_ = camera_width;
		camera_height_ = camera_height;
	}
	GLfloat camera_width() const {return camera_width_;};
	GLfloat camera_height() const{return camera_height_;};
};