#include "Texture.h"
#include <IL/IL.h>

Texture::Texture()
{
    //Initialize texture ID
    texture_id_ = 0;

    //Initialize texture dimensions
    texture_width_ = 0;
    texture_height_ = 0;
}

Texture::~Texture()
{
    //Free texture data if needed
    FreeTexture();
}

bool Texture::LoadTextureFromFile( std::string path )
{
    //Texture loading success
    bool textureLoaded = false;

    //Generate and set current image ID
    ILuint imgID = 0;
    ilGenImages( 1, &imgID );
    ilBindImage( imgID );

    //Load image
    ILboolean success = ilLoadImage( path.c_str() );

    //Image loaded successfully
    if( success == IL_TRUE )
    {
        //Convert image to RGBA
       // success = ilConvertImage( IL_RGBA, IL_UNSIGNED_BYTE );
        if( success == IL_TRUE )
        {
            //Create texture from file pixels
            textureLoaded = LoadTextureFromPixels32
			( 
				(GLuint*)ilGetData(), (GLuint)ilGetInteger( IL_IMAGE_WIDTH ), (GLuint)ilGetInteger( IL_IMAGE_HEIGHT ) 
			);
        }

        //Delete file from memory
        ilDeleteImages( 1, &imgID );
    }

    //Report error
    if( !textureLoaded )
    {
        printf( "Unable to load %s\n", path.c_str() );
    }

    return textureLoaded;
}

bool Texture::LoadTextureFromPixels32( GLuint* pixels, GLuint width, GLuint height )
{
    //Free texture if it exists
    FreeTexture();
    //Get texture dimensions
    texture_width_ = width;
    texture_height_ = height;

    //Generate texture ID
    glGenTextures( 1, &texture_id_ );

    //Bind texture ID
    glBindTexture( GL_TEXTURE_2D, texture_id_ );

    //Generate texture
    glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels );

    //Set texture parameters
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );

    //Unbind texture
    glBindTexture( GL_TEXTURE_2D, NULL );

    //Check for error
    GLenum error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error loading texture from %p pixels! %s\n", pixels, gluErrorString( error ) );
        return false;
    }

    return true;
}

void Texture::FreeTexture()
{
    //Delete texture
    if( texture_id_ != 0 )
    {
        glDeleteTextures( 1, &texture_id_ );
        texture_id_ = 0;
    }

    texture_width_ = 0;
    texture_height_ = 0;
}

void Texture::Render( GLfloat x, GLfloat y, GLfloat tex_x = 0.f, GLfloat tex_y = 0.f, GLfloat tex_x_size = 1.0f, GLfloat tex_y_size = 1.0f,GLfloat ext_x = 0.f,GLfloat ext_y = 0.f)
{
    //If the texture exists
    if( texture_id_ != 0 )
    {
        //Remove any previous transformations
      glLoadIdentity();

        //Move to rendering point
        glTranslatef( x, y, 0.f );

        //Set texture ID
        glBindTexture( GL_TEXTURE_2D, texture_id_ );

        //Render textured quad
        glBegin( GL_QUADS );
            glTexCoord2f( tex_x, tex_y );							glVertex2f(0.f, 0.f );
            glTexCoord2f( tex_x + tex_x_size, tex_y );				glVertex2f(texture_width_*tex_x_size*ext_x, 0.f );
            glTexCoord2f( tex_x + tex_x_size, tex_y + tex_y_size );	glVertex2f(texture_width_*tex_x_size*ext_x, texture_height_*tex_y_size*ext_y );
            glTexCoord2f( tex_x, tex_y + tex_y_size );				glVertex2f(0.f, texture_height_*tex_y_size*ext_y );
        glEnd();
    }
}