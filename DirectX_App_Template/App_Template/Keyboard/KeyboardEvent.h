#pragma once

class KeyboardEvent
{
public:
	enum EventType
	{
		Press,		// Нажато
		Release,	// Отпущено
		Invalid		// Недействительно
	};

	/// <summary>
	/// Генерация недействительного события
	/// </summary>
	KeyboardEvent();				

	/// <summary>
	/// Генерация события
	/// </summary>
	/// <param name="type"> - Тип события</param>
	/// <param name="key"> - Связанная с событием клавиша</param>
	KeyboardEvent(const EventType type, const unsigned char key);
	
	/// <summary>
	/// Событие-нажатия клавиши
	/// </summary>
	/// <returns>
	/// True - Было нажато,
	/// False - Не было нажато
	/// </returns>
	bool IsPress() const;

	/// <summary>
	/// Событие-отпущения клавиши
	/// </summary>
	/// <returns>
	/// True - Было отпущено,
	/// False - Не было отпущено
	/// </returns>
	bool IsRelease() const;

	/// <summary>
	/// Статус корректности типа события
	/// </summary>
	/// <returns>
	/// True - Если тип не является недействительным,
	/// False - Если тип недействителен
	/// </returns>
	bool IsValid() const;

	/// <summary>
	/// Получить код клавиши
	/// </summary>
	/// <returns>Код клавиши</returns>
	unsigned char GetKeyCode() const;

private:
	EventType type;		// Тип события
	unsigned char key;	// Код клавиши
};