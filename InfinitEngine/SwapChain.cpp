#include "SwapChain.h"
#include "GraphicEngine.h"

SwapChain::SwapChain() : m_current_back_buffer_index(0) {
    // �������������� ���������� m_back_buffers
    const UINT SwapChainBufferCount = 2;
    m_back_buffers.resize(SwapChainBufferCount); // ����� SwapChainBufferCount - ���������� ������� � ������� SwapChain
}

SwapChain::~SwapChain()
{
    // ����������
}

ID3D12DescriptorHeap* SwapChain::getRTVDescriptorHeap() const {
    return m_rtvDescriptorHeap;
}

UINT SwapChain::getCurrentBackBufferIndex() const {
    return m_currentBackBufferIndex;
}

ID3D12Resource* SwapChain::getCurrentBackBuffer() const {
    if (m_back_buffers.empty() || m_current_back_buffer_index >= m_back_buffers.size()) {
        return nullptr; // ���������� nullptr � ������ ������
    }
    return m_back_buffers[m_current_back_buffer_index]; // ���������� ��������� �� ������� ����� �����
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
    if (!GraphicEngine::get()->m_d3d_device || !GraphicEngine::get()->m_dxgi_factory)
    {
        // ���� m_d3d_device ��� m_dxgi_factory �� ����������������, �� �� ����� ������� SwapChain
        return false;
    }

    DXGI_SWAP_CHAIN_DESC m_desc;
    ZeroMemory(&m_desc, sizeof(m_desc));

    m_desc.BufferCount = 1;
    m_desc.BufferDesc.Width = width;
    m_desc.BufferDesc.Height = height;
    m_desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    m_desc.BufferDesc.RefreshRate.Numerator = 60;
    m_desc.BufferDesc.RefreshRate.Denominator = 1;
    m_desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    m_desc.OutputWindow = hwnd;
    m_desc.SampleDesc.Count = 1;
    m_desc.SampleDesc.Quality = 0;
    m_desc.Windowed = TRUE;

    HRESULT hr = GraphicEngine::get()->m_dxgi_factory->CreateSwapChain(GraphicEngine::get()->m_d3d_device, &m_desc, &m_swap_chain);

    if (FAILED(hr))
    {
        // ��������� ������
        return false;
    }

    return true;
}

bool SwapChain::present(bool vsync) {
    m_swap_chain->Present(vsync, NULL);
    return true;
}

bool SwapChain::release()
{
    if (m_swap_chain)
    {
        m_swap_chain->Release();
        m_swap_chain = nullptr; // �������� ��������� ����� ������������ ��������
    }

    // ���������� true, ����� �������� �������� ������������
    return true;
}
