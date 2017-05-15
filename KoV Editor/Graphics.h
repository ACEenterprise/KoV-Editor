#ifndef GRAPHICS_H
#define GRAPHICS_H
#include<Windows.h>
#include<fstream>
#include<iostream>
#include"Gui.h"
#include"Bitmap.h"
#include"Sprite.h"
using namespace std;

class Graphics
{
private:

	HWND hwnd;
	HDC mHdc;
	HBITMAP backbuffer, oldBackBuffer;
	HBRUSH oldBrush;
	int width, height;
	int scale_width, scale_height;

	int x, y;

public:
	Graphics();

	Graphics(Window &window, int width, int height);

	void create(Window &window, int width, int height);

	void invalidate();

	void draw(Bitmap *bitmap, int x, int y, int width, int height);

	void draw(Bitmap *bitmap, int x, int y, int width, int height, int chop_x, int chop_y, int chop_width, int chop_height);

	void draw(Bitmap *bitmap, int x, int y, int width, int height, int chop_x, int chop_y, int chop_width, int chop_height, Bitmap *mask, int reverse, double rotation);

	void draw(Sprite *sprite, int x, int y, int width, int height);

	void draw(Sprite *sprite, int frame, int x, int y, int width, int height);

	void draw(Sprite *sprite, int x, int y, int width, int height, Bitmap *mask, bool reverse, double rotation);

	void draw(Sprite *sprite, int frame, int x, int y, int width, int height, Bitmap *mask, bool reverse, double rotation);

	void draw(int left, int top, int right, int bottom);

	void translate(int x, int y);

	void resize(int width, int height);

	~Graphics();

};

#endif