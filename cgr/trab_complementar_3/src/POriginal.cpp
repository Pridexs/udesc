// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica

#include "POriginal.h"

#include <cmath>

POriginal::POriginal(unsigned int nParticles, float lifetime, float worldGravity)
{
    mLifetime = lifetime;
    mNumParticles = nParticles;
    mWorldGravity = 0.0f;

    initParticles();
}

void POriginal::initParticles()
{
    mParticles.clear();
    for (int i = 0; i < mNumParticles; i++) 
    {
        float velocity = (float)(rand() % 100) / 100.f;
    	float angle = (rand() % 360) * M_PI / 180.0;
        struct Particle p;
        p.x = 0.0f;
        p.y = 0.0f;
        p.veloc_x = cos( angle ) * velocity;
        p.veloc_y = sin (angle ) * velocity;
        p.lifetime = mLifetime;
        mParticles.push_back(p);
    }
}

void POriginal::handleEvent( SDL_Event& e )
{

}

void POriginal::update( float dt )
{
    int activeParticles = 0;
    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        if(it->lifetime > 0) 
        {
            activeParticles++;
            it->veloc_y -= mWorldGravity;
            it->x += it->veloc_x * dt;
            it->y += it->veloc_y * dt;
            it->lifetime -= dt;
        }
    }

    if (!activeParticles)
        initParticles();
}

void POriginal::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        glBegin(GL_POINTS);
            glVertex3f( it->x, it->y, 0.0f );
        glEnd();
    }
}