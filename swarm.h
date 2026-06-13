#ifndef SWARM_H
#define SWARM_H
#include "particle.h"
namespace particleproj
{
    class Swarm
    {
        public:
        const static int N_Particles = 8000;
        private : 
        Particle *pParticles;
        int last_time;
        public : 
        Swarm();
        ~Swarm();
        const Particle * const getParticles() { return pParticles;};
        void update(int elapsed);
    };
}
#endif