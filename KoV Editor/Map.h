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
	int width_tile, height_tile;
	int x, y;

public:

	Map(int width, int height,int width_tile,int height_tile) {
		this->width = width;
		this->height = height;
		this->width_tile = width_tile;
		this->height_tile = height_tile;

		MapTiles = new Tile[width * height];
		walkable = new int[width * height];
		x = y = 0;
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
				if (j * width_tile +x>=0 && j * width_tile+x <=1920 && i * height_tile +y>=0 && i * height_tile +y<=1080)
				{
					if (MapTiles[i*width + j].getAnimation().getSprite())
					{
						g.draw(MapTiles[i*width + j].getAnimation().getSprite(), MapTiles[i*width + j].getAnimation().getFrame(), j * width_tile+x, i * height_tile+y, width_tile*MapTiles[i*width + j].getSizeW(), height_tile*MapTiles[i*width + j].getSizeH());
						MapTiles[i*width + j].getAnimation().runAnimation();
					}

					if(MapTiles[i*width + j].get_State()==0)
						g.draw(j * width_tile + x, i * height_tile + y, j * width_tile + x + width_tile, i * height_tile + y + height_tile, RGB(255, 255, 255), RGB(0, 255, 0), true);
					else if (MapTiles[i*width + j].get_State() == 1)
						g.draw(j * width_tile + x, i * height_tile + y, j * width_tile + x + width_tile, i * height_tile + y + height_tile, RGB(255, 255, 255), RGB(255, 0, 0), true);
				}
			}
	}

	void setAnimation(Animation anim, int x,int y,int size_w,int size_h)
	{
		MapTiles[y*width + x].setSizeW(size_w);
		MapTiles[y*width + x].setSizeH(size_h);
		MapTiles[y*width + x].setAnimation(anim);
	}

	void setTileState(int x, int y, int state)
	{
		MapTiles[y*width + x].setState(state);
	}

	void setX(int x)
	{
		this->x = x;
	}

	void setY(int y)
	{
		this->y = y;
	}
	
	int getX()
	{
		return x;
	}

	int getY()
	{
		return y;
	}

	int getWidth()
	{
		return width;
	}
	
	int getHeight()
	{
		return height;
	}

	int getWidthTile()
	{
		return width_tile;
	}

	int getHeightTile()
	{
		return height_tile;
	}


};


#endif