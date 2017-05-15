#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <algorithm>
#include <fstream>

class Map {
	Tile *MapTiles;
	int *walkable;
	int width, height;

	ofstream out("map.out");

	Map(int width, int height) {
		this->width = width;
		this->height = height;
		MapTiles = new Tile[width * height];
		walkable = new int[width * height];
		
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				walkable[i * width + j] = 0;
			}
		}
	}


	void addWater(int x, int y) {
		int coord = x * width + y;
		MapTiles[coord].setCoord(x, y);
		MapTiles[coord].setHeight(32);
		MapTiles[coord].setWidth(32);

		Sprite *sprite = new Sprite();
		sprite->Load("water", 3, 3);
		MapTiles[coord].setSprite(sprite);
	}


	void addGrass(int x, int y) {
		int coord = x * width + y;
		MapTiles[coord].setCoord(x, y);
		MapTiles[coord].setHeight(32);
		MapTiles[coord].setWidth(32);

		Sprite *sprite = new Sprite();
		sprite->Load("grass", 1, 1);
		MapTiles[coord].setSprite(sprite);

		walkable[coord] = 1;
	}


	void addMine(const char* filename, int x, int y) {
		int coord = x * width + y;
		MapTiles[coord].setCoord(x, y);
		MapTiles[coord].setHeight(64);
		MapTiles[coord].setWidth(96);

		Sprite *sprite = new Sprite();
		sprite->Load(filename, 1, 1);
		MapTiles[coord].setSprite(sprite);

		walkable[(x + 3) * width + y + 1] = 2;
	}


	void addCastle(const char* filename, int x, int y) {
		int coord = x * width + y;
		MapTiles[coord].setCoord(x, y);
		MapTiles[coord].setHeight(192);
		MapTiles[coord].setWidth(192);

		Sprite *sprite = new Sprite();
		sprite->Load(filename, 1, 1);
		MapTiles[coord].setSprite(sprite);

		walkable[(x + 6) * width + y + 3] = 2;
	}

	void output() {
		for (int i = 0; i < height; ++i) {
			for (int j = 0; j < width; ++j) {
				out << walkable[i][j] << ' ';
			}
			out << '\n';
		}
	}

};


#endif