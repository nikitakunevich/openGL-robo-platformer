#ifndef TEXTURE_H
#define TEXTURE_H

#include "OpenGL.h"
#include <cstdio>
#include <string>

class Texture
{
    public:
        Texture();
        ~Texture();
        bool LoadTextureFromFile( std::string path );
        bool LoadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height );
        void FreeTexture();
		void Render(GLfloat x, GLfloat y, GLfloat tex_x, GLfloat tex_y, GLfloat tex_x_size, GLfloat tex_y_size, GLfloat ext_x, GLfloat ext_y);
		GLuint texture_id()		const	{return texture_id_;};
		GLuint texture_width()	const	{return texture_width_;};
		GLuint texture_height()	const	{return texture_height_;};
    private:
        //Texture name
        GLuint texture_id_;
        //Texture dimensions
        GLuint texture_width_;
        GLuint texture_height_;
};

#endif
