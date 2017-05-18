#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <algorithm>
#include <fstream>
#include"Graphics.h"
#include"Animation.h"
class Map {
	Tile *MapTiles;
	int *walkable;
	int width, height;

public:

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
  
	void drawMap(Graphics &g)
	{

		for(int i=0;i<height;++i)
			for (int j = 0; j < width; ++j)
			{
				if (j * 128 >= 0 && j * 128 <= 1920 && i * 128 >= 0 && i * 128 <= 1080)
				{
					g.draw(MapTiles[i*width + j].getAnimation().getSprite(), MapTiles[i*width + j].getAnimation().getFrame(), j * 128, i * 128, 128, 128);
					MapTiles[i*width + j].getAnimation().runAnimation();
				}
			}
	}

	void setSprite(Animation anim, int i)
	{
		MapTiles[i].setAnimation(anim);
	}


};


#endif