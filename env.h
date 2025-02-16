#pragma once
//#include "gui.h"
//#include <vector>
#include <SDL2/SDL.h>

class Enviroment{
public:
	Enviroment();
	~Enviroment();
	void setScreen(int width, int height);
	void getScreen(int &width, int &height);
	int getScreenWidth();
	int getScreenHeight();
	SDL_Renderer* getRenderer();
	SDL_Window* getWindow();
	SDL_Surface* getSurface();
	void setDraw(void (*f)());
	void setUpdate(void (*f)());
	void setInit(void (*f)());
	void Start();
	void Stop();
	void halt();
	void pause(void (*drawf)());
	void put_pixel(int x, int y, SDL_Color c);
	SDL_Color get_pixel(int x, int y);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
	int screen_width;
	int screen_height;
	void (*update)();
	void (*draw)();
	void (*init)();
	bool run;
};

static bool color_compare(SDL_Color a, SDL_Color b){
	return (a.r == b.r && a.g == b.g && a.b == b.b );
}
static bool compare_color(SDL_Color b, SDL_Color a){
	return color_compare(b,a);//to scare the ocd mortals
}

static bool color_less(SDL_Color a, SDL_Color b){
	return (a.r <= b.r && a.g <= b.g && a.b <= b.b );
}

static bool less_color(SDL_Color a, SDL_Color b){
	return color_less(a,b);
}

static bool color_between(SDL_Color a, SDL_Color b, SDL_Color c){
	return ( (a.r <= b.r && b.r<=c.r) &&
			 (a.g <= b.g && b.g<=c.g) &&
			 (a.b <= b.b && b.b<=c.b));
}

static bool between_color(SDL_Color a, SDL_Color b, SDL_Color c){
	return color_between(a,b,c);
}
