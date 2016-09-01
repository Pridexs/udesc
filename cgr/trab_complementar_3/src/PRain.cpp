// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica

#include "PRain.h"

PRain::PRain(int spawnPointX, int spawnPointY, 
    float width, float height, float velocity_y, unsigned int nParticles)
{
    mSpawnPointX = spawnPointX;
    mSpawnPointY = spawnPointY;
    mWidth = width;
    mNParticles = nParticles;
    mVelocity_y = velocity_y;

    for (int i = 0; i < mNParticles; i++) 
    {
        struct Particle p;
        //p.x = (rand() % int(width / 2.0)) +  spawnPointX;
        p.x = 300;
        p.y = spawnPointY;
        p.veloc_y = velocity_y;
        p.distanceTraveled = 0;
        mParticles.push_back(p);
    }
}

void PRain::handleEvent( SDL_Event& e )
{

}

void PRain::update( float dt )
{
    float dTrav;
    for (std::list<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        printf("%f %f\n", it->distanceTraveled, mHeight);
        if (it->distanceTraveled < mHeight) 
        {
            dTrav = it->veloc_y * dt;
            it->y -= dTrav;
            it->distanceTraveled += dTrav;
        }
        else
        {
            it->x = (rand() % int(mWidth / 2.0)) +  mSpawnPointX;
            it->y = mSpawnPointY;
            it->distanceTraveled = 0;
        }
    }
}

void PRain::render()
{
    for (std::list<struct Particle>::iterator it = mParticles.begin(); it != mParticles.end(); it++) 
    {
        printf("%f %f\n", it->x, it->y);
        glBegin(GL_POINTS);
            glVertex3f( it->x, it->y, 0.0f);
        glEnd();
    }
}