#pragma once
#include "StringConverter.h"
#include <Windows.h>
class ErrorLogger
{
public:
	/// <summary>
	/// ����� ���������� �� ������ �� �������
	/// </summary>
	/// <param name="message">��������� �� ������</param>
	static void Log(std::string message);
	/// <summary>
	/// ����� ���������� �� ������ �� ������� � �����������
	/// </summary>
	/// <param name="hr">���������� �� ������</param>
	/// <param name="message">��������� �� ������</param>
	static void Log(HRESULT hr, std::string message);
	/// <summary>
	/// ����� ���������� �� ������ � ������� ������� � �����������
	/// </summary>
	/// <param name="hr">���������� �� ������</param>
	/// <param name="message">��������� �� ������</param>
	static void Log(HRESULT hr, std::wstring message);	
};
