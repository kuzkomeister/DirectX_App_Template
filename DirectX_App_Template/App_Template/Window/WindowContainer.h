#pragma once
#include "RenderWindow.h"
#include "../Keyboard/KeyboardClass.h"
#include "../Mouse/MouseClass.h"
#include "../Graphics/Graphics.h"

/// <summary>
/// Класс для работы с окном
/// </summary>
class WindowContainer
{
public:
	/// <summary>
	/// Конструктор класса
	/// </summary>
	WindowContainer();

	/*
	* В WPARAM и LPARAM, W - значит 16-битный WORD, L - значит 32-битный LONG 
	*/

	/// <summary>
	/// Метод обработки сообщений, отправленных в окно
	/// </summary>
	/// <param name="hwnd"> - Дескриптор оконной процедуры, которая получает сообщение</param>
	/// <param name="uMsg"> - Определяет сообщение</param>
	/// <param name="wParam"> - Определяет дополнительную информацию о сообщении. Содержание зависит от передаваемого сообщения</param>
	/// <param name="lParam"> - Определяет дополнительную информацию о сообщении. Содержание зависит от передаваемого сообщения</param>
	/// <returns>32-битный результат обработки сообщения</returns>
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	RenderWindow render_window;		// 
	KeyboardClass keyboard;			// Класс клавиатуры
	MouseClass mouse;				// Класс мыши
	Graphics gfx;					//
private:

};