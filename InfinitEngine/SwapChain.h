#pragma once

#include <wrl/client.h> // �������� ������������ ���� ��� ComPtr
#include <vector>
#include <d3d12.h>
#include <dxgi.h>

class SwapChain
{
public:
    SwapChain();
    ~SwapChain();

    bool init(HWND hwnd, UINT width, UINT height);

    ID3D12DescriptorHeap* getRTVDescriptorHeap() const;
    UINT getCurrentBackBufferIndex() const;

    ID3D12Resource* getCurrentBackBuffer() const;

    bool present(bool vsync);
    bool release();

private:
    ID3D12DescriptorHeap* m_rtvDescriptorHeap;
    UINT m_currentBackBufferIndex;
    std::vector<ID3D12Resource*> m_back_buffers;
    IDXGISwapChain* m_swap_chain = nullptr; // �������������� ��������� m_swap_chain ��������� nullptr
    UINT m_current_back_buffer_index = 0; // ��������� ���������� ��� ������������ �������� ������
};
