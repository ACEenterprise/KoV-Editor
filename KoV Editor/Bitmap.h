#ifndef BITMAP_H
#define BITMAP_H

#include<Windows.h>
#include<fstream>
using namespace std;
class Bitmap
{

private:
	friend class Graphics;

	BITMAPFILEHEADER bmH;
	BITMAPINFOHEADER bmiH;
	HBITMAP bm;
	BITMAPINFO *bmi;
	unsigned char *pixels;
	unsigned char *color_table;

	int width;
	int height;

	void create(HWND hwnd);

	void create_mask(HWND hwnd, bool reverse);

public:
	Bitmap();

	bool Load(const char *file_name);

	int getWidth();

	int getHeight();

	~Bitmap();
};

#endif