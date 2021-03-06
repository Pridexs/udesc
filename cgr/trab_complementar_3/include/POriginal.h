// Alexandre Maros
// pridexs.com
// CGR - Computacao Grafica
//
//
// Class to hold the information about the
// original particle system showed in class.

#ifndef PORIGINAL_HPP
#define PORIGINAL_HPP

#include <vector>
#include <SDL2/SDL.h>
#include <GL/glu.h>

class POriginal
{
    public:
        POriginal(unsigned int nParticles, float lifetime,
            float worldGravity);

        void handleEvent( SDL_Keysym *keysym );

        void render();
        void update(float dt);

        void resetParticles();

    private:
        void initParticles();

        float mLifetime;
        float mWorldGravity;

        unsigned mNumParticles;

        struct Particle {
            float x, y, veloc_x, veloc_y;
            float lifetime;
        };

        std::vector<struct Particle> mParticles;
};

#endif