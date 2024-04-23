#include "Window.h"
#include <Windows.h>

Window* win = nullptr;

Window::Window()
{
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg)
	{
	case WM_CREATE:
	{
		// Event when window created
		win->setHWND(hwnd);
		win->onCreate();
		break;
	}
	case WM_DESTROY:
	{
		// Event when window destroyed
		win->onDestroy();
		::PostQuitMessage(0);
		break;
	}
	default:
	{
		return ::DefWindowProc(hwnd, msg, wParam, lParam);
	}
	}
}
bool Window::init() {
	WNDCLASSEX window;
	window.cbClsExtra = NULL;
	window.cbSize = sizeof(WNDCLASSEX);
	window.cbWndExtra = NULL;
	window.hbrBackground = (HBRUSH)COLOR_WINDOW;
	window.hCursor = LoadCursor(NULL, IDC_ARROW);
	window.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	window.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	window.hInstance = NULL;
	window.lpszClassName = "InfinitEngine";
	window.lpszMenuName = "";
	window.style = NULL;
	window.lpfnWndProc = &WndProc;
	if (!::RegisterClassEx(&window)) // If the class registration is fail, the function will return false
		return false;

	if (!win)
		win = this;

	// Window creation
	m_hwnd = ::CreateWindowEx(WS_EX_OVERLAPPEDWINDOW, window.lpszClassName, "Infinite Engine", WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, 1600, 900,
		NULL, NULL, NULL, NULL);

	// if creation fail return false

	if (!m_hwnd) {
		return false;
	}

	//show up the window
	::ShowWindow(m_hwnd, SW_SHOW);
	::UpdateWindow(m_hwnd);

	// set flag that window initialized to "true"
	m_is_run = true;
	return true;
}

bool Window::broadcast()
{
	MSG msg;

	this->onUpdate();

	while ((::PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))>0)
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	Sleep(0);

	return true;
}

bool Window::release()
{
	//Destroy window
	if (!::DestroyWindow(m_hwnd))
		return false;
	return true;
}

bool Window::isRun()
{
	return m_is_run;
}

RECT Window::getClientWindowRect()
{
	RECT rc;
	::GetClientRect(this->m_hwnd, &rc);
	return rc;
}

void Window::setHWND(HWND hwnd)
{
	this->m_hwnd = hwnd;
}

void Window::onDestroy()
{
	// if the window is not initialized
	m_is_run = false;
}

void Window::onCreate() {
	// Реализация метода onUpdate
}

void Window::onUpdate() {
	// Реализация метода onUpdate
}

Window::~Window()
{

}
