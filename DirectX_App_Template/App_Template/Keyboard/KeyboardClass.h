#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
public:
	KeyboardClass();
	
	/// <summary>
	/// Нажата ли клавиша с кодом
	/// </summary>
	/// <param name="keycode"> - Код клавиши</param>
	/// <returns>
	/// True - нажата клавиша,
	/// False - не нажата 
	/// </returns>
	bool KeyIsPressed(const unsigned char keycode);

	/// <summary>
	/// Пуст ли буфер событий
	/// </summary>
	/// <returns>
	/// True - буфер пуст,
	/// False - буфер не пуст
	/// </returns>
	bool KeyBufferIsEmpty();

	/// <summary>
	/// Пуст ли буфер символов
	/// </summary>
	/// <returns>
	/// True - буфер пуст,
	/// False - буфер не пуст
	/// </returns>
	bool CharBufferIsEmpty();

	/// <summary>
	/// Считать событие клавиатуры из буфера событий клавиатуры
	/// </summary>
	/// <returns></returns>
	KeyboardEvent ReadKey();

	/// <summary>
	/// Считать код из буфера кодов клавиатуры
	/// </summary>
	/// <returns></returns>
	unsigned char ReadChar();

	/// <summary>
	/// Нажать клавишу
	/// </summary>
	/// <param name="key"> - Код нажатой клавиши</param>
	void OnKeyPressed(const unsigned char key);

	/// <summary>
	/// Отпустить клавишу
	/// </summary>
	/// <param name="key"> - Код отпущенной клавиши</param>
	void OnKeyReleased(const unsigned char key);

	void OnChar(const unsigned char key);

	/// <summary>
	/// Включить автоматическое повторение сеанса ключей
	/// </summary>
	void EnableAutoRepeatKeys();

	/// <summary>
	/// Выключить автоматическое повторение сеанса ключей
	/// </summary>
	void DisableAutoRepeatKeys();


	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
private:
	bool autoRepeatKeys = false;				// Автоповтор событий клавиатуры
	bool autoRepeatChars = false;				// Автоповтор кодов клавиатуры
	bool keyStates[256];						// Состояния клавиш клавиатуры (Нажата/Отпущена -> True/False)
	std::queue<KeyboardEvent> keyBuffer;		// Буфер событий клавиатуры
	std::queue<unsigned char> charBuffer;		// Буфер кодов клавиатуры
};