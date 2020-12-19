#include "gameloop.hpp"
using namespace std;


map<string, int [3]> ColorManager;
ColorManager["Miku"] = {0, 255, 235};
ColorManager["Black"] = {0, 0, 0};


class TextManager {

public:
    TextManager(int w, int h, int xpos, int ypos, string text);
    ~TextManager();

private:
    SDL_Texture *TextTexture = NULL;
    SDL_Surface *TextSurface = NULL;
    SDL_Rect dst;
    TTF_Font *TextFont;
    SDL_Color TextColor;
    stringstream TextText;
};

TextManager::TextManager(int w, int h, int xpos, int ypos, string text) {
    
    TextTexture = NULL;
    TextSurface = NULL;
    dst.h = h;
    dst.w = w;
    dst.x = xpos;
    dst.y = ypos;
    if(TTF_Init() == -1) {
        cout << "TTF_Init: " << TTF_GetError() << endl;
    }
    
    TextFont = TTF_OpenFont("./fonts/GenJyuuGothic-Regular.ttf", 500);
    if(!TextFont) {
        cout << "TTF_OpenFont: " << TTF_GetError() << endl;
    }
    TTF_SetFontStyle(TextFont, TTF_STYLE_BOLD|TTF_STYLE_ITALIC);
    TextColor = ColorManager["Miku"];
    
    TextText.str( "" );
    TextText << text;

    if (!TextTexture) {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't create texture from surface: %s", SDL_GetError());
    }
}