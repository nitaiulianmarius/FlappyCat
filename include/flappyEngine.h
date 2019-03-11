#include "wall.h"
#include "player.h"

class Engine
{
public:

    int w; // game width
    int h; // game height
    DWORD startalg,stopalg,globalTime;

    bool run; // if game is started

    void loadData(); // load all images & sounds
    void input(); // input player
    void update(); // update game
    void render(); // render
    void onExit();

    void init(int W,int H) // init game
    {
        w=W,h=H;
        initSDL("Flappy Cat",w,h,window,renderer);
        loadData();
        globalTime=clock();
        srand(time(NULL));
    };

    void setFPS(int Fps,DWORD start,DWORD stop)
    {
        int Time=stop-start;

        if(Time < 1000/Fps)
            SDL_Delay(1000/Fps-Time);
    };

    Engine()
    {
        run=true;
    }

};

void Engine::update()
{


    if(clock()-globalTime > 1600)
    {
        globalTime=clock();

        Wall wal1;
        wal1.x=WIDTH;
        wal1.y=rand()%(HEIGHT-200)+100;
        _zid.push_back(wal1);
    }

    player.update();
    zid.update();

}

void Engine::render()
{

    /// background
    showImg(background,renderer,0,0,w,h);
    zid.render();
    player.render();
    SDL_RenderPresent(renderer);
    SDL_UpdateWindowSurface(window);

}

void Engine::input()
{

    while(SDL_PollEvent(&event))
    {
        if(event.type==SDL_QUIT)
        {
            run=false;
            SDL_Quit();
        }

        if(event.type==SDL_KEYDOWN)
            if(event.key.keysym.sym==SDLK_SPACE && !player.lose)
            {
                player.direction=UP;
                player.distance=0;
            }
    }

}


void Engine::onExit()
{

    while(player.y < HEIGHT - player.r)
    {
        if(HEIGHT - player.y + player.r > 6)
            player.y += 5;

        else
            player.y = HEIGHT - player.r;

        render();
    }

    SDL_Quit();
    cout<<"Scor: "<<player.scor<<endl;
    system("pause");

}

void Engine::loadData()
{

    loadImg(background,renderer,"data/background.jpg");
    loadImg(cat,renderer,"data/cat.png");
    loadImg(wall,renderer,"data/wall.png");
    loadImg(anykey,renderer,"data/anykey.png");

}
