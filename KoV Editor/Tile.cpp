#include "Tile.h"
#include"Animation.h"
Tile::Tile() {
	solid = true;
}

Tile::~Tile() {
	
}


void Tile::setAnimation(Animation animation) {
	this->animation = animation;
}
 
Animation &Tile::getAnimation() {
	return animation;
}