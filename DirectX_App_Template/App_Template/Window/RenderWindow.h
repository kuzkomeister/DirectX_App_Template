#pragma once
#include "../ErrorLogger.h"

class WindowContainer;

/// <summary>
/// ����� ���������� ����
/// </summary>
class RenderWindow
{
public:
	/// <summary>
	/// �������������
	/// </summary>
	/// <param name="pWindowContainer"> - ��������� �� ��������� ����</param>
	/// <param name="hInstance"> - ���������� ����</param>
	/// <param name="window_title"> - �������� ����</param>
	/// <param name="window_class"> - �������� ������ ����</param>
	/// <param name="width"> - ������ ����</param>
	/// <param name="height"> - ������ ����</param>
	/// <returns>
	/// True  - ���� ���������, 
	/// False - ���� �� ���������
	/// </returns>
	bool Initialize(WindowContainer* pWindowContainer,
					HINSTANCE hInstance,		
					std::string window_title, 
					std::string window_class, 
					int width, int height);

	/// <summary>
	/// ���������� ������ ��������� �� ���������� � ����
	/// </summary>
	/// <returns>
	/// True  -	���� ��������, 
	/// False - ���� ���� �������
	/// </returns>
	bool ProcessMessages();		

	/// <summary>
	/// �������� ���������� ����
	/// </summary>
	/// <returns>���������� ����</returns>
	HWND GetHWND() const;

	/// <summary>
	/// ����������
	/// </summary>
	~RenderWindow();							

private:
	void RegisterWindowClass();				// ����������� ����

	HWND handle = NULL;						// ���������� ����
	HINSTANCE hInstance = NULL;				// ���������� ����������
	std::string window_title = "";			// �������� ����
	std::wstring window_title_wide = L"";	// �������� ���� � Unicode
	std::string window_class = "";			// �������� ������ ����
	std::wstring window_class_wide = L"";	// �������� ������ ���� � Unicode
	int width = 0;							// ������ ����
	int height = 0;							// ������ ����
};