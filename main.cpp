#include "image.h"
#include "env.h"
#include <SDL2/SDL.h>
#include <iostream>

Enviroment app;
Image map;
SDL_Event event;
bool butt=1;
int block = 30;


void example_draw(){
	SDL_RenderClear(app.getRenderer());
	//app.put_pixel(100,100,{255,255,255,255},app.getRenderer());
	if(butt) map.render_image(app.getRenderer());
	SDL_RenderPresent(app.getRenderer());
}

void example_update(){
	//todo: input as a text, aka on hold move 
	while((SDL_PollEvent(&event))){
		if(event.type == SDL_KEYUP){
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) app.Stop();
			else if(event.key.keysym.scancode == SDL_SCANCODE_I){
				butt=!butt;
			}
		}
		if(event.type == SDL_KEYDOWN){	
			
			if(event.key.keysym.scancode == SDL_SCANCODE_A){
				map.updateTextureRect({-block,0,0,0});
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_D){
				map.updateTextureRect({block,0,0,0});
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_W){
				map.updateTextureRect({0,-block,0,0});
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_S){
				map.updateTextureRect({0,block,0,0});	
			}
			
			if(event.key.keysym.scancode == SDL_SCANCODE_R){
				map.updateTextureRect({0,0,block,0});	
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_T){
				map.updateTextureRect({0,0,0,block});	
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_F){
				map.updateTextureRect({0,0,-block,0});	
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_G){
				map.updateTextureRect({0,0,0,-block});	
			}
			
			if(event.key.keysym.scancode == SDL_SCANCODE_P){
				SDL_Rect rect = map.getTextureRect();
				std::cout<<"{x,y,w,h}"<<" : {"<< rect.x<<","<< rect.y<<","<< rect.w<<","
												<< rect.h<<"}\n";
			}
		}
		
		
	}
}

void example_init(){	
	map.load_image("./map1.png",app.getRenderer());
	map.set_rects({0,0,app.getScreenHeight(),app.getScreenWidth()},{600,600,360,420});
}


int main(){
	app.setDraw(example_draw);
	app.setUpdate(example_update);
	app.setInit(example_init);
	app.Start();

	std::cout<<"\nnigga\n";
	return 0;
}
