#pragma once
#include "../ErrorLogger.h"

class WindowContainer;

/// <summary>
/// Класс рендеринга окна
/// </summary>
class RenderWindow
{
public:
	/// <summary>
	/// Инициализация
	/// </summary>
	/// <param name="pWindowContainer"> - Указатель на контейнер окна</param>
	/// <param name="hInstance"> - Дескриптор окна</param>
	/// <param name="window_title"> - Название окна</param>
	/// <param name="window_class"> - Название класса окна</param>
	/// <param name="width"> - Ширина окна</param>
	/// <param name="height"> - Высота окна</param>
	/// <returns>
	/// True  - Окно создалось, 
	/// False - Окно не создалось
	/// </returns>
	bool Initialize(WindowContainer* pWindowContainer,
					HINSTANCE hInstance,		
					std::string window_title, 
					std::string window_class, 
					int width, int height);

	/// <summary>
	/// Обработчик приема сообщений от клавиатуры и мыши
	/// </summary>
	/// <returns>
	/// True  -	Окно доступно, 
	/// False - Окно было закрыто
	/// </returns>
	bool ProcessMessages();		

	/// <summary>
	/// Получить дескриптор окна
	/// </summary>
	/// <returns>Дескриптор окна</returns>
	HWND GetHWND() const;

	/// <summary>
	/// Деструктор
	/// </summary>
	~RenderWindow();							

private:
	void RegisterWindowClass();				// Регистрация окна

	HWND handle = NULL;						// Дескриптор окна
	HINSTANCE hInstance = NULL;				// Дескриптор приложения
	std::string window_title = "";			// Название окна
	std::wstring window_title_wide = L"";	// Название окна в Unicode
	std::string window_class = "";			// Название класса окна
	std::wstring window_class_wide = L"";	// Название класса окна в Unicode
	int width = 0;							// Ширина окна
	int height = 0;							// Высота окна
};