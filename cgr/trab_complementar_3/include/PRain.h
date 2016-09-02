#ifndef PRAIN_HPP
#define PRAIN_HPP

// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica

//
// mWidth - Determinar o tamanho da area em que a chuva podera
// aparecer
//
// mHeight - A altura que a chuva ira cair (ao percorrer x unidades
// ela some, em que x é o height)
//
// mNumParticles - Numero de particulas máximas que podem existir ao
// mesmo tempo
//

#include <vector>
#include <list>
#include <SDL2/SDL.h>
#include <GL/glu.h>

class PRain
{
    public:
        PRain(int spawnPointX, int spawnPointY, 
            float width, float height, float maxHeight,
             float velocity_y, unsigned int nParticles);

        void handleEvent( SDL_Event& e );

        void render();
        void update(float dt);

    private:
        float mWidth, mHeight, mMaxHeight;
        float mVelocity_y;

        int mSpawnPointX, mSpawnPointY;
        int mNumParticles;

        struct Particle {
            float x1, y1, veloc_y;
            float x2, y2;
        };

        std::list<struct Particle> mParticles;
};

#endif