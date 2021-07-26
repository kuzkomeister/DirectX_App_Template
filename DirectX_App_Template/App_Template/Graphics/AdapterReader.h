#pragma once
#include "..\\ErrorLogger.h"
#include <d3d11.h>
#pragma comment(lib,"d3d11.lib")
#pragma comment(lib,"DirectXTK.lib")
#pragma comment(lib,"DXGI.lib")
#include <wrl/client.h>
#include <vector> 

class AdapterData
{
public:
	/// <summary>
	/// ����������� AdapterData
	/// </summary>
	/// <param name="pAdapter"> - ��������� �� �������</param>
	AdapterData(IDXGIAdapter* pAdapter);	
	IDXGIAdapter* pAdapter = nullptr;		// ��������� �� ����������
	DXGI_ADAPTER_DESC description;			// 
};

class AdapterReader
{
public:
	/// <summary>
	/// �������� ������ ���������
	/// </summary>
	/// <returns>������ ���������</returns>
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> adapters;		// ������ ���������
};