#pragma once
#include <d3d12.h>
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
	static GraphicEngine* get();

private:
	ID3D12Device* m_d3d_device;
	D3D_FEATURE_LEVEL m_feature_level;
	ID3D12CommandQueue* m_d3d_command_queue = nullptr;
};

