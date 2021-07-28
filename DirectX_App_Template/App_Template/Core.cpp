#include "Engine.h"

/*
	Существует две точки входа в программу WinMain и wWinMain, разница лишь в том, что WinMain использует ANSII кодировку, а wWinMain Unicode

	nCmdShow принимает следующие значения:
	1. SW_HIDE - Скрывает окно и активизирует другое окно.
	2. SW_MINIMIZE - Минимизирует определенное окно и активизирует окно верхнего уровня в списке системы.
	3. SW_RESTORE - Активизирует и отображает окно. Если окно минимизировано или развернуто, Windows восстанавливает его в первоначальном размере и позиции (то же самое, что и SW_SHOWNORMAL).
	4. SW_SHOW - Активизирует и отображает окно на экране в его текущем размере и позиции.
	5. SW_SHOWMAXIMIZED - Активизирует окно и отображает его как развернутое окно.
	6. SW_SHOWMINIMIZED - Активизирует окно и отображает его как пиктограмму.
	7. SW_SHOWMINNOACTIVE - Отображает окно как пиктограмму. Активное окно остается активным.
	8. SW_SHOWNA - Отображает окно в его текущем состоянии. Активное окно остается активным.
	9. SW_SHOWNOACTIVATE - Отображает окно в его самых последних размерах и позиции. Активное окно остается активным.
	10. SW_SHOWNORMAL - Активизирует и отображает окно. Если окно минимизировано или развернуто, Windows восстанавливает его в первоначальный размер и позицию (то же самое, что и SW_RESTORE).

	Источники по WinMain:
	1. https://firststeps.ru/mfc/winapi/win/r.php?103
	2. https://docs.microsoft.com/ru-ru/windows/win32/learnwin32/winmain--the-application-entry-point
*/

/// <summary>
/// Точка входа в программу
/// </summary>
/// <param name="hInstance"> - Дескриптор текущего экземпляра окна</param>
/// <param name="hPrevInstance"> - Дескриптор предыдущего экземпляра окна (всегда NULL, если нужно то использовать mutex)</param>
/// <param name="lpCmdLine"> - Аргументы командной строки в виде Unicode строки, потому что wWinMain</param>
/// <param name="nCmdShow"> - Флаг, как должно отображаться окно</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR lpCmdLine,
						_In_ int nCmdShow)
{
	/*
		CoInitialize - инициализация библиотеки COM в текущем потоке и определяет модель параллелизма, как однопоточный
		Источник по CoInitialize:
		1. https://docs.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize

		Источник по HRESULT:
		1.
		HRESULT - 32-битное значение описывающее ошибку или предупреждение.
			1-битный код. "S" Бит высокого порядка, указывающий на успешность выполнения (ошибка/не ошибка).
			4-битный код, зарезервированны. "R", "C", "N", "r".
			11-битный код. "Facility" указывает на ответственность за ошибку или предупреждение, также известный как код объекта.
			16-битный код. "Code" уникальный номер, который описывает ошибку или предупреждение.
	*/
	HRESULT hr = CoInitialize(NULL);
	
	/*
	* Проверка на успешность выполнения инициализации COM библиотеки. 
	*/
	if (FAILED(hr))
	{
		/*
		* Если не удалось инициализировать, то выводим в отдельном окне информацию об ошибке.
		* Передаем информацию об ошибке и сообщение об ошибке.
		*/
		ErrorLogger::Log(hr, "Ошибка: Не удалось инициализировать COM библиотеку.");
		/*
		* Завершаем работу приложения
		*/
		return -1;
	}

	Engine engine;
	/*
		Инициализация 
	*/
	if (engine.Initialize(hInstance, "Title", "MyWindowClass", 800, 600))
	{
		/*
			Цикл действует пока окно не закрыто
		*/
		while (engine.ProcessMessages() == true)
		{
			engine.Update();
			engine.RenderFrame();
		}
	}
	return 0;
};