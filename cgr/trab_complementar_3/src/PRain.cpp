// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica

#include "PRain.h"

PRain::PRain(int spawnPointX, int spawnPointY, 
    float width, float height, float maxHeight,
     float velocity_y, unsigned int nParticles)
{
    mSpawnPointX = spawnPointX;
    mSpawnPointY = spawnPointY;
    mNumParticles = nParticles;
    mVelocity_y = velocity_y;
    mHeight = height;
    mMaxHeight = maxHeight;
    mWidth = width;

    initParticles();
}

void PRain::initParticles()
{
    for (int i = 0; i < mNumParticles; i++) 
    {
        struct Particle p;
        p.x1 = 1 - ((rand() % 200) / 100.f);
        p.y1 = 1.0f;
        p.x2 = p.x1;
        p.y2 = p.y1 + (mMaxHeight * ((rand() % 100) / 100.0));
        p.veloc_y = 0.5 + (float)(rand() % 50) / 100.f;
        mParticles.push_back(p);
    }
}

void PRain::resetParticles()
{
    mParticles.clear();
    initParticles();
}

void PRain::handleEvent( SDL_Event& e )
{

}

void PRain::update( float dt )
{
    float dTrav;
    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
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
            it->y2 = it->y1 + (mMaxHeight * ((rand() % 100) / 100.0));
        }
    }
}

void PRain::render()
{
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        glBegin(GL_LINES);
            glVertex2f( it->x1, it->y1 );
            glVertex2f( it->x2, it->y2 );
        glEnd();
    }
}