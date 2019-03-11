const short UP=1,DOWN=2;

class Player
{
public:

    int x,y; // (x,y) position
//    int xi,yi; // (x,y) initial (inainte de space)
    int r; // r img
    short direction; // up=1 / down=2
    int distance; // d: (x,y), (xi,yi)
    int maxdistance;
    int v;
    int scor;
    bool lose;

    void update();
    void render();

    Player(int xPos,int yPos,int R)
    {
        x=xPos;
        y=yPos;
        r=R;
        direction=DOWN;
        distance=0;
        maxdistance=100;
        lose=false;
        scor=0;
    }

};

Player player(50,250,22);

void Player::update()
{

    // colision
    if(!_zid.empty())
        if(_zid[0].x <= 72 && _zid[0].x > 4)
            if(y - r < _zid[0].y - _zid[0].distance/2 ||
               y + r > _zid[0].y + _zid[0].distance/2)
                lose=true;


    if(!_zid.empty() && _zid[0].x < -23)
        player.scor++;

    if(!lose)
    {
        if(distance > 50)
            v=8;
        if(distance > 90)
            v=2;
        if(distance == 0 || distance == maxdistance)
            v=4;

        if(distance >= maxdistance)
            direction = DOWN;

        if(direction == UP)
        {
            y -= v;
            distance += v;
        }
    }

    if(direction == DOWN)
    {
        if(HEIGHT - y + r > v)
            y += v;

        else
            y = HEIGHT - r;
    }



    if(y == HEIGHT - r)
        lose=true;


    if(y < -r)
        direction=DOWN,v=4;


}

void Player::render()
{

    showImg(cat,renderer,x-r,y-r,2*r,2*r);

}
