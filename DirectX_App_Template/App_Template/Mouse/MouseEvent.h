#pragma once
struct MousePoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPress,			// ЛКМ нажата 
		LRelease,		// ЛКМ отпущена
		RPress,			// ПКМ нажата
		RRelease,		// ПКМ отпущена
		MPress,			// Колесико нажато
		MRelease,		// Колесико отпущено
		WheelUp,		// Прокрутка колесика вверх
		WheelDown,		// Прокрутка колесика вниз
		Move,			// Перемещение мыши
		RAW_MOVE,		// Необработанное движение ввода
		Invalid			// Недействительное 
	};
private:
	EventType type;
	int x;
	int y;
public:
	/// <summary>
	/// Генерация недействительного события
	/// </summary>
	MouseEvent();

	/// <summary>
	/// Генерация события
	/// </summary>
	/// <param name="type"> - Тип события</param>
	/// <param name="x"> - Координата Х</param>
	/// <param name="y"> - Координата Y</param>
	MouseEvent(const EventType type, const int x, const int y);

	/// <summary>
	/// Статус корректности типа события
	/// </summary>
	/// <returns>
	/// True - Если не является недействительным,
	/// False - Если является недействительным
	/// </returns>
	bool IsValid() const;

	/// <summary>
	/// Получить тип события
	/// </summary>
	/// <returns></returns>
	EventType GetType() const;

	/// <summary>
	/// Получить местоположение мыши
	/// </summary>
	/// <returns></returns>
	MousePoint GetPos() const;


	int GetPosX() const;
	int GetPosY() const;
};