#include "SwapChain.h"
#include "GraphicEngine.h"
#include <iostream>

constexpr UINT SwapChainBufferCount = 2;


SwapChain::SwapChain() : m_current_back_buffer_index(0), m_rtvDescriptorHeap(nullptr) {
    // Инициализируем переменную m_back_buffers
    m_back_buffers.resize(SwapChainBufferCount); // Здесь SwapChainBufferCount - количество буферов в цепочке SwapChain
}

ID3D12DescriptorHeap* SwapChain::getRTVDescriptorHeap() const {
    std::cout << "RTVDescriptor: " << m_rtvDescriptorHeap << "\n";
    return m_rtvDescriptorHeap;
}

UINT SwapChain::getCurrentBackBufferIndex() const {
    std::cout << "m_currentBackBufferIndex: " << m_currentBackBufferIndex << "\n";
    return m_currentBackBufferIndex;
}

ID3D12Resource* SwapChain::getCurrentBackBuffer() const {
    if (m_back_buffers.empty() || m_current_back_buffer_index >= m_back_buffers.size()) {
        std::cout << "m_back_buffers is empty or index is out of bounds\n";
        return nullptr; // Возвращаем nullptr в случае ошибки
    }
    return m_back_buffers[m_current_back_buffer_index]; // Возвращаем указатель на текущий буфер кадра
}

bool SwapChain::init(HWND hwnd, UINT width, UINT height)
{
    if (!GraphicEngine::get()->m_d3d_device || !GraphicEngine::get()->m_dxgi_factory)
    {
        // Если m_d3d_device или m_dxgi_factory не инициализированы, то не можем создать SwapChain
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

    // Инициализация переменной rtvHeapDesc
    D3D12_DESCRIPTOR_HEAP_DESC rtvHeapDesc = {};
    rtvHeapDesc.NumDescriptors = SwapChainBufferCount; // Количество дескрипторов в куче
    rtvHeapDesc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV; // Тип кучи
    rtvHeapDesc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE; // Флаги (в данном случае нет дополнительных флагов)

    HRESULT hr = GraphicEngine::get()->m_d3d_device->CreateDescriptorHeap(&rtvHeapDesc, IID_PPV_ARGS(&m_rtvDescriptorHeap));
    if (FAILED(hr))
    {
        // Обработка ошибки
        return false;
    }

    hr = GraphicEngine::get()->m_dxgi_factory->CreateSwapChain(GraphicEngine::get()->m_d3d_command_queue, &m_desc, &m_swap_chain);
    if (FAILED(hr))
    {
        // Обработка ошибки
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
    m_swap_chain->Release();
    delete this;

    // Возвращаем true, чтобы показать успешное освобождение
    return true;
}

SwapChain::~SwapChain()
{
    // Деструктор
}