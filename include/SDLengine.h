#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdio.h>
#include <string>



void loadImg(SDL_Texture* &m_pTexture,SDL_Renderer* &g_pRenderer,const char *title)
{
	SDL_Surface* pTempSurface=IMG_Load(title);
	m_pTexture=SDL_CreateTextureFromSurface(g_pRenderer,pTempSurface);
	SDL_FreeSurface(pTempSurface);
}


void showImg(SDL_Texture* m_pTexture,SDL_Renderer* &g_pRenderer,int x,int y,int lx=0,int ly=0)
{
	SDL_Rect m_sourceRectangle;
	SDL_Rect m_destinationRectangle;

	SDL_QueryTexture(m_pTexture,NULL,NULL,&m_sourceRectangle.w,&m_sourceRectangle.h);

	if(!lx && !ly)
        lx=m_sourceRectangle.h,ly=m_sourceRectangle.w;

	m_destinationRectangle.x=x;
	m_sourceRectangle.x=0;
	m_destinationRectangle.y=y;
	m_sourceRectangle.y=0;
	m_destinationRectangle.h=ly;
	m_destinationRectangle.w=lx;

	SDL_RenderCopy(g_pRenderer,m_pTexture,&m_sourceRectangle,&m_destinationRectangle);
}




void loadSound(Mix_Music* &sound,char *cale)
{
    sound = Mix_LoadMUS(cale);
}

void playSound(Mix_Music* sound)
{
    Mix_PlayMusic(sound,-1);
}






class LTexture
{
	public:
		LTexture();

		void loadFromRenderedText(SDL_Renderer *&gRenderer, std::string textureText, SDL_Color textColor);
		void render(SDL_Renderer *&gRenderer, int x, int y,int lx,int ly, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL, SDL_RendererFlip flip = SDL_FLIP_NONE );
		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
		int mWidth;
		int mHeight;
};

bool init();
void loadMedia();

TTF_Font *gFont;

LTexture::LTexture()
{
	//Initialize
	mTexture = NULL;
	mWidth = 0;
	mHeight = 0;
}

void LTexture::loadFromRenderedText(SDL_Renderer* &gRenderer, std::string textureText, SDL_Color textColor )
{
	if( mTexture != NULL )
	{
		SDL_DestroyTexture( mTexture );
		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}

	SDL_Surface* textSurface = TTF_RenderText_Solid( gFont, textureText.c_str(), textColor );

    mTexture = SDL_CreateTextureFromSurface( gRenderer, textSurface );

        mWidth = textSurface->w;
        mHeight = textSurface->h;


    SDL_FreeSurface( textSurface );
}


void LTexture::render(SDL_Renderer *&gRenderer, int x, int y,int lx=0,int ly=0, double angle, SDL_Point* center, SDL_RendererFlip flip )
{
        SDL_Rect renderQuad = { x, y, mWidth, mHeight };



	    if(!lx && !ly)
        {
            renderQuad.w = getWidth();//clip->w;
            renderQuad.h = getHeight();//clip->h;
        }
        else
        {
            renderQuad.w = lx;
            renderQuad.h = ly;
        }
	SDL_RenderCopyEx( gRenderer, mTexture, clip, &renderQuad, angle, center, flip );
}

void loadText(SDL_Renderer *gRenderer, LTexture &gTextTexture,char *text)
{
	gFont = TTF_OpenFont( "lazy.ttf", 12 );

    SDL_Color textColor = { 100, 100, 0 };
    gTextTexture.loadFromRenderedText(gRenderer,text, textColor);
}

int LTexture::getWidth()
{
	return mWidth;
}

int LTexture::getHeight()
{
	return mHeight;
}

bool initSDL(const char* title, int width, int height ,SDL_Window* &gWindow,SDL_Renderer* &gRenderer)
{
	//Initialization flag
	bool success = true;

	//Initialize SDL
    SDL_Init( SDL_INIT_EVERYTHING );

    Mix_OpenAudio(49000,MIX_DEFAULT_FORMAT,2,16384);

		SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" );

		//Create window
		gWindow = SDL_CreateWindow( title, SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED ,width , height, SDL_WINDOW_SHOWN );


			gRenderer = SDL_CreateRenderer( gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

				//Initialize renderer color
				SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF );

				//Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					success = false;
				}

				TTF_Init();

	return success;
}


