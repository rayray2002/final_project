
#include "TextureManager.h"
using namespace std;
// #include "ECS/BackGroundComponent.hpp"
#include <map>

SDL_Texture* TextureManager::LoadTexture(const char* texture)
{   

    SDL_Surface* tmpSurface;
    static int i = 1;
    cout << "i = " << i<<endl;
if (i == 1)
        tmpSurface = SDL_LoadBMP("./img/miku/0001.bmp");
if (i == 2)
        tmpSurface = SDL_LoadBMP("./img/miku/0002.bmp");
if (i == 3)
        tmpSurface = SDL_LoadBMP("./img/miku/0003.bmp");
if (i == 4)
         tmpSurface = SDL_LoadBMP("./img/miku/0004.bmp");
if (i == 5)
         tmpSurface = SDL_LoadBMP("./img/miku/0005.bmp");
if (i == 6)
         tmpSurface = SDL_LoadBMP("./img/miku/0006.bmp");
if (i == 7)
         tmpSurface = SDL_LoadBMP("./img/miku/0007.bmp");
if (i == 8)
         tmpSurface = SDL_LoadBMP("./img/miku/0008.bmp");
if (i == 9)
         tmpSurface = SDL_LoadBMP("./img/miku/0009.bmp");
if (i == 10)
         tmpSurface = SDL_LoadBMP("./img/miku/0010.bmp");
if (i == 11)
         tmpSurface = SDL_LoadBMP("./img/miku/0011.bmp");
if (i == 12)
         tmpSurface = SDL_LoadBMP("./img/miku/0012.bmp");
if (i == 13)
         tmpSurface = SDL_LoadBMP("./img/miku/0013.bmp");
if (i == 14)
         tmpSurface = SDL_LoadBMP("./img/miku/0014.bmp");
if (i == 15)
         tmpSurface = SDL_LoadBMP("./img/miku/0015.bmp");
if (i == 16)
         tmpSurface = SDL_LoadBMP("./img/miku/0016.bmp");
if (i == 17)
         tmpSurface = SDL_LoadBMP("./img/miku/0017.bmp");
if (i == 18)
         tmpSurface = SDL_LoadBMP("./img/miku/0018.bmp");
if (i == 19)
         tmpSurface = SDL_LoadBMP("./img/miku/0019.bmp");
if (i == 20)
         tmpSurface = SDL_LoadBMP("./img/miku/0020.bmp");
if (i == 21)
         tmpSurface = SDL_LoadBMP("./img/miku/0021.bmp");
if (i == 22)
         tmpSurface = SDL_LoadBMP("./img/miku/0022.bmp");
if (i == 23)
         tmpSurface = SDL_LoadBMP("./img/miku/0023.bmp");
if (i == 24)
         tmpSurface = SDL_LoadBMP("./img/miku/0024.bmp");
if (i == 25)
         tmpSurface = SDL_LoadBMP("./img/miku/0025.bmp");
if (i == 26)
         tmpSurface = SDL_LoadBMP("./img/miku/0026.bmp");
if (i == 27)
         tmpSurface = SDL_LoadBMP("./img/miku/0027.bmp");
if (i == 28)
         tmpSurface = SDL_LoadBMP("./img/miku/0028.bmp");
if (i == 29)
         tmpSurface = SDL_LoadBMP("./img/miku/0029.bmp");
if (i == 30)
         tmpSurface = SDL_LoadBMP("./img/miku/0030.bmp");
if (i == 31)
         tmpSurface = SDL_LoadBMP("./img/miku/0031.bmp");
if (i == 32)
         tmpSurface = SDL_LoadBMP("./img/miku/0032.bmp");
if (i == 33)
         tmpSurface = SDL_LoadBMP("./img/miku/0033.bmp");
if (i == 34)
         tmpSurface = SDL_LoadBMP("./img/miku/0034.bmp");
if (i == 35)
         tmpSurface = SDL_LoadBMP("./img/miku/0035.bmp");
if (i == 36)
         tmpSurface = SDL_LoadBMP("./img/miku/0036.bmp");
if (i == 37)
         tmpSurface = SDL_LoadBMP("./img/miku/0037.bmp");
if (i == 38)
         tmpSurface = SDL_LoadBMP("./img/miku/0038.bmp");
if (i == 39)
         tmpSurface = SDL_LoadBMP("./img/miku/0039.bmp");
if (i == 40)
         tmpSurface = SDL_LoadBMP("./img/miku/0040.bmp");
if (i == 41)
         tmpSurface = SDL_LoadBMP("./img/miku/0041.bmp");
if (i == 42)
         tmpSurface = SDL_LoadBMP("./img/miku/0042.bmp");
if (i == 43)
         tmpSurface = SDL_LoadBMP("./img/miku/0043.bmp");
if (i == 44)
         tmpSurface = SDL_LoadBMP("./img/miku/0044.bmp");
if (i == 45)
         tmpSurface = SDL_LoadBMP("./img/miku/0045.bmp");
if (i == 46)
         tmpSurface = SDL_LoadBMP("./img/miku/0046.bmp");
if (i == 47)
         tmpSurface = SDL_LoadBMP("./img/miku/0047.bmp");
if (i == 48)
         tmpSurface = SDL_LoadBMP("./img/miku/0048.bmp");
if (i == 49)
         tmpSurface = SDL_LoadBMP("./img/miku/0049.bmp");
if (i == 50)
         tmpSurface = SDL_LoadBMP("./img/miku/0050.bmp");
if (i == 51)
         tmpSurface = SDL_LoadBMP("./img/miku/0051.bmp");
if (i == 52)
         tmpSurface = SDL_LoadBMP("./img/miku/0052.bmp");
if (i == 53)
         tmpSurface = SDL_LoadBMP("./img/miku/0053.bmp");
if (i == 54)
         tmpSurface = SDL_LoadBMP("./img/miku/0054.bmp");
    i++;
    SDL_Delay(200);
    if (i > 54) i = 1;
    SDL_Texture* tex = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    SDL_FreeSurface(tmpSurface);
    return tex;
}


void TextureManager::Draw(/*SDL_Renderer* renderer,*/ SDL_Texture* tex, SDL_Rect src, SDL_Rect dest, SDL_RendererFlip flip)
{
    SDL_RenderCopy(Game::renderer, tex, /*&src,*/NULL, &dest);
    //SDL_RenderPresent(Game::renderer);
    cout << "copy" << endl;
    // SDL_Surface*  tmpSurface = SDL_LoadBMP("./img/miku.bmp");
    // SDL_Texture* texx = SDL_CreateTextureFromSurface(Game::renderer, tmpSurface);
    // SDL_FreeSurface(tmpSurface);
    // SDL_RenderCopy(Game::renderer, tex, &src, &dest);
    // cout << "(" << dest.w << "," << dest.h << ")" << endl;
}