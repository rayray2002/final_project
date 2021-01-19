#include <SDL2/SDL.h>
#include "MenuComponent.h"
#include <string>
#include <iostream>
#include <SDL2/SDL_ttf.h>
#define WIDTH 1280
#define HEIGHT 720
using namespace std;
// 
//
words::words(const int size) : wordsize(size){
	font = TTF_OpenFont("fonts/GenJyuuGothic-Regular.ttf", wordsize);
	TTF_SetFontStyle(font, TTF_STYLE_ITALIC | TTF_STYLE_BOLD);
	colortype=0;
}
words::~words(){
	;
}
words words::operator=(const string &p){
	word=p;
	return *this;
}
bool words::mouseisin(int x,int y){
	if(x>rect.x&&x<rect.x+rect.w&&y>rect.y&&y<rect.y+rect.h) return true;
	else return false;
}
void words::SetRectMid(int x,int y){
	rect.x=x;
	rect.y=y;
}
void words::ChangeColor(){
	colortype=!colortype;
}
void words::draw(SDL_Renderer *renderer){
	SDL_Surface *surface;
	if(!colortype)
	surface = TTF_RenderText_Solid(font, word.c_str(), color[0]);
	else
	surface = TTF_RenderText_Solid(font, word.c_str(), color[1]);
	SDL_Texture *texture = SDL_CreateTextureFromSurface(renderer,surface);
	if(!stop){
		rect.x-=surface->clip_rect.w/2;
		rect.y-=surface->clip_rect.h/2;
		rect.w =surface->clip_rect.w;
		rect.h =surface->clip_rect.h;
		stop=1;
	}
	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
//
//
//
//
int picture::num=1;
int picture::Getnum(){
	return num;
}
void picture::Setnum(int a){
	num=a;
}
picture::picture(int max) : maxnum(max){
	rect.x=0;
	rect.y=0;
	rect.w=1280;
	rect.h=720;
}
picture::~picture(){
	;
}
void picture::SetRect(int x,int y,int w,int h){
	rect.x=x;
	rect.y=y;
	rect.w=w;
	rect.h=h;
}
picture picture::operator=(const string &p){
	path=p;
	return *this;
}
picture& picture::operator++(){
	num++;
	if(num>maxnum) num=1;
	return *this;
}
bool picture::mouseisin(int x,int y){
	if(x>rect.x&&x<rect.x+rect.w&&y>rect.y&&y<rect.y+rect.h) return true;
	else return false;
}
void picture::draw(SDL_Renderer *renderer){
	string fullpath=path+to_string(num)+".bmp";
	SDL_Surface *surface=SDL_LoadBMP(fullpath.c_str());
	SDL_Texture *texture=SDL_CreateTextureFromSurface(renderer,surface);
	SDL_RenderCopy(renderer,texture,NULL,&rect);
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(surface);
}
//
//
//
//
//
