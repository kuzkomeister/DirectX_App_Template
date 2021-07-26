#pragma once
#include "Window/WindowContainer.h"
class Engine : WindowContainer
{
public:
	/// <summary>
	/// Инициализация окна
	/// </summary>
	/// <param name="hInstance"> - Дескриптор окна</param>
	/// <param name="window_title"> - Название окна</param>
	/// <param name="window_class"> - Название класса окна</param>
	/// <param name="width"> - Ширина окна</param>
	/// <param name="height"> - Высота окна</param>
	/// <returns>
	/// True - окно успешно создалось,
	/// False - окно не создалось
	/// </returns>
	bool Initialize(HINSTANCE hInstance, 
					std::string window_title, 
					std::string window_class, 
					int width, int height);
	
	/// <summary>
	/// Обработчик приема сообщений от клавиатуры и мыши
	/// </summary>
	/// <returns>
	/// True - Происходит процесс приема сообщений, 
	/// False - Окно было закрыто
	/// </returns>
	bool ProcessMessages();

	/// <summary>
	/// Прием сообщений от клавиатуры
	/// </summary>
	void Update();

	/// <summary>
	/// Функция для рендеринга
	/// </summary>
	void RenderFrame();
};