#include "WindowContainer.h"

bool RenderWindow::Initialize(WindowContainer* pWindowContainer,
							  HINSTANCE hInstance, 
							  std::string window_title, 
							  std::string window_class, 
							  int width, int height)
{
	this->hInstance = hInstance;
	this->width = width;
	this->height = height;
	this->window_title = window_title;
	this->window_title_wide = StringConverter::StringToWide(this->window_title);
	this->window_class = window_class;
	this->window_class_wide = StringConverter::StringToWide(this->window_class); 

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
		case WM_NCCREATE:
		{
			const CREATESTRUCTW* const pCreate = reinterpret_cast<CREATESTRUCTW*>(lParam);
			WindowContainer* pWindow = reinterpret_cast<WindowContainer*>(pCreate->lpCreateParams);
			if (pWindow == nullptr) //Sanity check
			{
				ErrorLogger::Log("Critical Error: Pointer to window container is null during WM_NCCREATE.");
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
	WNDCLASSEX wc;										//Класс окна (должен быть заполнен перед созданием окна). Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		//Флаги [Перерисовывать при изменении ширины | высоты | перемещении]. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc = HandleMessageSetup;				// Указатель на функцию WindowProc для обработки сообщений этого окна
	wc.cbClsExtra = 0;									//# дополнительные байты, которые необходимо выделить в соответствии с классом окна
	wc.cbWndExtra = 0;									//# дополнительные байты после выделения окна
	wc.hInstance = this->hInstance;						// Дескриптор программы, содержащий процедуру окна
	wc.hIcon = NULL;									// Дескриптор значка класса иконки. Должен быть ресурс иконки, пока пусто
	wc.hIconSm = NULL;									// Дескриптор значка программы, пока пусто
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// Стандартный курсор - если 1 - NULL, то нужно явно указывать форму курсора, когда он входит в окно
	wc.hbrBackground = NULL;							// Дескриптор класса фоновой кисти для цвета фона окна, пока пусто, а позже сделаем его черным. Подробнее: https://msdn.microsoft.com/en-us/library/windows/desktop/dd144925(v=vs.85).aspx
	wc.lpszMenuName = NULL;								// Указатель на NULL названия класса нашего окна
	wc.lpszClassName = this->window_class_wide.c_str(); //
	wc.cbSize = sizeof(WNDCLASSEX);						// Необходимо заполнить размер для нашей структуры cbSize
	RegisterClassEx(&wc);								// Регистрация окна для использования
}

HWND RenderWindow::GetHWND() const
{
	return this->handle;
}