#pragma once
#include "StringConverter.h"
#include <Windows.h>
class ErrorLogger
{
public:
	/// <summary>
	/// Вывод информации об ошибке со строкой
	/// </summary>
	/// <param name="message">Сообщение об ошибке</param>
	static void Log(std::string message);
	/// <summary>
	/// Вывод информации об ошибке со строкой и результатом
	/// </summary>
	/// <param name="hr">Информация об ошибке</param>
	/// <param name="message">Сообщение об ошибке</param>
	static void Log(HRESULT hr, std::string message);
	/// <summary>
	/// Вывод информации об ошибке с широкой строкой и результатом
	/// </summary>
	/// <param name="hr">Информация об ошибке</param>
	/// <param name="message">Сообщение об ошибке</param>
	static void Log(HRESULT hr, std::wstring message);	
};
