#include "AdapterReader.h"

std::vector<AdapterData> AdapterReader::adapters;	// Инициализируем статическое поле

std::vector<AdapterData> AdapterReader::GetAdapters()
{
	if (adapters.size() > 0) // Если адаптеры уже инициализированы
		return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;

	// Создаем объект DXGIFactory
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Ошибка при создании DXGIFactory для нумерации адаптеров.");
		exit(-1);
	}

	// Заполняем вектор с адаптерами
	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter)))
	{
		adapters.push_back(AdapterData(pAdapter));
		index += 1;
	}

	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* pAdapter)
{
	this->pAdapter = pAdapter;
	HRESULT hr = pAdapter->GetDesc(&this->description);
	if (FAILED(hr))
	{
		ErrorLogger::Log(hr, "Ошибка при получении описания для IDXGIAdapter.");
	}
}