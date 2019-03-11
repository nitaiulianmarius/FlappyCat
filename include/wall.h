class Wall
{
public:

    int x;
    int y; // mijlocul ferestrei
    int distance; // intre cele 2 obstacole

    void update();
    void render();

    Wall()
    {
        distance = 150;
    }

}zid;

vector <Wall > _zid;

void Wall::update()
{

    for(int i=0;i<_zid.size();i++)
    {
        _zid[i].x-=4;

        if(_zid[i].x < -24)
            _zid.erase(_zid.begin()+i);
    }

}

void Wall::render()
{

    for(int i=0;i<_zid.size();i++)
    {
        showImg(wall,renderer,_zid[i].x,0     ,24,_zid[i].y-_zid[i].distance/2);
        showImg(wall,renderer,_zid[i].x,_zid[i].y+_zid[i].distance/2,24,HEIGHT);
    }

}
