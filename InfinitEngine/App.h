#pragma once
#include "Window.h"
#include "GraphicEngine.h"
class App : public Window
{
public:
	App();
	~App();

	// ������������ ����� Window
	void onCreate() override;
	void onUpdate() override;
	void onDestroy() override;

};