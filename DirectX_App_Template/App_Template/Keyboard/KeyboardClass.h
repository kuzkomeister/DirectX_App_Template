#pragma once
#include "KeyboardEvent.h"
#include <queue>

class KeyboardClass
{
public:
	KeyboardClass();
	
	/// <summary>
	/// ������ �� ������� � �����
	/// </summary>
	/// <param name="keycode"> - ��� �������</param>
	/// <returns>
	/// True - ������ �������,
	/// False - �� ������ 
	/// </returns>
	bool KeyIsPressed(const unsigned char keycode);

	/// <summary>
	/// ���� �� ����� �������
	/// </summary>
	/// <returns>
	/// True - ����� ����,
	/// False - ����� �� ����
	/// </returns>
	bool KeyBufferIsEmpty();

	/// <summary>
	/// ���� �� ����� ��������
	/// </summary>
	/// <returns>
	/// True - ����� ����,
	/// False - ����� �� ����
	/// </returns>
	bool CharBufferIsEmpty();

	/// <summary>
	/// ������� ������� ���������� �� ������ ������� ����������
	/// </summary>
	/// <returns></returns>
	KeyboardEvent ReadKey();

	/// <summary>
	/// ������� ��� �� ������ ����� ����������
	/// </summary>
	/// <returns></returns>
	unsigned char ReadChar();

	/// <summary>
	/// ������ �������
	/// </summary>
	/// <param name="key"> - ��� ������� �������</param>
	void OnKeyPressed(const unsigned char key);

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="key"> - ��� ���������� �������</param>
	void OnKeyReleased(const unsigned char key);

	void OnChar(const unsigned char key);

	/// <summary>
	/// �������� �������������� ���������� ������ ������
	/// </summary>
	void EnableAutoRepeatKeys();

	/// <summary>
	/// ��������� �������������� ���������� ������ ������
	/// </summary>
	void DisableAutoRepeatKeys();


	void EnableAutoRepeatChars();
	void DisableAutoRepeatChars();
	bool IsKeysAutoRepeat();
	bool IsCharsAutoRepeat();
private:
	bool autoRepeatKeys = false;				// ���������� ������� ����������
	bool autoRepeatChars = false;				// ���������� ����� ����������
	bool keyStates[256];						// ��������� ������ ���������� (������/�������� -> True/False)
	std::queue<KeyboardEvent> keyBuffer;		// ����� ������� ����������
	std::queue<unsigned char> charBuffer;		// ����� ����� ����������
};