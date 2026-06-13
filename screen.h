#ifndef SCREEN_H
#define SCREEN_H
#include <SDL3/SDL.h>
namespace particleproj
{
class Screen
{
    public:
    const static int screen_width = 800;
    const static int screen_height = 600;
    private:
      SDL_Window *window;
      SDL_Renderer *renderer;
      SDL_Texture *texture;
      Uint32 *buffer1;
      Uint32 *buffer2;
    public:
    Screen();
    bool init();
    bool processEvents();
    void close();
    void changescreencolour(Uint32 colour);
    void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
    void update();
    void boxblur();
};
}


#endif 