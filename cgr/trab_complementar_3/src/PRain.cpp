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
        p.veloc_y = 0.5 + (float)(rand() % 60) / 100.f;
        p.veloc_x = 0;
        mParticles.push_back(p);
    }
}

void PRain::resetParticles()
{
    mParticles.clear();
    initParticles();
}

void PRain::updateParticles()
{
    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        it->veloc_x = mVelocity_x;
        it->x1 = it->x1;
        it->x2 = it->x1 + (mVelocity_x * 0.2);
    }
}

void PRain::handleEvent( SDL_Keysym *keysym )
{
    switch(keysym->sym)
        {
            case SDLK_w:
                mVelocity_x += 0.01;
                updateParticles();
                break;
            case SDLK_s:
                mVelocity_x -= 0.01;
                updateParticles();
                break;
        }
}

void PRain::update( float dt )
{
    float dTravY, dTravX;
    for (std::vector<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        if (it->y1 > -1.0) 
        {
            dTravY = it->veloc_y * dt;
            dTravX = it->veloc_x * dt;
            it->y1 -= dTravY;
            it->y2 -=  dTravY;
            it->x1 -= dTravX;
            it->x2 -= dTravX;
        }
        else
        {
            it->x1 = 1 - ((rand() % 200) / 100.f);
            it->y1 = 1.0;
            it->x2 = it->x1 + mVelocity_x;
            it->y2 = it->y1 + (mMaxHeight * ((rand() % 100) / 100.0));
            it->veloc_x = mVelocity_x;
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