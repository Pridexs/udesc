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
        // Spawnar particulas
    }
}

void PRain::handleEvent( SDL_Event& e )
{

}

void PRain::render()
{

}