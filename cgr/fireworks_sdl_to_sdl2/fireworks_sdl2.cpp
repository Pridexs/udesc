// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica
//
// Consideracoes:
// Esse codigo teve como base o tutorial do 'Lazy Foo' sobre introducao
// do SDL2 e o codigo disponbilizado pelo professor Andre Tavares da Silva
// sobre particulas.
// O codigo disponbilizado pelo professor era implementado em SDL1, entao
// tomei a liberdade de migrar o codigo com a ajuda do tutorial.
//
// Para acessalo: http://www.joinville.udesc.br/portal/professores/andretavares
// Materiais -> CGR -> fireworks_sdl.c
//

//Using SDL, SDL OpenGL, standard IO, and, strings
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <GL/glu.h>

#include <stdio.h>
#include <string>
#include <unistd.h>

//Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

//Starts up SDL, creates window, and initializes OpenGL
bool init();

//Initializes matrices and clear color
bool initGL();

//Input handler
void handleKeyPress( SDL_Keysym *keysym );

//Per frame update
void update();

//Renders quad to the screen
void render();

//Frees media and shuts down SDL
void close();

//The window we'll be rendering to
SDL_Window* gWindow = NULL;

//OpenGL context
SDL_GLContext gContext;

//Render flag
bool gRenderQuad = true;

/* for the particles */
#define NUM_PARTICLES 30000
#define GRAVITY 0.0000

// Particles Structure
struct s_pf {
  float x, y, veloc_x, veloc_y;
  unsigned lifetime;
} particles[NUM_PARTICLES];

// Main loop flag
bool quit = false;

// Initialize the particles
void InitParticle(int pause)
{
	int i;

  	for(i=0;i<NUM_PARTICLES;i++) {
    	float velocity = (float)(rand() % 100)/5000.0;
    	int angle = rand() % 360;
    	particles[i].veloc_x = cos( (M_PI * angle/180.0) ) * velocity;
    	particles[i].veloc_y = sin( (M_PI * angle/180.0) ) * velocity;
    	particles[i].x = 0.0;
    	particles[i].y = 0.0;
    	particles[i].lifetime = rand() % 100;
  	}
}

bool init()
{
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
		gWindow = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN );
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
				//Use Vsync
				if( SDL_GL_SetSwapInterval( 1 ) < 0 )
				{
					printf( "Warning: Unable to set VSync! SDL Error: %s\n", SDL_GetError() );
				}

				//Initialize OpenGL
				if( !initGL() )
				{
					printf( "Unable to initialize OpenGL!\n" );
					success = false;
				}
			}
		}
	}

	return success;
}

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

void handleKeyPress( SDL_Keysym *keysym )
{
	switch ( keysym->sym ) 
	{
		case SDLK_ESCAPE:
			quit = true;
			break;
		case SDLK_F1:
			// Needs to implement a toggle funciton
			SDL_SetWindowFullscreen(gWindow, SDL_WINDOW_FULLSCREEN_DESKTOP);
			break;
		default:
			break;
	}
}

void update()
{
	//No per frame update needed
}

void render()
{
	int i, active_particles = 0;

	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT );
	
	glBegin(GL_POINTS);
	for(i=0;i<NUM_PARTICLES;i++)
	{
		if(particles[i].lifetime) 
		{
			active_particles++;
			particles[i].veloc_y -= GRAVITY;
			particles[i].x += particles[i].veloc_x;
			particles[i].y += particles[i].veloc_y;
			particles[i].lifetime--;

			glVertex3f( particles[i].x, particles[i].y, 0.0f); // draw pixel
		}
	}
	glEnd();

	if(!active_particles) InitParticle(1);
}

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

			SDL_Delay(50);

			//Render quad
			render();
			
			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}
		
	}


	//Free resources and close SDL
	close();

	return 0;
}