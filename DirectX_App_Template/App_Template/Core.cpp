#include "Engine.h"

/*
	���������� ��� ����� ����� � ��������� WinMain � wWinMain, ������� ���� � ���, ��� WinMain ���������� ANSII ���������, � wWinMain Unicode

	nCmdShow ��������� ��������� ��������:
	1. SW_HIDE - �������� ���� � ������������ ������ ����.
	2. SW_MINIMIZE - ������������ ������������ ���� � ������������ ���� �������� ������ � ������ �������.
	3. SW_RESTORE - ������������ � ���������� ����. ���� ���� �������������� ��� ����������, Windows ��������������� ��� � �������������� ������� � ������� (�� �� �����, ��� � SW_SHOWNORMAL).
	4. SW_SHOW - ������������ � ���������� ���� �� ������ � ��� ������� ������� � �������.
	5. SW_SHOWMAXIMIZED - ������������ ���� � ���������� ��� ��� ����������� ����.
	6. SW_SHOWMINIMIZED - ������������ ���� � ���������� ��� ��� �����������.
	7. SW_SHOWMINNOACTIVE - ���������� ���� ��� �����������. �������� ���� �������� ��������.
	8. SW_SHOWNA - ���������� ���� � ��� ������� ���������. �������� ���� �������� ��������.
	9. SW_SHOWNOACTIVATE - ���������� ���� � ��� ����� ��������� �������� � �������. �������� ���� �������� ��������.
	10. SW_SHOWNORMAL - ������������ � ���������� ����. ���� ���� �������������� ��� ����������, Windows ��������������� ��� � �������������� ������ � ������� (�� �� �����, ��� � SW_RESTORE).

	��������� �� WinMain:
	1. https://firststeps.ru/mfc/winapi/win/r.php?103
	2. https://docs.microsoft.com/ru-ru/windows/win32/learnwin32/winmain--the-application-entry-point
*/

/// <summary>
/// ����� ����� � ���������
/// </summary>
/// <param name="hInstance"> - ���������� �������� ���������� ����</param>
/// <param name="hPrevInstance"> - ���������� ����������� ���������� ���� (������ NULL, ���� ����� �� ������������ mutex)</param>
/// <param name="lpCmdLine"> - ��������� ��������� ������ � ���� Unicode ������, ������ ��� wWinMain</param>
/// <param name="nCmdShow"> - ����, ��� ������ ������������ ����</param>
/// <returns></returns>
int APIENTRY wWinMain(_In_ HINSTANCE hInstance,
						_In_opt_ HINSTANCE hPrevInstance,
						_In_ LPWSTR lpCmdLine,
						_In_ int nCmdShow)
{
	/*
		CoInitialize - ������������� ���������� COM � ������� ������ � ���������� ������ ������������, ��� ������������
		�������� �� CoInitialize:
		1. https://docs.microsoft.com/en-us/windows/win32/api/objbase/nf-objbase-coinitialize

		�������� �� HRESULT:
		1.
		HRESULT - 32-������ �������� ����������� ������ ��� ��������������.
			1-������ ���. "S" ��� �������� �������, ����������� �� ���������� ���������� (������/�� ������).
			4-������ ���, ����������������. "R", "C", "N", "r".
			11-������ ���. "Facility" ��������� �� ��������������� �� ������ ��� ��������������, ����� ��������� ��� ��� �������.
			16-������ ���. "Code" ���������� �����, ������� ��������� ������ ��� ��������������.
	*/
	HRESULT hr = CoInitialize(NULL);
	
	/*
	* �������� �� ���������� ���������� ������������� COM ����������. 
	*/
	if (FAILED(hr))
	{
		/*
		* ���� �� ������� ����������������, �� ������� � ��������� ���� ���������� �� ������.
		* �������� ���������� �� ������ � ��������� �� ������.
		*/
		ErrorLogger::Log(hr, "������: �� ������� ���������������� COM ����������.");
		/*
		* ��������� ������ ����������
		*/
		return -1;
	}

	Engine engine;
	/*
		������������� 
	*/
	if (engine.Initialize(hInstance, "Title", "MyWindowClass", 800, 600))
	{
		/*
			���� ��������� ���� ���� �� �������
		*/
		while (engine.ProcessMessages() == true)
		{
			engine.Update();
			engine.RenderFrame();
		}
	}
	return 0;
};