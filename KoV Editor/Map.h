#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <algorithm>

class Map {
	Tile *MapTiles;

	Map(int width, int height) {
		MapTiles = new Tile[width * height];
	}



};


#endif