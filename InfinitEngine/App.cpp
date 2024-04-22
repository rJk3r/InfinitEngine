#include "App.h"
#include <iostream>
#include "SwapChain.h"
#include "GraphicEngine.h"
#include "d3dx12.h"
#include <d3d12.h>

App::App() {
    m_swap_chain = nullptr;
}

App::~App() {
    if (m_swap_chain) {
        delete m_swap_chain;
        m_swap_chain = nullptr;
    }
}

void App::onCreate() {
    GraphicEngine::get()->init();
    m_swap_chain = GraphicEngine::get()->createSwapChain();

    RECT rc = this->getClientWindowRect();
    m_swap_chain->init(this->m_hwnd, rc.right - rc.left, rc.bottom - rc.top);
}

void App::onUpdate() {

    ID3D12Resource* currentBackBuffer = m_swap_chain->getCurrentBackBuffer();
    if (currentBackBuffer) {
        // ��������� ���������� ������ ��� ����������������� ���������� ������
        ID3D12GraphicsCommandList* commandList = GraphicEngine::get()->getCommandList();
        if (commandList) {
            // ������� ���������� ��������� ������, ���� �� ������
            commandList->Close();

            // ������� �������� ������ �����
            CD3DX12_RESOURCE_BARRIER barrier = CD3DX12_RESOURCE_BARRIER::Transition(currentBackBuffer, D3D12_RESOURCE_STATE_PRESENT, D3D12_RESOURCE_STATE_RENDER_TARGET);
            commandList->ResourceBarrier(1, &barrier);

            FLOAT clearColor[] = { 1.0f, 0.0f, 0.0f, 1.0f }; // ���� ������� (�������)
            CD3DX12_CPU_DESCRIPTOR_HANDLE rtvHandle(m_swap_chain->getRTVDescriptorHeap()->GetCPUDescriptorHandleForHeapStart(), m_swap_chain->getCurrentBackBufferIndex(), GraphicEngine::get()->getRTVDescriptorSize());
            commandList->ClearRenderTargetView(rtvHandle, clearColor, 0, nullptr);

            barrier = CD3DX12_RESOURCE_BARRIER::Transition(currentBackBuffer, D3D12_RESOURCE_STATE_RENDER_TARGET, D3D12_RESOURCE_STATE_PRESENT);
            commandList->ResourceBarrier(1, &barrier);

            Window::onUpdate();
            // ���������� ������� �� ����������
            GraphicEngine::get()->getCommandQueue()->ExecuteCommandLists(1, CommandListCast(&commandList));
        }
    }

}

void App::onDestroy() {
    Window::onDestroy();
    GraphicEngine::get()->release();
}
