#include <iostream>
#include <cstdio>
#include "env.h"

Enviroment::Enviroment(){
	//init sdl
	if(SDL_Init(SDL_INIT_EVERYTHING) == -1){
		std::cout << "SDL_Init Error:" << SDL_GetError()<<std::endl;
		exit(-1);
	}
	
	screen_height = 720;
	screen_width  = 1024;
	
	window = SDL_CreateWindow("Closing Reverie", SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
					 screen_width, screen_height, 0);
	if(window == nullptr){
		std::cout << "SDL_CreateWindow Error:" << SDL_GetError()<<std::endl;
		exit(-1);
	}
	
	renderer = SDL_CreateRenderer(window, -1, 0);
	if(renderer == nullptr){
		std::cout << "SDL_CreateRenderer Error:" << SDL_GetError()<<std::endl;
		exit(-1);
	}
}

Enviroment::~Enviroment(){
	//disable sdl
	SDL_Quit();
}

void Enviroment::setScreen(int width, int height){
	screen_width = width;
	screen_height= height;
}

void Enviroment::getScreen(int &width, int &height){
	width = screen_width;
	height= screen_height;
}

int Enviroment::getScreenWidth(){
	return screen_width;
}

int Enviroment::getScreenHeight(){
	return screen_height;
}

SDL_Renderer* Enviroment::getRenderer(){
	return renderer;
}

SDL_Surface* Enviroment::getSurface(){
	return SDL_GetWindowSurface(window);
}

SDL_Window* Enviroment::getWindow(){
	return window;
}


void Enviroment::setDraw(void (*f)()){
	draw = f;
}

void Enviroment::setUpdate(void (*f)()){
	update = f;
}

void Enviroment::setInit(void (*f)()){
	init = f;
}


void Enviroment::Start(){
	run = 1;
	init();
	
	while(run){
		frameStart = SDL_GetTicks();
		update();
		draw();
		frameTime = SDL_GetTicks() - frameStart;
        	if (frameTime < frame_delay) {
        	    SDL_Delay(frame_delay - frameTime);
        	}
	}
}

void Enviroment::Stop(){
	run = 0;
}

void Enviroment::halt(){
	SDL_Event event;
	while(! (SDL_PollEvent(&event) && event.type == SDL_KEYDOWN && 
			event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ));
}

void Enviroment::pause(void (*drawf)()){
	setDraw(drawf);
	halt();
}

void Enviroment::put_pixel(int x, int y, SDL_Color c){
	SDL_Color old_color;
	SDL_GetRenderDrawColor(renderer,&old_color.r,&old_color.g,&old_color.b,&old_color.a);
	SDL_SetRenderDrawColor(renderer, c.r,c.g,c.b,c.a);
	SDL_RenderDrawPoint(renderer,x,y);
	SDL_SetRenderDrawColor(renderer,old_color.r,old_color.g,old_color.b,old_color.a);
}


SDL_Color Enviroment::get_pixel(int x, int y){
	Uint32 color;
	SDL_Color outp;
	unsigned char r,g,b,a;
	SDL_Rect rect={x,y,1,1};
	SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_ARGB8888, &color, 32);
	SDL_GetRGBA(color,SDL_AllocFormat(SDL_PIXELFORMAT_ARGB8888), &r,&g,&b,&a);
	outp = {r,g,b,a};
	return outp;
}


