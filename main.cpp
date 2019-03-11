#include "iostream"
#include "SDLengine.h"
#include "windows.h"
#include "vector.h"

#define WIDTH 360
#define HEIGHT 500

SDL_Renderer *renderer;
SDL_Window *window;
SDL_Texture *cat,*wall,*background,*anykey;
SDL_Event event;

#include "include/flappyEngine.h"

using namespace std;

int main(int argc,char* argv[])
{

    Engine game;
    game.init(WIDTH,HEIGHT);

    game.render();
    showImg(anykey,renderer,10,50,WIDTH-20,30);
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);


    int ok=1;
    while(ok)
     while(SDL_PollEvent(&event))
        if(event.type==SDL_QUIT)
            game.run=false,ok=0;
        else
            if(event.type==SDL_KEYDOWN)
                ok=0;

    while(game.run && !player.lose)
    {

        game.startalg=GetTickCount();
        game.input();
        game.update();
        game.render();
        game.stopalg=GetTickCount();
        game.setFPS(60,game.startalg,game.stopalg);

    }

    game.onExit();

}
