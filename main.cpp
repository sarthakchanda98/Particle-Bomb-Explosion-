#include <iostream>
#include <SDL3/SDL.h>
#include "screen.h"
#include <math.h>
#include "swarm.h"
using namespace std;
using namespace particleproj;
int main()
{
    Screen screen1;
    if(!(screen1.init()))
    {
        cout << "Initialisation Failed" << endl;
    }
    Swarm swarm;

    while(true)
    {
        const Particle * const pParticles  = swarm.getParticles();
        // update the swarm once per frame
        int elapsed = SDL_GetTicks();
        swarm.update(elapsed);
        unsigned char red = (1 + sin(elapsed * 0.0009)) * 128;
        unsigned char green = (1 + sin(elapsed * 0.0008)) * 128;
        unsigned char blue = (1 + sin(elapsed * 0.0007)) * 128;
        for(int i =0; i< Swarm :: N_Particles; i++)
        {
            Particle particle = pParticles[i];
            int x = (particle.x + 1) * (Screen :: screen_width)/2;
            int y =  particle.y  * (Screen :: screen_width)/2 + Screen :: screen_height/2;
            screen1.setPixel(x,y,red,green,blue);
        }
        screen1.boxblur();
        screen1.update();
        //check for closing events
        if(!(screen1.processEvents()))
        {
           break;
        }     
    }
    screen1.close();
    return 0;
}
