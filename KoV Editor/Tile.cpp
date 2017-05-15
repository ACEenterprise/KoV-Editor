#include "Tile.h"

Tile::Tile() {
	x = 0;
	y = 0;
	width = 0;
	height = 0;
	solid = true;
	sprite = NULL;
}

Tile::~Tile() {
	delete sprite;
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

void Tile::setSprite(Sprite *sprite) {
	this->sprite = sprite;
}

int Tile::getWidth() {
	return width;
}

int Tile::getHeight() {
	return height;
}

Sprite* Tile::getSprite() {
	return sprite;
}