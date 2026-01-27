#include "window.h"

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
	case WM_CLOSE:
		DestroyWindow(hWnd);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

Window::Window(int input_width, int input_height)
{
	m_hInstance = GetModuleHandle(nullptr);
	const wchar_t* CLASS_NAME = L"Graphics";

	WNDCLASS wndClass = {};
	wndClass.lpszClassName = CLASS_NAME;
	wndClass.hInstance = m_hInstance;
	wndClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	wndClass.lpfnWndProc = WindowProc;

	RegisterClass(&wndClass);

	DWORD style = WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;

	RECT rect;
	rect.left = 250;
	rect.top = 250;
	rect.right = rect.left + input_width;
	rect.bottom = rect.top + input_height;

	AdjustWindowRect(&rect, style, false);

	m_hWnd = CreateWindowEx(
		0,
		CLASS_NAME,
		L"Title",
		style,
		rect.left,
		rect.top,
		rect.right - rect.left,
		rect.bottom - rect.top,
		NULL,
		NULL,
		m_hInstance,
		NULL
	);

	ShowWindow(m_hWnd, SW_SHOW);

	// Initialize pixel buffer to correct screen size
	m_width = input_width;
	m_height = input_height;
	m_pixels.resize(m_width * m_height, RGB(0, 0, 0));
}

Window::~Window()
{
	const wchar_t* CLASS_NAME = L"Graphics";

	UnregisterClass(CLASS_NAME, m_hInstance);
}

bool Window::ProcessMessages()
{
	MSG msg = {};

	while (PeekMessage(&msg, nullptr, 0u, 0u, PM_REMOVE)) 
	{
		if (msg.message == WM_QUIT) { return false; }

		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return true;
}

void Window::DrawFrame() {
	HDC hdc = GetDC(m_hWnd);

	BITMAPINFO bmi = {};
	bmi.bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
	bmi.bmiHeader.biWidth = m_width;
	bmi.bmiHeader.biHeight = -m_height;   // Negative flips so (0,0) is top-left
	bmi.bmiHeader.biPlanes = 1;
	bmi.bmiHeader.biBitCount = 32;       // One COLORREF (RGB) per pixel
	bmi.bmiHeader.biCompression = BI_RGB;

	// Copy pixel buffer to window
	StretchDIBits(
		hdc,
		0, 0, m_width, m_height,         // destination rectangle
		0, 0, m_width, m_height,         // source rectangle
		m_pixels.data(),                 // <-- your pixel array
		&bmi,
		DIB_RGB_COLORS,
		SRCCOPY
	);

	ReleaseDC(m_hWnd, hdc);
}