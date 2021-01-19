#ifndef MENUCOMPONENT_H
#define MENUCOMPONENT_H
#include <string>
#include <SDL2/SDL.h>
#include <iostream>
#include <SDL2/SDL_ttf.h>
using namespace std;
class MenuComponent
{
public:
	virtual void draw(SDL_Renderer *renderer){
		return;
	}
protected:
	SDL_Rect rect;
	const SDL_Color color[2] = {{255, 223, 0}, {0, 255, 235}};
};

class words : public MenuComponent
{
public:
	words(const int);
	~words();
	words operator=(const string &);
	bool mouseisin(int,int);
	void SetRectMid(int,int);
	void draw(SDL_Renderer *);
	void ChangeColor();
private:
	const int wordsize;
	bool stop = false;
	TTF_Font *font;
	string word;
	bool colortype;
};

class picture : public MenuComponent
{
public:
	picture(int);
	~picture();
	picture operator=(const string &);
	picture& operator++();
	void SetRect(int,int,int,int);
	int Getnum();
	void Setnum(int);
	bool mouseisin(int,int);
	void draw(SDL_Renderer *);
private:
	const int maxnum;
	static int num;
	string path;
};

#endif
