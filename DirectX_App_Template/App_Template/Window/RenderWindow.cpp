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
		0,											// ����������� ����� Windows - �� ���������� ����� �� ���������. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ff700543(v=vs.85).aspx
		this->window_class_wide.c_str(),			// �������� ������ ����
		this->window_title_wide.c_str(),			// �������� ����
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU,	// ����� ����. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms632600(v=vs.85).aspx
		wr.left,									// ���������� ���� � 
		wr.top,										// ���������� ���� Y
		wr.right - wr.left,							// ������ ����
		wr.bottom - wr.top,							// ������ ����
		NULL,										// ���������� ���� ���������� ������
		NULL,										// ���������� ���� ��� �������������� ��������� ����. ����� ���������� NULL � ������������ ���� � WindowClassEx, ���� ���� ���������� ������������
		this->hInstance,							// ���������� ����������
		pWindowContainer);							// ��������� ��� �������� ����

	if (this->handle == NULL)
	{
		ErrorLogger::Log(GetLastError(), L"������ ��� �������� ����: " + StringConverter::StringToWide(this->window_title));
		return false;
	}

	// �������� ���� ������ ���� � ������� ����� �� ���
	ShowWindow(this->handle, SW_SHOW);
	SetForegroundWindow(this->handle);
	SetFocus(this->handle);

	return true;
}

bool RenderWindow::ProcessMessages()
{
	// ���������� ��������� ����
	MSG msg;
	ZeroMemory(&msg, sizeof(MSG)); // ������������� ��������� ���������

	while  (PeekMessage(&msg,	// ��� ������� ��������� (���� ����). ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
			this->handle,		// ���������� ���� 
			0,					// ����������� �������� �������. � ������ ������ �� ����������� (����� ������������, ��������, ��� ��������� ������ ��������� �� ����)
			0,					// ������������ �������� ������
			PM_REMOVE))			// ������� ����� ������� ����� PeekMessage. ��� ��������� �������������� ���������� ���������. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644943(v=vs.85).aspx
	{
		TranslateMessage(&msg); // �������������� �� ���������� ������-��������� � ����������, ����� ����� �� ����������. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644955(v=vs.85).aspx
		DispatchMessage(&msg);	// ��������� ��������� � ��� WindowProc ��� ����� ����. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms644934(v=vs.85).aspx
	}

	// ������� ����, ���� ��� �������� �������
	if (msg.message == WM_NULL)
	{
		if (!IsWindow(this->handle))
		{
			this->handle = NULL; // ���� ��������� ��������� ��������� �� ����������� ����� ����
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
	WNDCLASSEX wc;										//����� ���� (������ ���� �������� ����� ��������� ����). ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ms633577(v=vs.85).aspx
	wc.style = CS_HREDRAW | CS_VREDRAW | CS_OWNDC;		//����� [�������������� ��� ��������� ������ | ������ | �����������]. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/ff729176(v=vs.85).aspx
	wc.lpfnWndProc = HandleMessageSetup;				// ��������� �� ������� WindowProc ��� ��������� ��������� ����� ����
	wc.cbClsExtra = 0;									//# �������������� �����, ������� ���������� �������� � ������������ � ������� ����
	wc.cbWndExtra = 0;									//# �������������� ����� ����� ��������� ����
	wc.hInstance = this->hInstance;						// ���������� ���������, ���������� ��������� ����
	wc.hIcon = NULL;									// ���������� ������ ������ ������. ������ ���� ������ ������, ���� �����
	wc.hIconSm = NULL;									// ���������� ������ ���������, ���� �����
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);			// ����������� ������ - ���� 1 - NULL, �� ����� ���� ��������� ����� �������, ����� �� ������ � ����
	wc.hbrBackground = NULL;							// ���������� ������ ������� ����� ��� ����� ���� ����, ���� �����, � ����� ������� ��� ������. ���������: https://msdn.microsoft.com/en-us/library/windows/desktop/dd144925(v=vs.85).aspx
	wc.lpszMenuName = NULL;								// ��������� �� NULL �������� ������ ������ ����
	wc.lpszClassName = this->window_class_wide.c_str(); //
	wc.cbSize = sizeof(WNDCLASSEX);						// ���������� ��������� ������ ��� ����� ��������� cbSize
	RegisterClassEx(&wc);								// ����������� ���� ��� �������������
}

HWND RenderWindow::GetHWND() const
{
	return this->handle;
}