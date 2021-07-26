#pragma once
struct MousePoint
{
	int x;
	int y;
};

class MouseEvent
{
public:
	enum EventType
	{
		LPress,			// ��� ������ 
		LRelease,		// ��� ��������
		RPress,			// ��� ������
		RRelease,		// ��� ��������
		MPress,			// �������� ������
		MRelease,		// �������� ��������
		WheelUp,		// ��������� �������� �����
		WheelDown,		// ��������� �������� ����
		Move,			// ����������� ����
		RAW_MOVE,		// �������������� �������� �����
		Invalid			// ���������������� 
	};
private:
	EventType type;
	int x;
	int y;
public:
	/// <summary>
	/// ��������� ����������������� �������
	/// </summary>
	MouseEvent();

	/// <summary>
	/// ��������� �������
	/// </summary>
	/// <param name="type"> - ��� �������</param>
	/// <param name="x"> - ���������� �</param>
	/// <param name="y"> - ���������� Y</param>
	MouseEvent(const EventType type, const int x, const int y);

	/// <summary>
	/// ������ ������������ ���� �������
	/// </summary>
	/// <returns>
	/// True - ���� �� �������� ����������������,
	/// False - ���� �������� ����������������
	/// </returns>
	bool IsValid() const;

	/// <summary>
	/// �������� ��� �������
	/// </summary>
	/// <returns></returns>
	EventType GetType() const;

	/// <summary>
	/// �������� �������������� ����
	/// </summary>
	/// <returns></returns>
	MousePoint GetPos() const;


	int GetPosX() const;
	int GetPosY() const;
};