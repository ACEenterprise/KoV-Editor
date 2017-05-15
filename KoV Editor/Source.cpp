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

	Map map(100,100);

	srand(time(NULL));


	for (int i = 0; i < 100*100; ++i)
	{

	   Animation anim;
	   anim.setSprite(&sprites[0]);
	   anim.setDuration(600);
	   anim.setRepeat(true);
	 
	   map.setSprite(anim, i);
	}

	graphics.create(mainWindow, 1920, 1080);


	DWORD dwFrames = 0;
	
	DWORD dwCurrentTime = 0;
	
	DWORD dwLastUpdateTime = 0;

	DWORD dwElapsedTime = 0;

	while (mainWindow.pollEvent().first != Window::Window_event::close)
	{

		dwFrames++;
		dwCurrentTime = GetTickCount(); // Even better to use timeGetTime()
		dwElapsedTime = dwCurrentTime - dwLastUpdateTime;

		if (dwElapsedTime >= 1000)
		{
			cout << dwFrames * 1000.0 / dwElapsedTime << "\n";
			dwFrames = 0;
			dwLastUpdateTime = dwCurrentTime;
		}

		map.drawMap(graphics);
		graphics.invalidate();
	}


	return 0;
}