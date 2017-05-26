#ifndef MAP_H
#define MAP_H

#include "Tile.h"
#include <algorithm>
#include <fstream>
#include<map>
#include<string>
#include<vector>
#include"Graphics.h"
#include"Animation.h"
class Map {
	Tile *MapTiles;
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
		x = y = 0;

		for (int i = 0; i < height; ++i)
			for (int j = 0; j < width; ++j)
				MapTiles[i*width + j].setState(1);
	}
  
	void drawMap(Graphics &g)
	{

		for(int i=0;i<height;++i)
			for (int j = 0; j < width; ++j)
			{
				if (j * width_tile +x>=0 && j * width_tile+x <=1920 && i * height_tile +y>=0 && i * height_tile +y<=1080 || i==0 && j==0)
				{
					if (MapTiles[i*width + j].getAnimation().getSprite())
					{
						g.draw(MapTiles[i*width + j].getAnimation().getSprite(), MapTiles[i*width + j].getAnimation().getFrame(), j * width_tile+x, i * height_tile+y, width_tile*MapTiles[i*width + j].getSizeW(), height_tile*MapTiles[i*width + j].getSizeH());
						MapTiles[i*width + j].getAnimation().runAnimation();
					}

					if(MapTiles[i*width + j].get_State()==1)
						g.draw(j * width_tile + x, i * height_tile + y, j * width_tile + x + width_tile, i * height_tile + y + height_tile, RGB(255, 255, 255), RGB(0, 255, 0), true);
					else if (MapTiles[i*width + j].get_State() == 0)
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

	void Export(string path)
	{
		ofstream out(path);

		out << width << " " << height<<"\n";

		out << width_tile << " " << height_tile << "\n";

		map<string, int> mp;
		int nr_sprites=0;

		vector<Sprite*> sp;

		for (int i = 0; i<height; ++i)
			for (int j = 0; j < width; ++j)
			{
				if (MapTiles[i*width+j].getAnimation().getSprite())
				{
					if (mp[MapTiles[i*width + j].getAnimation().getSprite()->getPath()] == 0)
					{
						nr_sprites++;
						mp[MapTiles[i*width + j].getAnimation().getSprite()->getPath()] = nr_sprites;

						sp.push_back(MapTiles[i*width + j].getAnimation().getSprite());
					}
				}
			}

		out << sp.size() << "\n";

		for (int i = 0; i < sp.size(); ++i)
		{
			out << sp[i]->getPath() << " " << sp[i]->getFramesPerWidth()<<" "
				   << sp[i]->getFramesPerHeight()<<"\n";
		}

		for (int i = 0; i<height; ++i)
			for (int j = 0; j < width; ++j)
			{
				if (MapTiles[i*width + j].getAnimation().getSprite())
				{
					out << mp[MapTiles[i*width + j].getAnimation().getSprite()->getPath()] << " ";
					out << MapTiles[i*width + j].getSizeW() << " " << MapTiles[i*width + j].getSizeH() << " " << MapTiles[i*width + j].get_State() << "\n";
				}
				else
				{
					out << "0 0 0 " << MapTiles[i*width + j].get_State()<<"\n";
				}
			}

		out.close();
	}

	void Import(string path, vector<Sprite> &sprites)
	{
		sprites.clear();

		ifstream in(path);

		in >> width >> height;
		in >> width_tile >> height_tile;

		delete[] MapTiles;

		MapTiles = new Tile[width * height];

		int n;

		in >> n;

		for (int i = 0; i < n; ++i)
		{
			Sprite sprite;

			sprites.push_back(sprite);

			string pt;
			int w, h;

			in >> pt >> w >> h;

			sprites[i].Load(pt.c_str(), w, h);
		}

		for (int i = 0; i < height; ++i)
		{
			int id,w,h,s;
		
			for (int j = 0; j < width; ++j)
			{

				in >> id >> w >> h >> s;

				if (id)
				{
					Animation anim;
					anim.setSprite(&sprites[id - 1]);
					anim.setDuration(500);
					anim.setRepeat(true);

					MapTiles[i*width + j].setAnimation(anim);
				}

				MapTiles[i*width + j].setSizeW(w);
				MapTiles[i*width + j].setSizeH(h);
				MapTiles[i*width + j].setState(s);
			}
		}

	}

};


#endif