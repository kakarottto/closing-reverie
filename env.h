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
	void put_pixel(int x, int y, SDL_Color c, SDL_Renderer* renderer);
	SDL_Color get_pixel(int x, int y, SDL_Renderer* renderer);
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
