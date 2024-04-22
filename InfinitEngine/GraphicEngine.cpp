#include "GraphicEngine.h"
#include "SwapChain.h"
#include "d3dx12.h"
#include <d3d12.h>

GraphicEngine::GraphicEngine()
{
	// Initialize any members if necessary
	m_d3d_device = nullptr;
	m_dxgi_device = nullptr;
	m_dxgi_adapter = nullptr;
	m_dxgi_factory = nullptr;
	m_d3d_command_queue = nullptr;
	m_command_allocator = nullptr;
	m_command_list = nullptr;
}

bool GraphicEngine::init()
{
	D3D_DRIVER_TYPE driver_types[] =
	{
		D3D_DRIVER_TYPE_HARDWARE,
		D3D_DRIVER_TYPE_WARP,
		D3D_DRIVER_TYPE_REFERENCE
	};
	UINT num_driver_types = ARRAYSIZE(driver_types);

	D3D_FEATURE_LEVEL feature_levels[] =
	{
		D3D_FEATURE_LEVEL_11_0
	};
	UINT num_feature_levels = ARRAYSIZE(feature_levels);

	HRESULT res = 0;
	HRESULT hr = 0; // Define hr here

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		res = D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3d_device));
		if (SUCCEEDED(res))
		{
			break;
			++driver_type_index;
			// Handle error
		}
	}

	if (FAILED(res))
	{
		return false;
	}

	// Create the command queue
	D3D12_COMMAND_QUEUE_DESC queueDesc = {};
	queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
	queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
	hr = m_d3d_device->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&m_d3d_command_queue));
	if (FAILED(hr))
	{
		// Handle error
		return false;
	}

	// Create the command allocator
	hr = m_d3d_device->CreateCommandAllocator(D3D12_COMMAND_LIST_TYPE_DIRECT, IID_PPV_ARGS(&m_command_allocator));
	if (FAILED(hr))
	{
		// Handle error
		return false;
	}

	// Create the command list
	hr = m_d3d_device->CreateCommandList(0, D3D12_COMMAND_LIST_TYPE_DIRECT, m_command_allocator, nullptr, IID_PPV_ARGS(&m_command_list));
	if (FAILED(hr))
	{
		// Handle error
		return false;
	}

	// Command lists are created in the recording state. Since there is nothing
	// to record right now and the main loop expects it to be closed, we close it.
	m_command_list->Close();

	hr = m_d3d_device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&m_dxgi_device));
	if (FAILED(hr) || m_dxgi_device == nullptr)
	{
		// Обработка ошибки инициализации
		return false;
	}

	// Получение указателей на родительские объекты
	hr = m_dxgi_device->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&m_dxgi_adapter));
	if (FAILED(hr) || m_dxgi_adapter == nullptr)
	{
		// Обработка ошибки получения указателя на адаптер
		m_dxgi_device->Release(); // Освобождаем интерфейс DXGI устройства
		m_dxgi_device = nullptr; // Устанавливаем указатель на nullptr
		return false;
	}

	hr = m_dxgi_adapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&m_dxgi_factory));
	if (FAILED(hr) || m_dxgi_factory == nullptr)
	{
		// Обработка ошибки получения указателя на фабрику DXGI
		m_dxgi_adapter->Release(); // Освобождаем интерфейс адаптера
		m_dxgi_adapter = nullptr; // Устанавливаем указатель на nullptr
		m_dxgi_device->Release(); // Освобождаем интерфейс DXGI устройства
		m_dxgi_device = nullptr; // Устанавливаем указатель на nullptr
		return false;
	}

	return true;
}

bool GraphicEngine::release()
{
	m_dxgi_device->Release();
	m_dxgi_adapter->Release();
	m_dxgi_factory->Release();

	m_d3d_device->Release();

	return true;
}

GraphicEngine::~GraphicEngine()
{
}

SwapChain* GraphicEngine::createSwapChain()
{
	return new SwapChain();
}

GraphicEngine* GraphicEngine::get()
{
	static GraphicEngine engine;
	return &engine;
}

unsigned int GraphicEngine::getRTVDescriptorSize() const {
	// Ваша реализация метода getRTVDescriptorSize
	return m_rtvDescriptorSize;
}