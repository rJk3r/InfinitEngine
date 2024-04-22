#include "GraphicEngine.h"

GraphicEngine::GraphicEngine()
{
	// Initialize any members if necessary
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

	for (UINT driver_type_index = 0; driver_type_index < num_driver_types;)
	{
		HRESULT res=D3D12CreateDevice(nullptr, D3D_FEATURE_LEVEL_11_0, IID_PPV_ARGS(&m_d3d_device));
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

	return true;
}

bool GraphicEngine::release()
{
	m_d3d_device->Release();
	return true;
}

GraphicEngine::~GraphicEngine()
{
}

GraphicEngine* GraphicEngine::get()
{
	static GraphicEngine engine;
	return &engine;
}
