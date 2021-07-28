#pragma once
#include "RenderWindow.h"
#include "../Keyboard/KeyboardClass.h"
#include "../Mouse/MouseClass.h"
#include "../Graphics/Graphics.h"

/// <summary>
/// ����� ��� ������ � �����
/// </summary>
class WindowContainer
{
public:
	/// <summary>
	/// ����������� ������
	/// </summary>
	WindowContainer();

	/*
	* � WPARAM � LPARAM, W - ������ 16-������ WORD, L - ������ 32-������ LONG 
	*/

	/// <summary>
	/// ����� ��������� ���������, ������������ � ����
	/// </summary>
	/// <param name="hwnd"> - ���������� ������� ���������, ������� �������� ���������</param>
	/// <param name="uMsg"> - ���������� ���������</param>
	/// <param name="wParam"> - ���������� �������������� ���������� � ���������. ���������� ������� �� ������������� ���������</param>
	/// <param name="lParam"> - ���������� �������������� ���������� � ���������. ���������� ������� �� ������������� ���������</param>
	/// <returns>32-������ ��������� ��������� ���������</returns>
	LRESULT WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam);

protected:
	RenderWindow render_window;		// 
	KeyboardClass keyboard;			// ����� ����������
	MouseClass mouse;				// ����� ����
	Graphics gfx;					//
private:

};