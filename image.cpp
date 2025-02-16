#include "image.h"
#include <SDL2/SDL_image.h>
#include <string>
#include <cmath>
#include <cstdio>

Image::Image(){
	texture = nullptr;
	texture_rect = {0,0,0,0};
	image_rect = {0,0,0,0};
	texture_width = 0;
	texture_height = 0;
}

Image::~Image(){}

void Image::load_image(std::string file, SDL_Renderer* renderer){
	if(texture != nullptr) SDL_DestroyTexture(texture);
	SDL_Surface *surface = IMG_Load(file.c_str());
	
	if(surface){
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		SDL_FreeSurface(surface);
		SDL_QueryTexture(texture, NULL, NULL, &texture_width, &texture_height);
		std::printf("%i x %i", texture_width, texture_height);
	}
}

bool Image::render_image(SDL_Renderer* renderer){
	if(SDL_RenderCopy(renderer, texture, &texture_rect, &image_rect) != 0){ 
		printf("render copy fucked up: %s\n", SDL_GetError());
		return false;
	}
	return true;	
}
void Image::set_rects(SDL_Rect onscreen, SDL_Rect portion){
	image_rect = onscreen;
	texture_rect = portion;
}

void Image::setTextureRect(SDL_Rect rect){
	texture_rect = rect;
}

SDL_Rect Image::getTextureRect(){
	return texture_rect;
}

SDL_Rect* Image::getpTextureRect(){
	return &texture_rect;
}

SDL_Texture* Image::getTexture(){
	return texture;
}

void Image::updateTextureRect(SDL_Rect rect){
	//todo: think it trough correctly and move out this update functions
	texture_rect.x = ((texture_rect.x+rect.x)< 0 ? texture_height+rect.x : (texture_rect.x+rect.x)%(image_rect.x+texture_height));
	texture_rect.y = ((texture_rect.y+rect.y)< 0 ? texture_width+rect.y : (texture_rect.y+rect.y)%(image_rect.y+texture_width));
	texture_rect.w = abs(texture_rect.w + rect.w); 
	texture_rect.h = abs(texture_rect.h+rect.h);
}

void Image::setImageRect(SDL_Rect rect){
	image_rect = rect;
}

SDL_Rect Image::getImageRect(){
	return image_rect;
}

SDL_Rect* Image::getpImageRect(){
	return &image_rect;
}

void Image::updateImageRect(SDL_Rect rect){
	image_rect.x = abs(image_rect.x+rect.x); 
	image_rect.y = abs(image_rect.y+rect.y);
	image_rect.w = abs(image_rect.w+rect.w);
	image_rect.h = abs(image_rect.h+rect.h);
}

