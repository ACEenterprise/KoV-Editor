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
		solid - bool value that tells either the player can walk or not on this tile.
		sprite - the sprite the current tile is holding. might get trickier for castels
				 or structures that doesn't respect the width and height.
	*/
private:

	bool solid;
	Animation animation;

public:

	//Contructor and deconstructor
	Tile();
	~Tile();
	void setAnimation(Animation animation);
	Animation &getAnimation();

};

#endif