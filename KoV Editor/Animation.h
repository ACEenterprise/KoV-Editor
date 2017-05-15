#ifndef ANIMATION_H
#define ANIMATION_H

#include"Sprite.h"


class Animation
{
private:
	Sprite *sprite;
	int duration;
	long long last_time;
	long long current_time;
	double mili_per_frame;
	bool repeat;
	int frame;

public:

	Animation();

	void setSprite(Sprite *sprite);

	void setDuration(int duration);

	void restart();

	void setRepeat(bool state);

	int getFrame();

	void runAnimation();

	Sprite* getSprite();
};

#endif;