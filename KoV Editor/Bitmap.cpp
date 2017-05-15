#include"Bitmap.h"

Bitmap::Bitmap()
{
	width = height = 0;
	pixels = NULL;
	color_table = NULL;
	bmi = NULL;
	bm = NULL;
}

void Bitmap::create(HWND hwnd)
{
	if (bm == NULL)
	{
		bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

		ZeroMemory(bmi, sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

		bmi->bmiHeader = bmiH;

		memcpy(bmi->bmiColors, color_table, bmH.bfOffBits - 54);

		HDC dc = GetDC(hwnd);

		bm = CreateDIBitmap(dc, &bmiH, CBM_INIT, pixels, bmi, DIB_RGB_COLORS);

		ReleaseDC(hwnd, dc);
	}
}

void Bitmap::create_mask(HWND hwnd, bool reverse)
{
	if (bm == NULL)
	{
		bmi = (BITMAPINFO*)malloc(sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

		ZeroMemory(bmi, sizeof(BITMAPINFO) + bmH.bfOffBits - 54);

		bmi->bmiHeader = bmiH;

		memcpy(bmi->bmiColors, color_table, bmH.bfOffBits - 54);

		HDC dc = GetDC(hwnd);

		if (reverse)
		{
			for (int i = 0; i < bmH.bfSize - bmH.bfOffBits; ++i)
				pixels[i] ^= 0xFF;
		}

		bm = CreateDIBitmap(NULL, &bmiH, CBM_INIT, pixels, bmi, DIB_RGB_COLORS);

		ReleaseDC(hwnd, dc);
	}
}

bool Bitmap::Load(const char *file_name)
{
	ifstream in(file_name, fstream::binary);


	in.read((char*)&bmH.bfType, 2);

	if (bmH.bfType != 19778)
		return false;

	in.read((char*)&bmH.bfSize, 4);

	in.read((char*)&bmH.bfReserved1, 2);

	in.read((char*)&bmH.bfReserved2, 2);

	in.read((char*)&bmH.bfOffBits, 4);

	in.read((char*)&bmiH.biSize, 4);

	in.read((char*)&bmiH.biWidth, 4);

	width = bmiH.biWidth;

	in.read((char*)&bmiH.biHeight, 4);

	height = bmiH.biHeight;

	in.read((char*)&bmiH.biPlanes, 2);

	in.read((char*)&bmiH.biBitCount, 2);

	in.read((char*)&bmiH.biCompression, 4);

	in.read((char*)&bmiH.biSizeImage, 4);

	in.read((char*)&bmiH.biXPelsPerMeter, 4);

	in.read((char*)&bmiH.biYPelsPerMeter, 4);

	in.read((char*)&bmiH.biClrUsed, 4);

	in.read((char*)&bmiH.biClrImportant, 4);

	if (bmH.bfOffBits - 54 != 0)
	{
		color_table = new unsigned char[bmH.bfOffBits - 54];
		in.read((char*)color_table, bmH.bfOffBits - 54);
	}

	pixels = new unsigned char[bmH.bfSize - bmH.bfOffBits];
	in.read((char*)pixels, bmH.bfSize - bmH.bfOffBits);

	return true;
}

int Bitmap::getWidth()
{
	return width;
}

int Bitmap::getHeight()
{
	return height;
}

Bitmap::~Bitmap()
{
	delete[] pixels;

	if (color_table)
		delete[] color_table;

	if (bmi)
		delete bmi;

	DeleteObject(&bmiH);
}