#include "Game.h"
#include "OpenGL.h"

int main( int argc, char* args[] )
{
	Game game(800,600);
    glutInit( &argc, args );
    glutInitContextVersion( 2, 1 );
    glutInitDisplayMode( GLUT_DOUBLE );
	glutInitWindowSize(game.screen_width(), game.screen_height());
    glutCreateWindow( "OpenGL" );
    if( !game.InitGL() )
    {
        printf( "Unable to initialize graphics library!\n" );
        return 1;
    }
    if( !game.LoadMedia() )
    {
        printf( "Unable to load media!\n" );
        return 2;
    }
	glutDisplayFunc(game.Render);
	glutKeyboardFunc(game.KeyboardKeyPress);
	glutKeyboardUpFunc(game.KeyboardKeyRelease);
    glutTimerFunc( 1000 / game.screen_fps(), game.MainLoop, 0 );
    glutMainLoop();
    return 0;
}