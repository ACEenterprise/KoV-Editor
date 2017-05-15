#include"Sprite.h"

Sprite::Sprite()
{
	x = 0;
	y = 0;
	width_of_frame = 0;
	height_of_frame = 0;

	current_frame = 0;
	number_of_frames = 0;
}

bool Sprite::Load(const char* filename, int frames_per_width, int frames_per_height)
{
	if (bm.Load(filename) == true)
	{
		this->frames_per_width = frames_per_width;
		this->frames_per_height = frames_per_height;
		this->number_of_frames = frames_per_width * frames_per_height;


		width_of_frame = bm.getWidth() / frames_per_width;
		height_of_frame = bm.getHeight() / frames_per_height;

		return true;
	}
	else
		return false;
}

void Sprite::set_starting_frame(int x)
{
	if (x >= 0 && x <= number_of_frames)
		current_frame = x;
}

void Sprite::next_frame()
{
	current_frame = (current_frame + 1) % number_of_frames;
}

int Sprite::get_current_frame()
{
	return current_frame;
}

int Sprite::get_number_of_frames()
{
	return number_of_frames;
}

int Sprite::getWidth()
{
	return width_of_frame;
}

int Sprite::getHeight()
{
	return height_of_frame;
}