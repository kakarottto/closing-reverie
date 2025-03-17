#pragma once
#include <SDL2/SDL.h>
#include <string>
class Image{
public:
	Image();
	~Image();
	void load_image(std::string file, SDL_Renderer* renderer);
	bool render_image( SDL_Renderer* renderer);
	void set_rects(SDL_Rect onscreen, SDL_Rect portion);
	void setTextureRect(SDL_Rect rect);
	SDL_Rect getTextureRect();
	SDL_Rect* getpTextureRect();
	void updateTextureRect(SDL_Rect rect);
	void setImageRect(SDL_Rect rect);
	SDL_Rect getImageRect();
	SDL_Rect* getpImageRect();
	int getTextureWidth();
	int getTextureHeight();
	SDL_Texture* getTexture();
	void updateImageRect(SDL_Rect rect);
private:
	SDL_Texture* texture;
	int texture_width, texture_height;
	SDL_Rect texture_rect;	//the part of the texture
	SDL_Rect image_rect;	//the part of the screen where its gonna be placed
};
