#include "image.h"
#include "env.h"
#include "world_character.h"
#include <SDL2/SDL.h>
#include <iostream>

Enviroment app;
Image map;
World_Character mc;
SDL_Event event;
bool butt=1;
int block = 10;



void example_draw(){
	SDL_RenderClear(app.getRenderer());
	if(butt) map.render_image(app.getRenderer());
	mc.render_image(app.getRenderer());


	/*
	left
	app.put_pixel(
			(app.getScreenWidth()-4*block)/2,
			(app.getScreenHeight()+block+4*mc.getCharHeight()/3)/2,
			SDL_Color{255,0,255,255}
			);
	
	app.put_pixel(
			(app.getScreenWidth()-4*block)/2,
			(app.getScreenHeight()+mc.getCharHeight())/2,
			SDL_Color{255,0,255,255}
			);
	
	right
	app.put_pixel(
			(app.getScreenWidth()+2*mc.getCharWidth()+4*block)/2,
			(app.getScreenHeight()+block+4*mc.getCharHeight()/3)/2,
			SDL_Color{255,0,255,255}
			);
	
	app.put_pixel(
			(app.getScreenWidth()+2*mc.getCharWidth()+4*block)/2,
			(app.getScreenHeight()+mc.getCharHeight())/2,
			SDL_Color{255,0,255,255}
			);

	up
	app.put_pixel(
			(app.getScreenWidth()-block+4*mc.getCharWidth()/3)/2,
			(app.getScreenHeight()-2*block)/2,
			SDL_Color{255,0,255,255}
			);
		
	app.put_pixel(
			(app.getScreenWidth()-block+mc.getCharWidth())/2,
			(app.getScreenHeight()-2*block)/2,
			SDL_Color{255,0,255,255}
			);	
	
	down
	app.put_pixel(
			(app.getScreenWidth()-block+mc.getCharWidth())/2,
			(app.getScreenHeight()+2*mc.getCharHeight()+2*block)/2,
			SDL_Color{255,0,255,255}
			);

	app.put_pixel(
			(app.getScreenWidth()-block+4*mc.getCharWidth()/3)/2,
			(app.getScreenHeight()+2*mc.getCharHeight()+2*block)/2,
			SDL_Color{255,0,255,255}
			);
	*/
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
				//tora-uma experience
				
				if(mc.can_go_trough( 
					app.get_pixel(
						(app.getScreenWidth()-4*block)/2,
						(app.getScreenHeight()+mc.getCharHeight())/2
					),
					app.get_pixel(
						(app.getScreenWidth()-4*block)/2,
						(app.getScreenHeight()+block+4*mc.getCharHeight()/3)/2
					)
			
				))
				{
				map.updateTextureRect({-block,0,0,0});	
				}
				mc.default_set(0);
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_D){
				
				if(mc.can_go_trough(
					app.get_pixel(
						(app.getScreenWidth()+2*mc.getCharWidth()+4*block)/2,
						(app.getScreenHeight()+block+4*mc.getCharHeight()/3)/2
					),
					app.get_pixel(		
						(app.getScreenWidth()+2*mc.getCharWidth()+4*block)/2,
						(app.getScreenHeight()+mc.getCharHeight())/2
					)
				))
				{
					map.updateTextureRect({block,0,0,0});	
				}
				
				mc.default_set(1);
				
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_W){
				if(mc.can_go_trough( 
					app.get_pixel(
						(app.getScreenWidth()-block+4*mc.getCharWidth()/3)/2,
						(app.getScreenHeight()-2*block)/2
					),
					app.get_pixel(
						(app.getScreenWidth()-block+mc.getCharWidth())/2,
						(app.getScreenHeight()-2*block)/2
					)
				))
				{
					map.updateTextureRect({0,-block,0,0});	
				}
				mc.default_set(2);
			}
			if(event.key.keysym.scancode == SDL_SCANCODE_S){
				if(mc.can_go_trough( 
					app.get_pixel(
						(app.getScreenWidth()-block+mc.getCharWidth())/2,
						(app.getScreenHeight()+2*mc.getCharHeight()+2*block)/2
					),
					app.get_pixel(
						(app.getScreenWidth()-block+4*mc.getCharWidth()/3)/2,
						(app.getScreenHeight()+2*mc.getCharHeight()+2*block)/2
					)
				))
				{
					map.updateTextureRect({0,block,0,0});	
				}
				mc.default_set(3);
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
	map.set_rects({0,0,app.getScreenWidth(),app.getScreenHeight()},{520,600,360,420});
	mc.setType(5);
	mc.setSide(1);
	mc.setSprite("./ff_char_world.png",app.getRenderer());
	mc.setLocation(app.getScreenWidth()/2,app.getScreenHeight()/2);
	mc.set_rects();
}


int main(){
	app.setDraw(example_draw);
	app.setUpdate(example_update);
	app.setInit(example_init);
	app.Start();

	std::cout<<"\nnigga\n";
	return 0;
}
