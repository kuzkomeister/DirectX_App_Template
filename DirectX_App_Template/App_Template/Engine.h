#pragma once
#include "Window/WindowContainer.h"
class Engine : WindowContainer
{
public:
	/// <summary>
	/// ������������� ����
	/// </summary>
	/// <param name="hInstance"> - ���������� ����</param>
	/// <param name="window_title"> - �������� ����</param>
	/// <param name="window_class"> - �������� ������ ����</param>
	/// <param name="width"> - ������ ����</param>
	/// <param name="height"> - ������ ����</param>
	/// <returns>
	/// True - ���� ������� ���������,
	/// False - ���� �� ���������
	/// </returns>
	bool Initialize(HINSTANCE hInstance, 
					std::string window_title, 
					std::string window_class, 
					int width, int height);
	
	/// <summary>
	/// ���������� ������ ��������� �� ���������� � ����
	/// </summary>
	/// <returns>
	/// True - ���������� ������� ������ ���������, 
	/// False - ���� ���� �������
	/// </returns>
	bool ProcessMessages();

	/// <summary>
	/// ����� ��������� �� ����������
	/// </summary>
	void Update();

	/// <summary>
	/// ������� ��� ����������
	/// </summary>
	void RenderFrame();
};