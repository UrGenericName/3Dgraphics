#pragma once
#include <Windows.h>
#include <vector>

LRESULT CALLBACK WindowProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

class Window
{
public:
	Window(int input_width = 640, int input_height = 480);
	Window(const Window&) = delete;
	Window& operator =(const Window&) = delete;
	~Window();

	bool ProcessMessages();

	void DrawFrame();

	int m_width;
	int m_height;

	std::vector<COLORREF> m_pixels;

private:
	HINSTANCE m_hInstance;
	HWND m_hWnd;
};

