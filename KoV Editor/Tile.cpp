#include "Tile.h"
#include"Animation.h"
Tile::Tile() {
	solid = true;
	size_w = 1;
	size_h = 1;
}

Tile::~Tile() {
	
}


void Tile::setAnimation(Animation animation) {
	this->animation = animation;
}
 
Animation &Tile::getAnimation() {
	return animation;
}

void Tile::setSizeW(int size_w)
{
	this->size_w = size_w;
}
void Tile::setSizeH(int size_h)
{
	this->size_h = size_h;
}
int Tile::getSizeW()
{
	return size_w;
}
int Tile::getSizeH()
{
	return size_h;
}