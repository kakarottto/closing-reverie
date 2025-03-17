#include "world_character.h"
#include "env.h"
#include <SDL2/SDL.h>
#include <iostream>

World_Character::World_Character(int type,int side,  std::string image_path,SDL_Renderer* renderer){
	setSprite(image_path,renderer);
	setType(type);
	setSide(type);
	flip = false;
	inmap_privilage = 0;
	char_width = 40;
	char_height= 40;
}

World_Character::World_Character(){
	setImagePath("");
	setType(0);
	setSide(0);
	flip = false;
	inmap_privilage = 0;
	char_width = 40;
	char_height= 40;
}

World_Character::~World_Character(){
}



void World_Character::setType(int type){
	this->type = type;
}
int World_Character::getType(){
	return type;
}

void World_Character::setImagePath(std::string image_path){
	this->image_path = image_path;
}

std::string World_Character::getImagePath(){
	return image_path;
}

void World_Character::setSprite(SDL_Renderer* renderer){
	this->img.load_image(image_path,renderer);
}

void World_Character::setSprite(std::string str,SDL_Renderer* renderer){
	image_path = str;
	this->img.load_image(str,renderer);
}

bool World_Character::render_image(SDL_Renderer* renderer){
	if(flip){
		if(SDL_RenderCopyEx(renderer, img.getTexture(),img.getpTextureRect(), img.getpImageRect(),
			0,NULL,SDL_RendererFlip::SDL_FLIP_HORIZONTAL)!=0){ 
			printf("render copy fucked up: %s\n", SDL_GetError());
			return false;
		}
		return true;
	}
	return img.render_image(renderer);
}
void World_Character::set_rects(){
	img.set_rects({locx,locy,char_width,char_height},{16*side,16*type,16,16});	
}
void World_Character::set_rects(SDL_Rect onscreen, SDL_Rect portion){
	img.set_rects(onscreen,portion);	
}
void World_Character::default_set(int pos){//0 left, 1 right, 2 up, 3 down,
	switch(pos){
		case 0:
			side = 2;
			flip = true;
		break;
		case 1:
			side = 2;
			flip = false;
		break;
		
		case 2:
			side = 0;
			flip = false;
		break;
		case 3:
			side = 1;
			flip = false;
		break;
		default:
			return;
	}
	
	set_rects();
	
}

void World_Character::setFlip(bool flip){
	this->flip = flip;
}

void World_Character::do_flip(){
	flip = !flip;
}
bool World_Character::is_fliped(){
	return flip;
}

int World_Character::getInmap_privilage(){
	return inmap_privilage;
}
void World_Character::setInmap_privilage(int priv){
	inmap_privilage = priv;
}

bool World_Character::can_go_trough(SDL_Point point, SDL_Color color_down,SDL_Color color_up){
	//detects the color and determines if can go to this place
	
	/*std::cout<<"top "<<(int)color_up.r<<" "<<(int)color_up.g<<
				" "  <<(int)color_up.b<<std::endl;
	std::cout<<"bot "<<(int)color_down.r<<" "<<(int)color_down.g<<
				" "  <<(int)color_down.b<<std::endl;
	*/
	
	//430 390
	std::cout<<"\nloc:" << point.x<<" "<<point.y<<std::endl;
	//passage check. todo: add an array of passages and check if its one of them
	if(point.x <= 450 && point.x>=410 && point.y == 390) return true;
	if(point.x <= 290 && point.x>=260 && point.y == 350) return true;
	SDL_Color water = {0,0,0,0};
	SDL_Color mountain_down = {82, 57, 32};
	SDL_Color mountain_mid = {164,139,74};
	SDL_Color mountain_up = {250, 225, 150};
	//grass: 106, 206, 57 ;
	//82, 57, 32
	//131, 123, 57
	//164, 139, 74
	//213, 172, 98
	//222, 205, 106
	//246, 222, 139
	//80<=246<=250, 50<180<225, 30<139<150
	//todo: add one more color that is the upper right corner of the surrounding of you
	//if the mountain collision is correct but the corner is different, then pass it
	//the bridge must be crossable
	std::cout<<(int)mountain_down.r<<" "<<(int)color_down.r<<" "<<(int)mountain_up.r<<"\n"
	<<(int)mountain_down.g<<" "<<(int)color_down.g<<" "<<(int)mountain_up.g<<"\n"
	<<(int)mountain_down.b<<" "<<(int)color_down.b<<" "<<(int)mountain_up.b<<"\n\n";
	if(inmap_privilage == 0){
		if(compare_color(color_down,water) || compare_color(color_up,water) ) return false;
		if( (color_between(mountain_down,color_down,mountain_mid) ||
		 	color_between(mountain_mid,color_down,mountain_up)) ||
		 	(color_between(mountain_down,color_up,mountain_mid) ||
		 	color_between(mountain_mid,color_up,mountain_up)) ) return false;
		
	}
	
	return true;
}

//sprite player width and height
int World_Character::getCharWidth(){
	return char_width;
}
int World_Character::getCharHeight(){
	return char_height;
}

void World_Character::setLocation(int x, int y){
	locx = x;
	locy = y;
}

Image World_Character::getSprite(){
	return img;
}
void World_Character::setSide(int side){
	this->side = side;
}

int World_Character::getSide(){
	return side;
}
