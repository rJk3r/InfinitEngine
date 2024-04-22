// App.h

#pragma once

#include "Window.h"
#include "GraphicEngine.h"
#include "SwapChain.h" // Добавляем SwapChain.h
#include "d3dx12.h"
#include <d3d12.h>

class App : public Window
{
public:
    App();
    ~App();

    // Унаследовано через Window
    void onCreate() override;
    void onUpdate() override;
    void onDestroy() override;
private:
    SwapChain* m_swap_chain;

};
