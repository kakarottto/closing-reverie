#pragma once
#include "image.h"
#include <string>
#include <vector>
#include <SDL2/SDL.h>

class World_Character{
public:
	World_Character();
	World_Character(int type, int side, std::string image_path,SDL_Renderer* renderer);
	~World_Character();
	void setType(int type);
	int getType();
	void setImagePath(std::string image_path);
	std::string getImagePath();
	void setSprite(SDL_Renderer* renderer);
	void setSprite(std::string str,SDL_Renderer* renderer);
	Image getSprite();
	bool render_image( SDL_Renderer* renderer);
	void set_rects();
	void set_rects(SDL_Rect onscreen, SDL_Rect portion);
	bool can_go_trough(SDL_Point point,SDL_Color color_down,SDL_Color color_up);
	void default_set(int pos);
	void do_flip();
	void setFlip(bool flip);
	bool is_fliped();
	int getInmap_privilage();
	void setInmap_privilage(int priv);
	void setLocation(int x, int y);
	void setSide(int side);
	int getSide();
	int getCharWidth();
	int getCharHeight();

	
private:

	Image img;
	std::string image_path;
	int locx, locy;
	int type;
	int side;
	bool flip;
	int row = 0;
	int char_width, char_height;
	int inmap_privilage;//0 walk on ground only,1 trough water only,2 water and ground,3 anywhere 
};
