#include "image.h"
#include "env.h"
#include "world_character.h"
#include <SDL2/SDL.h>
#include <iostream>
#include <cstdlib>
#include <time.h>
static Enviroment app;
static Image map;
static World_Character mc;
static SDL_Event event;
static bool butt=1;
static int block = 10;
static int steps = 0;
static SDL_Rect world_rect = {0,0,0,0};
static World_Character world_mc;
Image monster;
Image finger;
int finger_level =0;
int finger_level_max = 3;

//TODO: Add text. Add monster class with hp and shii
//TODO: Add fighting option and let the moster do his shi
//TODO: Add 4 heroes when fighting
//TODO: After the battle ends go to the world map the way it was

void battle_init(){
	finger.load_image("./finger.png",app.getRenderer());
	finger.set_rects(SDL_Rect{600,500,finger.getTextureWidth()/10,finger.getTextureHeight()/10},
			 {0,0,finger.getTextureWidth(),finger.getTextureHeight()});
	
	monster.load_image("./death.png",app.getRenderer());
	monster.set_rects({100,100,360,355},{0,0,360,355});

	mc.setLocation(3*app.getScreenWidth()/4,app.getScreenHeight()/2);
	mc.default_set(0);
}

void battle_update(){
	while((SDL_PollEvent(&event))){
		if(event.type == SDL_KEYUP){
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) app.Stop();
		}
		if(event.type == SDL_KEYDOWN){
			if(event.key.keysym.sym == SDLK_UP){
				if(finger_level>0){
					finger.updateImageRect({0,-block,0,0});
					--finger_level;
				}
			}
			else if(event.key.keysym.sym == SDLK_DOWN){
				if(finger_level<=finger_level_max){
					finger.updateImageRect({0,block,0,0});
					++finger_level;
				}
			}
		}
	}
}

void battle_draw(){
	SDL_RenderClear(app.getRenderer());
	finger.render_image(app.getRenderer());
	mc.render_image(app.getRenderer());
	monster.render_image(app.getRenderer());
	SDL_RenderPresent(app.getRenderer());
}
////////////////////////////////////////
////////////////////////////////////////
void world_draw(){
	SDL_RenderClear(app.getRenderer());
	if(butt) map.render_image(app.getRenderer());
	mc.render_image(app.getRenderer());


	/*
	//left
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
	
	//right
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

	//up
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
	
	//down
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

void world_update(){
	//todo:
	while((SDL_PollEvent(&event))){
		if(event.type == SDL_KEYUP){
			if(event.key.keysym.scancode == SDL_SCANCODE_ESCAPE ) app.Stop();
			else if(event.key.keysym.scancode == SDL_SCANCODE_I){
				butt=!butt;
			}
		}
		if(event.type == SDL_KEYDOWN){	
			SDL_Rect rect = map.getTextureRect();
			if(event.key.keysym.scancode == SDL_SCANCODE_A){
				//tora-uma experience
				
				if(mc.can_go_trough(
					SDL_Point{rect.x-block,rect.y},
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
					--steps;
					map.updateTextureRect({-block,0,0,0});	
				}
				mc.default_set(0);
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_D){
				
				if(mc.can_go_trough(
					SDL_Point{rect.x+block,rect.y},
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
					--steps;
					map.updateTextureRect({block,0,0,0});	
				}
				
				mc.default_set(1);
				
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_W){
				if(mc.can_go_trough(
					SDL_Point{rect.x,rect.y-block},
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
					--steps;
					map.updateTextureRect({0,-block,0,0});	
				}
				mc.default_set(2);
			}
			else if(event.key.keysym.scancode == SDL_SCANCODE_S){
				if(mc.can_go_trough(
					SDL_Point{rect.x,rect.y+block}, 
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
					--steps;
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
				std::cout<<"{x,y,w,h}"<<" : {"<< rect.x<<","<< rect.y<<","
					<< rect.w<<","<< rect.h<<"}\n";
			}
		}
		
		
	}
	
	if(steps <=0){
		//steps = rand() % 30;
		std::cout<<"FIGHT!!\n";
		app.Stop();
		//save
		SDL_Rect rect = map.getTextureRect();
		world_rect = rect;
		world_mc = mc;
		
		app.setDraw(battle_draw);
		app.setUpdate(battle_update);
		app.setInit(battle_init);
		app.Start();
	}
}

void start_init(){
	steps = rand() % 10;
	map.load_image("./map1.png",app.getRenderer());
	map.set_rects({0,0,app.getScreenWidth(),app.getScreenHeight()},{520,600,360,420});
	mc.setType(3);
	mc.setSide(1);
	mc.setSprite("./ff_char_world.png",app.getRenderer());
	mc.setLocation(app.getScreenWidth()/2,app.getScreenHeight()/2);
	mc.set_rects();
}


int main(){
	srand(time(0));
	app.setDraw(world_draw);
	app.setUpdate(world_update);
	app.setInit(start_init);
	app.Start();

	std::cout<<"\nnigga\n";
	return 0;
}
