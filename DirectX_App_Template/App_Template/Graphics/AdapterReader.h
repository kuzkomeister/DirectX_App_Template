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
	/// Конструктор AdapterData
	/// </summary>
	/// <param name="pAdapter"> - Указатель на адаптер</param>
	AdapterData(IDXGIAdapter* pAdapter);	
	IDXGIAdapter* pAdapter = nullptr;		// Указатель на устройство
	DXGI_ADAPTER_DESC description;			// 
};

class AdapterReader
{
public:
	/// <summary>
	/// Получить вектор адаптеров
	/// </summary>
	/// <returns>вектор адаптеров</returns>
	static std::vector<AdapterData> GetAdapters();
private:
	static std::vector<AdapterData> adapters;		// Вектор адаптеров
};