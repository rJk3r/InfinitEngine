#pragma once
#include "Window.h"
#include "GraphicEngine.h"
class App : public Window
{
public:
	App();
	~App();

	// Унаследовано через Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

};