#include "KeyboardClass.h"

KeyboardClass::KeyboardClass()
{
	for (int i = 0; i < 256; i++)
		this->keyStates[i] = false; // Заполняем статусы клавиш как нетронутые
}

bool KeyboardClass::KeyIsPressed(const unsigned char keycode)
{
	return this->keyStates[keycode];
}

bool KeyboardClass::KeyBufferIsEmpty()
{
	return this->keyBuffer.empty();
}

bool KeyboardClass::CharBufferIsEmpty()
{
	return this->charBuffer.empty();
}

KeyboardEvent KeyboardClass::ReadKey()
{
	if (this->keyBuffer.empty())	// Проверка на наличие событий для считывания
	{
		return KeyboardEvent();			// Возвращаем пустое событие (Недействительное)
	}
	else
	{
		KeyboardEvent e = this->keyBuffer.front();	// Получаем первое событие из буфера
		this->keyBuffer.pop();						// Удаляем это событие из буфера
		return e;									// Возвращаем это событие
	}
}

unsigned char KeyboardClass::ReadChar()
{
	if (this->charBuffer.empty())	// Проверка на наличие кодов для считывания
	{
		return 0u;						// Возвращаем NULL char
	}
	else
	{
		unsigned char e = this->charBuffer.front();	// Получаем первый код из буфера
		this->charBuffer.pop();						// Удаляем этот код из буфера
		return e;									// Возвращаем этот код
	}
}

void KeyboardClass::OnKeyPressed(const unsigned char key)
{
	this->keyStates[key] = true;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Press, key));
}

void KeyboardClass::OnKeyReleased(const unsigned char key)
{
	this->keyStates[key] = false;
	this->keyBuffer.push(KeyboardEvent(KeyboardEvent::EventType::Release, key));
}

void KeyboardClass::OnChar(const unsigned char key)
{
	this->charBuffer.push(key);
}

void KeyboardClass::EnableAutoRepeatKeys()
{
	this->autoRepeatKeys = true;
}

void KeyboardClass::DisableAutoRepeatKeys()
{
	this->autoRepeatKeys = false;
}

void KeyboardClass::EnableAutoRepeatChars()
{
	this->autoRepeatChars = true;
}

void KeyboardClass::DisableAutoRepeatChars()
{
	this->autoRepeatChars = false;
}

bool KeyboardClass::IsKeysAutoRepeat()
{
	return this->autoRepeatKeys;
}

bool KeyboardClass::IsCharsAutoRepeat()
{
	return this->autoRepeatChars;
}