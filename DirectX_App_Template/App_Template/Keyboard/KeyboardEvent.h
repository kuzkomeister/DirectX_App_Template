#pragma once

class KeyboardEvent
{
public:
	enum EventType
	{
		Press,		// ������
		Release,	// ��������
		Invalid		// ���������������
	};

	/// <summary>
	/// ��������� ����������������� �������
	/// </summary>
	KeyboardEvent();				

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="type"> - ��� �������</param>
	/// <param name="key"> - ��������� � �������� �������</param>
	KeyboardEvent(const EventType type, const unsigned char key);
	
	/// <summary>
	/// �������-������� �������
	/// </summary>
	/// <returns>
	/// True - ���� ������,
	/// False - �� ���� ������
	/// </returns>
	bool IsPress() const;

	/// <summary>
	/// �������-��������� �������
	/// </summary>
	/// <returns>
	/// True - ���� ��������,
	/// False - �� ���� ��������
	/// </returns>
	bool IsRelease() const;

	/// <summary>
	/// ������ ������������ ���� �������
	/// </summary>
	/// <returns>
	/// True - ���� ��� �� �������� ����������������,
	/// False - ���� ��� ��������������
	/// </returns>
	bool IsValid() const;

	/// <summary>
	/// �������� ��� �������
	/// </summary>
	/// <returns>��� �������</returns>
	unsigned char GetKeyCode() const;

private:
	EventType type;		// ��� �������
	unsigned char key;	// ��� �������
};