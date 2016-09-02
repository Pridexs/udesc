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

#include "../include/PTimer.h"
#include "../include/PRain.h"
#include "../include/POriginal.h"

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

// Variavel para manter o tipo de particula ativa.
// original = mostrado em sala de aula.
namespace ParticleType {
	enum ParticleType {
		original, rain, TOTAL_COUNT
	};
}

ParticleType::ParticleType currentParticle = ParticleType::rain;

/* for the particles */
float worldGravity = 0.0000;

// FOR RAIN
float numRainParticles = 700;
float rainWidth = SCREEN_WIDTH;
float rainHeight = SCREEN_HEIGHT;
float rainVelocity_y = (float)(rand() % 200) / 100.f;
float rainSpawnPointX = 0.0f;
float rainSpawnPointY = 0;
float rainMaxHeight = 0.09;

// Original Particles Structure
const int numOriginalParticles = 5000;

// Particles
PRain rainParticles(rainSpawnPointX, rainSpawnPointY, rainWidth, 
		rainHeight, rainMaxHeight , rainVelocity_y, numRainParticles);

POriginal originalParticles(numOriginalParticles, 5.f, worldGravity);

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
		case SDLK_r:
			//Changes the particle to RAIN
			currentParticle = ParticleType::rain;
			rainParticles.resetParticles();
			break;
		case SDLK_o:
			//Changes the particle to Original
			currentParticle = ParticleType::original;
			originalParticles.resetParticles();
			break;
		default:
			break;
	}
}

void update( float dt )
{
	if (currentParticle == ParticleType::original)
	{
		originalParticles.update(dt);
	}
	else if (currentParticle == ParticleType::rain)
	{
		rainParticles.update(dt);
	}
}

void render()
{
	if (currentParticle == ParticleType::original)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		originalParticles.render();
	}
	else if (currentParticle == ParticleType::rain)
	{
		glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
		rainParticles.render();
	}
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

        PTimer stepTimer;
        stepTimer.start();

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

			float timeStep = stepTimer.getTicks() / 1000.f;
            stepTimer.start();
			
			update(timeStep);
			render();

			//Update screen
			SDL_GL_SwapWindow( gWindow );
		}
		
	}

	//Free resources and close SDL
	close();

	return 0;
}