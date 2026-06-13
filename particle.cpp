#include <iostream>
#include <stdlib.h>
#include "particle.h"
#include <math.h>
#include "screen.h"
using namespace std;
using namespace particleproj;

Particle :: Particle() : x(0), y(0)
{
   direction = ((2*M_PI*rand())/RAND_MAX);
   speed = (0.0001*rand())/RAND_MAX;
}
Particle :: ~Particle()
{

}
void Particle :: update(int interval)
{
    double xspeed = speed * cos(direction);
    double yspeed = speed * sin(direction);
    x += xspeed * interval;
    y += yspeed * interval;
    
    
     
}
