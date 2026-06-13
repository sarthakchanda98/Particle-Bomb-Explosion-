#include <iostream>
#include "swarm.h"
using namespace std;
using namespace particleproj;

Swarm :: Swarm() : last_time(0)
{
    pParticles = new Particle[N_Particles];
}
Swarm :: ~Swarm()
{
    delete [] pParticles;
}
void Swarm :: update(int elapsed)
{
    int interval = elapsed - last_time;
    for(int i=0;i<N_Particles;i++)
    {
        pParticles[i].update(interval);
    }
    last_time = elapsed;
}