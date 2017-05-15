#include "Tile.h"
#include"Animation.h"
Tile::Tile() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	solid = true;
}

Tile::~Tile() {
	
}

void Tile::setCoord(int x, int y) {
	this->x = x;
	this->y = y;
}

void Tile::setWidth(int widht) {
	this->width = widht;
}

void Tile::setHeight(int height) {
	this->height = height;
}

void Tile::setAnimation(Animation animation) {
	this->animation = animation;
}

int Tile::getWidth() {
	return width;
}
 
int Tile::getHeight() {
	return height;
}
 
Animation &Tile::getAnimation() {
	return animation;
}