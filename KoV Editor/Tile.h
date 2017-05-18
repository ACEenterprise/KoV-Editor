#ifndef TILE_H
#define TILE_H

#include <iostream>
#include "Sprite.h"
#include"Animation.h"

/*
	Tile Class.
	Ment to represent the smallest part of the map.
*/

class Tile {
	/*
		x, y - left upper corner coordinates.
		widht, height - widht and height of the tile. i assume there will be the same 
						width and height for all the tiles so i might delete those 2.
		solid - bool value that tells either the player can walk or not on this tile.
		sprite - the sprite the current tile is holding. might get trickier for castels
				 or structures that doesn't respect the width and height.
	*/
private:

	int x, y, width, height;
	bool solid;
	Animation animation;

public:

	//Contructor and deconstructor
	Tile();
	~Tile();
	 
	     
	void setCoord(int x, int y);
	void setWidth(int width);
	void setHeight(int height);
	void setAnimation(Animation animation);
	   
	int getWidth();
	int getHeight();
	Animation &getAnimation();

};

#endif