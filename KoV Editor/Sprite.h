#ifndef SPRITE_H
#define SPRITE_H

#include"Bitmap.h"

class Sprite
{
private:
	friend class Graphics;
	Bitmap bm;

	int x, y;
	int number_of_frames;
	int frames_per_width;
	int frames_per_height;

	int current_frame;
	int width_of_frame;
	int height_of_frame;

public:
	Sprite();

	bool Load(const char* filename, int frames_per_width, int frames_per_height);

	void set_starting_frame(int x);

	void next_frame();

	int get_current_frame();

	int get_number_of_frames();

	int getWidth();

	int getHeight();

};

#endif