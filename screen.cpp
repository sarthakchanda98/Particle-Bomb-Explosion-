#include <iostream>
#include "screen.h"
#include <math.h>
using namespace std;
namespace particleproj
{
Screen :: Screen()
{
    window = NULL , renderer = NULL, texture = NULL, buffer1 = NULL,  buffer2 = NULL;
}
bool Screen :: init()
{
    if(!SDL_Init(SDL_INIT_VIDEO))
    {
       return false;
    }
    window = SDL_CreateWindow("Particle Bomb Explosion Sim", screen_width, screen_height, 0);
    if(window == NULL)
    {
        SDL_Quit();
        return false;
    }
    renderer = SDL_CreateRenderer(window, NULL);
    if(renderer == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_Quit();
        return false;
    }
    texture = SDL_CreateTexture(renderer,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_STATIC, screen_width, screen_height );
    if(texture == NULL)
    {
        SDL_DestroyWindow(window);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyTexture(texture);
        SDL_Quit();
        return false;
    }
    buffer1 = new Uint32[screen_width*screen_height];
    buffer2 = new Uint32[screen_width*screen_height];
    memset(buffer1, 0, screen_width*screen_height*sizeof(Uint32));
    memset(buffer2, 0, screen_width*screen_height*sizeof(Uint32));
    return true;
}
bool Screen :: processEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event))
        {
            if(event.type == SDL_EVENT_QUIT)
            {
               return false;
            }
        }
    return true;
}
void Screen :: close()
{
    delete [] buffer1;
    delete [] buffer2;
    SDL_DestroyRenderer(renderer);
    SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
void Screen :: changescreencolour(Uint32 colour)
{
    for(int i = 0;i<(screen_height*screen_width);i++)
    {
        buffer1[i] = colour;
    }
}
void Screen :: setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue)
{
    if(x<0 || x >= screen_width || y<0 || y>=screen_height)
    {
        return;
    }
    Uint32 colour = 0;
    colour += red;
    colour <<= 8;
    colour += green;
    colour <<= 8;
    colour += blue;
    colour <<= 8;
    colour += 0xFF;
    buffer1[(y*screen_width) + x] = colour;
}
void Screen :: update()
{
    SDL_UpdateTexture(texture, NULL, buffer1, screen_width*sizeof(Uint32));
    SDL_RenderClear(renderer);
    SDL_RenderTexture(renderer, texture, NULL, NULL);
    SDL_RenderPresent(renderer);
}

void Screen :: boxblur()
{
    Uint32 *temp;
    temp = buffer1;
    buffer1 = buffer2;
    buffer2 = temp;

    for(int i=0;i<screen_height;i++)
    {
        for(int j = 0; j<screen_width;j++)
        {
            int redtotal = 0;
            int greentotal = 0;
            int bluetotal = 0;
            for(int row = -1; row<=1;row++)
            {
                for(int col = -1; col<=1;col++)
                {
                    int currentx = j + col;
                    int currenty = i + row;
                    if(currentx>=0 && currentx<screen_width && currenty>=0 && currenty<screen_height)
                    {
                        Uint32 colour=buffer2[currenty * screen_width + currentx];
                        Uint8 red = colour >> 24;
                        Uint8 green = colour >> 16;
                        Uint8 blue = colour>> 8;
                        redtotal += red;
                        greentotal += green;
                        bluetotal += blue;
                    }
                }
            }
            Uint8 red = redtotal/9;
            Uint8 green = greentotal/9;
            Uint8 blue = bluetotal/9;
            setPixel(j, i, red, green, blue);
        }
    }

}
}
