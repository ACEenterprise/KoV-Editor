#include"Gui.h"
bool Window::create_window(const char *title, int x, int y, int width, int height)
{

	wndclass.cbSize = sizeof(wndclass);
	wndclass.cbClsExtra = NULL;
	wndclass.cbWndExtra = NULL;
	wndclass.hInstance = GetModuleHandle(NULL);
	wndclass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndclass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndclass.lpszMenuName = NULL;
	wndclass.style = NULL;
	wndclass.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wndclass.lpszClassName = "window";
	wndclass.lpfnWndProc = WndProc;

	if (!RegisterClassEx(&wndclass))
		return false;

	hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		"window",
		title,
		WS_OVERLAPPEDWINDOW,
		x, y, width, height,
		NULL, NULL, wndclass.hInstance, NULL);

	RECT rect;

	GetClientRect(hwnd, &rect);

	client_width = rect.right;
	client_height = rect.bottom;

	if (!hwnd)
		return false;


	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);


	this->width = width;
	this->height = height;

	mod_width = width;
	mod_height = height;

	return true;
}

std::pair<int, int> Window::pollEvent()
{
	POINT p;
	if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
		int nr = 0;
		switch (msg.message)
		{

		case WM_QUIT:
			return std::make_pair(Window_event::close, 0);
			break;

		case WM_KEYDOWN:
			nr = 0;

			if(LOWORD(msg.wParam)>='A' && LOWORD(msg.wParam) <='Z')
                 return std::make_pair(Key_event::key_pressed, LOWORD(msg.wParam)-'A');
			
			if (LOWORD(msg.wParam) >= '0' && LOWORD(msg.wParam) <= '9')
				return std::make_pair(Key_event::key_pressed, LOWORD(msg.wParam)-'0'+52);

			break;
		case WM_KEYUP:
			nr = 0;
			if (LOWORD(msg.wParam) >= 'A' && LOWORD(msg.wParam) <= 'Z')
				return std::make_pair(Key_event::key_released, LOWORD(msg.wParam) - 'A');

			if (LOWORD(msg.wParam) >= '0' && LOWORD(msg.wParam) <= '9')
				return std::make_pair(Key_event::key_released, LOWORD(msg.wParam) - '0' + 52);
			break;
		case WM_LBUTTONDOWN:
			GetCursorPos(&p);
			ScreenToClient(hwnd, &p);
			
			return std::make_pair(Mouse_event::left_pressed, p.x | ((p.y)<<16));
			break;
		case WM_LBUTTONUP:
			GetCursorPos(&p);
			ScreenToClient(hwnd, &p);

			return std::make_pair(Mouse_event::left_released, p.x | ((p.y) << 16));
			break;

		  //RIGHT CLICK AND ARROWS TO DO
		}
	}
	return std::make_pair(-1, 0);
}

void Window::destroy()
{
	DestroyWindow(hwnd);
}

int Window::getWidth()
{
	return mod_width;
}

int Window::getHeight()
{
	return mod_height;
}

int Window::getClientWidth()
{
	return client_width;
}

int Window::getClientHeight()
{
	return client_height;
}

void Window::setWindowTitle(std::string title)
{
	SetWindowText(hwnd, title.c_str());
}

void Window::make_fullscreen()
{
	HDC hDC = ::GetWindowDC(NULL);
	::SetWindowPos(hwnd, NULL, 0, 0, ::GetDeviceCaps(hDC, HORZRES), ::GetDeviceCaps(hDC, VERTRES), SWP_FRAMECHANGED);

	mod_width = ::GetDeviceCaps(hDC, HORZRES);
	mod_height = ::GetDeviceCaps(hDC, VERTRES);

	ReleaseDC(NULL, hDC);

	RECT rect;

	GetClientRect(hwnd, &rect);

	client_width = rect.right;
	client_height = rect.bottom;
}

void Window::restore()
{
	HDC hDC = ::GetWindowDC(NULL);
	::SetWindowPos(hwnd, NULL, 0, 0, width, height, SWP_FRAMECHANGED);

	mod_width = width;
	mod_height = height;

	ReleaseDC(NULL, hDC);

	RECT rect;

	GetClientRect(hwnd, &rect);

	client_width = rect.right;
	client_height = rect.bottom;
}