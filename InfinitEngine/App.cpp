#include "App.h"
#include <iostream>

App::App()
{
}
App::~App()
{
}

void App::onCreate()
{
	GraphicEngine::get()->init();
}

void App::onUpdate()
{
}

void App::onDestroy()
{
	Window::onDestroy();
	GraphicEngine::get()->release();
}
