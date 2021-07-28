#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer,
							  HINSTANCE hInstance, 
							  std::string window_title, 
							  std::string window_class, 
							  int width, int height)
{
	// Присвоение значений в соответствующие поля
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class); 

	// Вызов регистрации окна
	this->RegisterWindowClass();

	int centerScreenX = GetSystemMetrics(SM_CXSCREEN) / 2 - this->width / 2;
	int centerScreenY = GetSystemMetrics(SM_CYSCREEN) / 2 - this->height / 2;

	RECT wr; //Widow Rectangle
	wr.left = centerScreenX;
	wr.top = centerScreenY;
	wr.right = wr.left + this->width;
	wr.bottom = wr.top + this->height;
	AdjustWindowRect(&wr, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, FALSE);

	this->handle = CreateWindowEx(
		0,											// Расширенный стиль Windows - мы используем стиль по умолчанию. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
		this->window_class_wide.c_str(),			// Название класса окна
		this->window_title_wide.c_str(),			// Название окна
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,	// Стиль окна. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
		wr.left,									// координата окна Х 
		wr.top,										// координата окна Y
		wr.right - wr.left,							// ширина окна
		wr.bottom - wr.top,							// высота окна
		NULL,										// Дескриптор окна вызвавшего данное
		NULL,										// Дескриптор меню или идентификатора дочернего окна. Можно установить NULL и использовать меню в WindowClassEx, если меню желательно использовать
		this->hInstance,							// Дескриптор приложения
		pWindowContainer);							// Параметры для создания окна

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), L"Ошибка при создании окна: " + StringConverter::StringToWide(this->window_title));
		return false;
	}

	// Показать окно поверх всех и сделать фокус на нем
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	// дескриптор сообщений окна
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // инициализация структуры сообщения

	while  (PeekMessage(&msg,	// Где хранить сообщения (если есть). Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
			this->handle,		// дескриптор окна 
			0,					// Минимальное значение фильтра. В данном случае не фильтруется (можно использовать, например, для обработки только сообщений от мыши)
			0,					// Максимальное значение фильта
			PM_REMOVE))			// Удалить после захвата через PeekMessage. Для получения дополнительных параметров аргумента. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
	{
		TranslateMessage(&msg); // Преобразование из виртульных ключей-сообщений в символьные, чтобы могли их отправлять. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
		DispatchMessage(&msg);	// Отправить сообщение в наш WindowProc для этого окна. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644934(v=vs.85).aspx
	}

	// Закрыть окно, если оно визульно закрыто
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL; // Цикл обработки сообщений заботится об уничтожении этого окна
			UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
			return false;
		}
	}

	return true;
}

RenderWindow::~RenderWindow()
{
	if (this->handle != NULL)
	{
		UnregisterClass(this->window_class_wide.c_str(), this->hInstance);
		DestroyWindow(handle);
	}
}

LRESULT CALLBACK HandleMsgRedirect(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
			// All other messages
		case WM_CLOSE:
			DestroyWindow(hwnd);
			return 0;

		default:
		{
			// retrieve ptr to window class
			WindowContainer* const pWindow = reinterpret_cast<WindowContainer*>(GetWindowLongPtr(hwnd, GWLP_USERDATA));
			// forward message to window class handler
			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
	}
}

LRESULT CALLBACK HandleMessageSetup(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg)
	{
		/*
		* WM_NCCREATE - сообщение приходящее перед созданием окна
		*/
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) 
			{
				ErrorLogger::Log("Критическая ошибка: указатель на WindowContainer пуст в WM_NCCREATE.");
				exit(-1);
			}
			SetWindowLongPtr(hwnd, GWLP_USERDATA, reinterpret_cast<LONG_PTR>(pWindow));
			SetWindowLongPtr(hwnd, GWLP_WNDPROC, reinterpret_cast<LONG_PTR>(HandleMsgRedirect));
			return pWindow->WindowProc(hwnd, uMsg, wParam, lParam);
		}
		default:
			return DefWindowProc(hwnd, uMsg, wParam, lParam);
	}
}

void RenderWindow::RegisterWindowClass()
{
	/*
	* Структура WNDCLASSEX содержит информацию о классе окна необходимую для регистрации окна
	* 
	* style       - Стили определяют дополнительные элементы класса окна. Стили можно объединить с помощью '|'
	*	Список стилей: http://www.vsokovikov.narod.ru/New_MSDN_API/Win_class/class_styles.htm
	* lpfnWndProc - Указатель на оконную процедуру WindowProc
	* cbClsExtra  - Число дополнительных байтов, которые размещаются вслед за структурой класса окна. Система инициализирует эти байты нулями
	* cbWndExtra  - Число дополнительных байтов, которые размещаются вслед за экземпляром окна. Система инициализирует эти байты нулями
	* hInstance   - Дескриптор экземпляра, который содержит оконную процедуру для класса
	* hIcon       - Дескриптор значка класса. Этот член структуры должен быть дескриптором ресурса значка
	* hIconSm	  - Дескриптор маленького значка, который связан с классом окна
	* hCursor	  - Дескриптор курсора класса. Этот член структуры должен быть дескриптором ресурса курсора. 
	*	Если этот член структуры - ПУСТО (NULL), приложение должно явно устанавливать форму курсора всякий раз, когда мышь перемещается в окно прикладной программы
	* hbrBackground - Дескриптор кисти фона класса. Этот член структуры может быть дескриптором физической кисти, которая используется, чтобы красить цветом фона, 
	*	или это может быть кодом цвета. Код цвета должен быть одним из ниже перечисленных стандартных системных цветов (значение 1 должно добавляться к выбранному цвету). 
	*	Если дается код цвета, Вы должны преобразовать его в один из ниже перечисленных типов HBRUSH: http://www.vsokovikov.narod.ru/New_MSDN_API/Win_class/str_wndclassex.htm
	* lpszMenuName  - Указатель на символьную строку с символом конца строки ('\0'), которая устанавливает имя ресурса меню класса, которое как имя показывается в файле ресурса
	* lpszClassName - Символьная строка, она задает имя класса окна. Имя класса может быть любым именем, зарегистрированным функцией RegisterClass или RegisterClassEx 
	* cbSize		- Размер структуры в байтах
	*/
	WNDCLASSEX wc;										// Класс окна (должен быть заполнен перед созданием окна). Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;		// уникальный контекст устройства для каждого окна в классе | перерисовать окно при изменении ширины или перемещении | -//- высоты -//-
	wc.lpfnWndProc = HandleMessageSetup;				// указатель на функцию, которая передаст указатель на наш WindowProc
	wc.cbClsExtra = 0;									// не нужны дополнительные байты
	wc.cbWndExtra = 0;									// не нужны дополнительные байты
	wc.hInstance = this->hInstance;						// дескриптор программы
	wc.hIcon = NULL;									// значок по умолчанию
	wc.hIconSm = NULL;									// значок по умолчанию
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// курсор по умолчанию
	wc.hbrBackground = NULL;							// дескриптор класса фоновой кисти для цвета фона окна
	wc.lpszMenuName = NULL;								// указатель на названия меню класса 
	wc.lpszClassName = this->window_class_wide.c_str(); // имя названия класса окна
	wc.cbSize = sizeof(WNDCLASSEX);						// размер структуры

	RegisterClassEx(&wc);								// Регистрация окна для использования
}

HWND RenderWindow::GetHWND() const
{
	return this->handle;
}