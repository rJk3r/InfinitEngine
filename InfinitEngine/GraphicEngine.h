#pragma once
#include <d3d12.h>
#include "d3dx12.h"
#include <dxgi.h>

class SwapChain;


class GraphicEngine
{
public:
	GraphicEngine();
	//Initialize the GraphicsEngine and DirectX 12 Device
	bool init();

	//Releases all resources loaded
	bool release();
	~GraphicEngine();
public:
	SwapChain* createSwapChain();
	UINT getRTVDescriptorSize() const;
public:
	static GraphicEngine* get();
public:
	ID3D12Device* getDevice() const { return m_d3d_device; }
	ID3D12CommandQueue* getCommandQueue() const { return m_d3d_command_queue; }
	ID3D12GraphicsCommandList* getCommandList() const { return m_command_list; }

private:
	ID3D12Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D12CommandQueue* m_d3d_command_queue = nullptr;
	ID3D12GraphicsCommandList* m_command_list = nullptr;
	ID3D12CommandAllocator* m_command_allocator = nullptr;
private:
	IDXGIDevice* m_dxgi_device = nullptr;
	IDXGIAdapter* m_dxgi_adapter = nullptr;
	IDXGIFactory* m_dxgi_factory = nullptr;
private:
	friend class SwapChain;
private:
	unsigned int m_rtvDescriptorSize; // Размер дескриптора кучи RTV
private:
	SwapChain* m_swap_chain;
};



