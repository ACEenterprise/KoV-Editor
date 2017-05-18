#include <iostream>
#include<vector>
#include<string>
#include "Graphics.h"
#include "Animation.h"
#include"Map.h"
#include<time.h>
using namespace std;

vector<Sprite> sprites;

int main() {

	ifstream paths("paths.txt");

	int number_of_sprites;

	paths >> number_of_sprites;

	Sprite sprite;

	for (int i = 1; i <= number_of_sprites; ++i)
		sprites.push_back(sprite);

	for (int i = 1; i <= number_of_sprites; ++i)
	{
		string path;
		int number_width;
		int number_height;
		paths >> path >> number_width >> number_height;


		sprites[i - 1].Load(path.c_str(), number_width, number_height);

	}

	paths.close();

	Window mainWindow;
	mainWindow.create_window("KoV Editor", 0, 0, 1920, 1080);

	Graphics graphics;
	 
	Map map(10,10,128,128);

	srand(time(NULL));

	graphics.create(mainWindow, 1920, 1080);


	DWORD dwFrames = 0;
	
	DWORD dwCurrentTime = 0;
	
	DWORD dwLastUpdateTime = 0;

	DWORD dwElapsedTime = 0;

	pair<int, int> ev;

	int ind = 0;

	int mouse_x = 0, mouse_y = 0;
	int sz_w=1, sz_h=1;
	while ((ev=mainWindow.pollEvent()).first != Window::Window_event::close)
	{

		if (ev.first == Window::Key_event::key_pressed)
		{
			if (ev.second == Window::Keys::_A)
			{
				ind = (sprites.size() + ind - 1) % sprites.size();
			}
			else if (ev.second == Window::Keys::_D)
			{
				ind = (sprites.size() + ind + 1) % sprites.size();
			}
			else if (ev.second == Window::Keys::_I)
			{
				map.setY(map.getY() + map.getHeightTile());
			}
			else if ((ev.second == Window::Keys::_J))
			{
				map.setX(map.getX() + map.getWidthTile());
			}
			else if ((ev.second == Window::Keys::_K))
			{
				map.setY(map.getY() - map.getHeightTile());
			}
			else if ((ev.second == Window::Keys::_L))
			{
				map.setX(map.getX() - map.getWidthTile());
			}
			else if ((ev.second == Window::Keys::_1))
			{
				sz_w++;
			}
			else if ((ev.second == Window::Keys::_2))
			{
				if(sz_w>1)
					sz_w--;
			}
			else if ((ev.second == Window::Keys::_3))
			{
				sz_h++;
			}
			else if ((ev.second == Window::Keys::_4))
			{
				if(sz_h>1)
					sz_h--;
			}

		}

		if (ev.first == Window::Mouse_event::moved)
		{
			mouse_x = ev.second & 0xFFFF;
			mouse_y = ev.second >> 16;

			mouse_x = (mouse_x / map.getWidthTile())*map.getWidthTile();
			mouse_y = (mouse_y / map.getHeightTile())*map.getHeightTile();

		}

		if (ev.first == Window::Mouse_event::left_pressed)
		{
			if (mouse_x + 1 >= map.getX() && mouse_x + 1 <= map.getX() + map.getWidth()*map.getWidthTile()
				&& mouse_y + 1 >= map.getY() && mouse_y + 1 <= map.getY() + map.getHeight()*map.getHeightTile())
			{
				Animation anim;
				anim.setSprite(&sprites[ind]);
				anim.setDuration(1000);
				anim.setRepeat(true);

				map.setAnimation(anim, (mouse_x - map.getX()) / map.getWidthTile(), (mouse_y - map.getY()) / map.getHeightTile());
			}
		}

		dwFrames++;
		dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
		dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

		if (dwElapsedTime >= 1000)
		{
			cout << dwFrames * 1000.0 / dwElapsedTime << "\n";
			dwFrames = 0;
			dwLastUpdateTime = dwCurrentTime;
		}

		graphics.draw(0, 0, 1920, 1080, RGB(0, 0, 0));

		map.drawMap(graphics);
		if(mouse_x+1 >=map.getX() && mouse_x+1<=map.getX()+map.getWidth()*map.getWidthTile()
			&& mouse_y + 1 >= map.getY() && mouse_y + 1 <= map.getY() + map.getHeight()*map.getHeightTile())
			graphics.draw(&sprites[ind], mouse_x, mouse_y, map.getWidthTile(), map.getHeightTile());
		graphics.invalidate();
	}

	//this is a test comment.
	return 0;
}