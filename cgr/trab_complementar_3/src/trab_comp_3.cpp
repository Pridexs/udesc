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
		original, rain, TOTAL_TYPE_PARTICLE
	};
}

ParticleType::ParticleType currentParticle = ParticleType::rain;

/* for the particles */
float worldGravity = 0.0000;

// FOR RAIN
struct RainParticle {
	float x1, y1, veloc_y;
	float x2, y2;
	float distanceTraveled;
};

float numRainParticles = 500;
float rainWidth = SCREEN_WIDTH;
float rainHeight = SCREEN_HEIGHT;
float rainVelocity_y = (float)(rand() % 200) / 100.f;
float rainSpawnPointX = 0.0f;
float rainSpawnPointY = 0;
float rainMaxHeight = 0.1;
std::list<struct RainParticle> rainParticles;


// Initialize Rain Particles
void initRainParticles()
{
	for (int i = 0; i < numRainParticles; i++) 
    {
        struct RainParticle p;
        p.x1 = 1 - ((rand() % 200) / 100.f) ;
        p.y1 = 1.0;
		p.x2 = p.x1;
		p.y2 = p.y1 + (rainMaxHeight * ((rand() % 100) / 100.0));
        p.veloc_y = 0.5 + (float)(rand() % 50) / 100.f;
        p.distanceTraveled = 0;
        rainParticles.push_back(p);
    }
}


// Original Particles Structure
const int numOriginalParticles = 5000;

struct s_pf {
  float x, y, veloc_x, veloc_y;
  float lifetime;
} particles[numOriginalParticles];


// Initialize the particles
void InitParticle()
{
	int i;

  	for(i=0;i<numOriginalParticles;i++) {
    	float velocity = (float)(rand() % 100) / 100.f;
    	float angle = (rand() % 360) * M_PI / 180.0;
    	particles[i].veloc_x = cos( angle ) * velocity;
    	particles[i].veloc_y = sin( angle ) * velocity;
    	particles[i].x = 0.0;
    	particles[i].y = 0.0;
    	particles[i].lifetime = 5.f;
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
		default:
			break;
	}
}

void update( float dt )
{
	int i, active_particles = 0;

	if (currentParticle == ParticleType::original) 
	{
		for(i=0;i<numOriginalParticles;i++)
		{
			if(particles[i].lifetime > 0) 
			{
				active_particles++;
				particles[i].veloc_y -= worldGravity;
				particles[i].x += particles[i].veloc_x * dt;
				particles[i].y += particles[i].veloc_y * dt;
				particles[i].lifetime -= dt;
			}
		}

		if(!active_particles) InitParticle();
	}
	else if (currentParticle == ParticleType::rain)
	{
		float dTrav;
		for (std::list<struct RainParticle>::iterator it = rainParticles.begin(); it != rainParticles.end(); it++) 
		{
			//printf("%f %f\n", it->distanceTraveled, mHeight);
			if (it->y1 > -1.0) 
			{
				dTrav = it->veloc_y * dt;
				it->y1 -= dTrav;
				it->y2 -=  dTrav;
			}
			else
			{
				it->x1 = 1 - ((rand() % 200) / 100.f);
				it->y1 = 1.0;
				it->x2 = it->x1;
				it->y2 = it->y1 + (rainMaxHeight * ((rand() % 100) / 100.0));
				it->distanceTraveled = 0;
			}
		}
	}

	
}

void render()
{
	int i;
	
	//Clear color buffer
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

	
	if (currentParticle == ParticleType::original)
	{
		glBegin(GL_POINTS);
			for(i=0;i<numOriginalParticles;i++)
			{
				if(particles[i].lifetime > 0) 
				{ 
					glVertex3f( particles[i].x, particles[i].y, 0.0f); // draw pixel
				}
			}
		glEnd();
	}
	else if (currentParticle == ParticleType::rain)
	{
		for (std::list<struct RainParticle>::iterator it = rainParticles.begin(); it != rainParticles.end(); it++) 
		{
			glBegin(GL_LINES);
				glVertex2f( it->x1, it->y1 );
				glVertex2f( it->x2, it->y2 );
			glEnd();
		}
		
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

    InitParticle();
	initRainParticles();

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