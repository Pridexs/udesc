// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica
// Trabalho complementar 3
//
// Sistema de Particulas
//

#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <unistd.h>


//Screen dimension constants
const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeyPress( SDL_Keysym *keysym );

//Per frame update
void update( float dt );

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

// Main loop flag
bool quit = false;
bool isFullScreen = false;

float dx,dy,dz;


// Initalize SDL
bool init()
{
    dx=dy=dz = 0.0f;
    //Initialization flag
    bool success = true;

    //Initialize SDL
    if( SDL_Init( SDL_INIT_VIDEO ) < 0 )
    {
        printf( "SDL could not initialize! SDL Error: %s\n", SDL_GetError() );
        success = false;
    }
    else
    {
        //Create window
        gWindow = SDL_CreateWindow( "Sistemas de Particulas", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
        if( gWindow == NULL )
        {
            printf( "Window could not be created! SDL Error: %s\n", SDL_GetError() );
            success = false;
        }
        else
        {
            //Create context
            gContext = SDL_GL_CreateContext( gWindow );
            if( gContext == NULL )
            {
                printf( "OpenGL context could not be created! SDL Error: %s\n", SDL_GetError() );
                success = false;
            }
            else
            {
                //Initialize OpenGL
                if( !initGL() )
                {
                    printf( "Unable to initialize OpenGL!\n" );
                    success = false;
                }
            }
        }
    }

    GLfloat mat_specular[] = { 2.0, 2.0, 2.0, 2.0 };
    GLfloat mat_shininess[] = { 50.0 };
    GLfloat light_position[] = { 0.0, 3.0, -3.0, 0.0 };

    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel (GL_SMOOTH);

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_DEPTH_TEST);

    return success;
}

// Initialize OpenGL
bool initGL()
{
    bool success = true;
    GLenum error = GL_NO_ERROR;

    //Initialize Projection Matrix
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }

    //Initialize Modelview Matrix
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();

    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    //Initialize clear color
    glClearColor( 0.f, 0.f, 0.f, 1.f );
    
    //Check for error
    error = glGetError();
    if( error != GL_NO_ERROR )
    {
        printf( "Error initializing OpenGL! %s\n", gluErrorString( error ) );
        success = false;
    }
    
    return success;
}

// Toggle Full Screen
void toggleFullScreen()
{
    if (!isFullScreen)
    {    
        SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
        // Get current display mode of all displays.
        SDL_DisplayMode current;
        for(int i = 0; i < SDL_GetNumVideoDisplays(); ++i){
            if(SDL_GetCurrentDisplayMode(i, &current) != 0)
            {
                SDL_Log("Could not get display mode for video display #%d: %s", i, SDL_GetError());
            }
            else
            {
                glViewport(0, 0, current.w, current.h);
                //SDL_Log("Display #%d: current display mode is %dx%dpx @ %dhz.", i, current.w, current.h, current.refresh_rate);
                isFullScreen = !isFullScreen;
            }
            // Breaking because I am only interested in the main display.
            // I do need to look into finding in which display the window is currently at.
            break;
        }
    }
    else
    {
        SDL_SetWindowFullscreen(gWindow, 0);
        glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
        isFullScreen = !isFullScreen;
    }
}

// Handle basic key presses
void handleKeyPress( SDL_Keysym *keysym )
{
    switch ( keysym->sym ) 
    {
        case SDLK_ESCAPE:
            quit = true;
            break;
        case SDLK_F1:
            toggleFullScreen();
            break;
        case SDLK_w:
            dz += 1;
            break;
        case SDLK_s:
            dz -= 1;
            break;
        case SDLK_d:
            dy -= 1;
            break;
        case SDLK_a:
            dy -= 1;
            break;
        default:
            break;
    }
}

void update()
{
}

void render()
{
    glClear (GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity();

    glRotatef (dz, 0.0f, 0.0f, 30.0f);
    glRotatef (dy, 0.0f, 30.0f, 0.0f);

    GLUquadricObj *q1, *q2;
    q1 = gluNewQuadric();
    q2 = gluNewQuadric();
    gluQuadricNormals(q1, GLU_SMOOTH);
    gluQuadricNormals(q2, GLU_SMOOTH);

    glPushMatrix();
    glTranslatef (0.0, -0.5, -.5);
    gluQuadricDrawStyle(q1, GLU_FILL );
    gluSphere( q1 , .4 , 40 , 18 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.0, 0.0, -.5f);
    gluQuadricDrawStyle(q1, GLU_FILL );
    gluSphere( q1 , .3 , 40 , 18 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.0, .4f, -.5f);
    gluQuadricDrawStyle(q1, GLU_FILL );
    gluSphere( q1 , .2 , 40 , 18 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef (-.09f, .5f, -.65f);
    gluQuadricDrawStyle(q1, GLU_FILL );
    gluSphere( q1 , .05 , 40 , 18 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.09f, .5f, -.65f);
    gluQuadricDrawStyle(q1, GLU_FILL );
    gluSphere( q1 , .05 , 40 , 18 );
    glPopMatrix();

    glPushMatrix();
    glTranslatef (0.09f, .5f, -.65f);
    gluQuadricDrawStyle(q2, GLU_FILL );
    gluCylinder( q2 , 1.f , 1.f , 1.f, 1, 16 );
    glPopMatrix();

}

// close the program
void close()
{
    //Destroy window	
    SDL_DestroyWindow( gWindow );
    gWindow = NULL;

    //Quit SDL subsystems
    SDL_Quit();
}

int main( int argc, char* args[] )
{

    srand(time(NULL));

    //Start up SDL and create window
    if( !init() )
    {
        printf( "Failed to initialize!\n" );
    }
    else
    {
        //Event handler
        SDL_Event e;
        
        //Enable text input
        SDL_StartTextInput();

        //While application is running
        while( !quit )
        {
            //Handle events on queue
            while( SDL_PollEvent( &e ) != 0 )
            {
                //User requests quit
                if( e.type == SDL_QUIT )
                {
                    quit = true;
                }
                //Handle keypress with current mouse position
                else if( e.type == SDL_KEYDOWN )
                {
                    handleKeyPress( &e.key.keysym );
                }
            }
            
            update();
            render();

            //Update screen
            SDL_GL_SwapWindow( gWindow );
        }
        
    }

    //Free resources and close SDL
    close();

    return 0;
}