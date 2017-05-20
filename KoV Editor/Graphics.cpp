#include"Graphics.h"

Graphics::Graphics()
{
	scale_width = scale_height = width = height = 0;
	x = y = 0;
}

Graphics::Graphics(Window &window, int width, int height)
{
	x = y = 0;
	this->hwnd = window.hwnd;
	HDC hdc = GetDC(hwnd);

	scale_width = this->width = width;
	scale_height = this->height = height;

	mHdc = CreateCompatibleDC(hdc);

	backbuffer = CreateCompatibleBitmap(hdc, width, height);

	ReleaseDC(hwnd, hdc);

	HBITMAP oldBackBuffer = (HBITMAP)SelectObject(mHdc, backbuffer);

	HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(WHITE_BRUSH));


	Rectangle(mHdc, 0, 0, width, height);

	SelectObject(mHdc, oldBrush);
}
void Graphics::create(Window &window, int width, int height)
{
	x = y = 0;
	this->hwnd = window.hwnd;
	HDC hdc = GetDC(hwnd);

	scale_width = this->width = width;
	scale_height = this->height = height;

	mHdc = CreateCompatibleDC(hdc);

	backbuffer = CreateCompatibleBitmap(hdc, width, height);

	ReleaseDC(hwnd, hdc);

	HBITMAP oldBackBuffer = (HBITMAP)SelectObject(mHdc, backbuffer);

	oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(BLACK_BRUSH));

	Rectangle(mHdc, 0, 0, width, height);

}
void Graphics::invalidate()
{
	HDC hdc = GetDC(hwnd);
	StretchBlt(hdc, x, y, scale_width, scale_height, mHdc, 0, 0, width, height, SRCCOPY);
	ReleaseDC(hwnd, hdc);
}


void Graphics::draw(Bitmap *bitmap, int x, int y, int width, int height)
{
	if (bitmap)
	{
		bitmap->create(hwnd);

		HDC hdc = GetDC(hwnd);

		HDC mem = CreateCompatibleDC(hdc);

		HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);


		StretchBlt(mHdc, x, y, width, height, mem, 0, 0, bitmap->width, bitmap->height, SRCCOPY);

		SelectObject(mem, old);

		DeleteDC(mem);
		ReleaseDC(hwnd, hdc);
	}



}

void Graphics::draw(Bitmap *bitmap, int x, int y, int width, int height, int chop_x, int chop_y, int chop_width, int chop_height)
{
	if (bitmap)
	{
		bitmap->create(hwnd);

		HDC hdc = GetDC(hwnd);

		HDC mem = CreateCompatibleDC(hdc);

		HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);


		StretchBlt(mHdc, x, y, width, height, mem, chop_x, chop_y, chop_width, chop_height, SRCCOPY);

		SelectObject(mem, old);

		DeleteDC(mem);
		ReleaseDC(hwnd, hdc);
	}



}


void Graphics::draw(Bitmap *bitmap, int x, int y, int width, int height, int chop_x, int chop_y, int chop_width, int chop_height, Bitmap *mask, int reverse, double rotation)
{
	if (bitmap)
	{
		bitmap->create(hwnd);

		if (mask)
			mask->create_mask(hwnd, reverse);

		HDC hdc = GetDC(hwnd);

		HDC mem = CreateCompatibleDC(hdc);

		HBITMAP old = (HBITMAP)SelectObject(mem, bitmap->bm);

		POINT mid_rotated_top_left = { -width / 2.0 * cos(rotation) - (-height / 2.0 * sin(rotation))
			, -width / 2.0 * sin(rotation) + (-height / 2.0 * cos(rotation)) };
		POINT mid_rotated_top_right = { width / 2.0 * cos(rotation) - (-height / 2.0 * sin(rotation))
			, width / 2.0 * sin(rotation) + (-height / 2.0 * cos(rotation)) };
		POINT mid_rotated_bottom_left = { -width / 2.0 * cos(rotation) - (height / 2.0 * sin(rotation))
			, -width / 2.0 * sin(rotation) + (height / 2.0 * cos(rotation)) };

		POINT p[3] = { { x + width / 2 + mid_rotated_top_left.x,y + height / 2 + mid_rotated_top_left.y },
		{ x + width / 2 + mid_rotated_top_right.x,y + height / 2 + mid_rotated_top_right.y },
		{ x + width / 2 + mid_rotated_bottom_left.x,y + height / 2 + mid_rotated_bottom_left.y } };
		if (mask)
			PlgBlt(mHdc, p, mem, chop_x, chop_y, chop_width, chop_height, mask->bm, chop_x, chop_y);
		else
			PlgBlt(mHdc, p, mem, chop_x, chop_y, chop_width, chop_height, NULL, chop_x, chop_y);

		SelectObject(mem, old);

		DeleteDC(mem);
		ReleaseDC(hwnd, hdc);
	}
	 
	  

}

void Graphics::draw(Sprite *sprite, int x, int y, int width, int height)
{
	if (sprite)
	{
		int position_x = (sprite->current_frame%sprite->frames_per_width)*sprite->width_of_frame;
		int position_y = (sprite->current_frame / sprite->frames_per_width)*sprite->height_of_frame;

		draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame);
	}

}

void Graphics::draw(Sprite *sprite, int frame, int x, int y, int width, int height)
{
	if (sprite)
	{
		frame %= sprite->number_of_frames;
		int position_x = (frame%sprite->frames_per_width)*sprite->width_of_frame;
		int position_y = (frame / sprite->frames_per_width)*sprite->height_of_frame;

		draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame);
	}

}



void Graphics::draw(Sprite *sprite, int x, int y, int width, int height, Bitmap *mask, bool reverse, double rotation)
{
	if (sprite)
	{
		int position_x = (sprite->current_frame%sprite->frames_per_width)*sprite->width_of_frame;
		int position_y = (sprite->current_frame / sprite->frames_per_width)*sprite->height_of_frame;

		draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame, mask, true, rotation);
	}

}

void Graphics::draw(Sprite *sprite, int frame, int x, int y, int width, int height, Bitmap *mask, bool reverse, double rotation)
{
	if (sprite)
	{
		frame %= sprite->number_of_frames;
		int position_x = (frame%sprite->frames_per_width)*sprite->width_of_frame;
		int position_y = (frame / sprite->frames_per_width)*sprite->height_of_frame;

		draw(&sprite->bm, x, y, width, height, position_x, position_y, sprite->width_of_frame, sprite->height_of_frame, mask, true, rotation);
	}

}

void Graphics::draw(int left, int top, int right, int bottom,int fill_color,int outline_color,bool transparency)
{
	if (transparency)
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(NULL_BRUSH));
		HPEN oldPen = (HPEN)SelectObject(mHdc, (HPEN)GetStockObject(DC_PEN));
		SetDCPenColor(mHdc, outline_color);

		Rectangle(mHdc, left, top, right, bottom);
		SelectObject(mHdc, oldBrush);
		SelectObject(mHdc, oldPen);
	}
	else
	{
		HBRUSH oldBrush = (HBRUSH)SelectObject(mHdc, (HBRUSH)GetStockObject(DC_BRUSH));
		HPEN oldPen = (HPEN)SelectObject(mHdc, (HPEN)GetStockObject(DC_PEN));
		SetDCPenColor(mHdc, outline_color);
		SetDCBrushColor(mHdc, fill_color);


		Rectangle(mHdc, left, top, right, bottom);
		SelectObject(mHdc, oldBrush);
		SelectObject(mHdc, oldPen);
	}
}

void Graphics::translate(int x, int y)
{
	RECT rect;
	rect.left = 0;
	rect.right = scale_width;
	rect.bottom = scale_height;
	rect.top = 0;
	InvalidateRect(hwnd, &rect, true);


	this->x = x;
	this->y = y;
}



void Graphics::resize(int width, int height)
{
	scale_width = width;
	scale_height = height;
}

Graphics::~Graphics()
{
	SelectObject(mHdc, oldBrush);
	SelectObject(mHdc, oldBackBuffer);

	DeleteObject(backbuffer);
	DeleteDC(mHdc);
}