#pragma once // ���� ������, �� ����� ����������� �������� ���� ��������� ����� ������ ����. ����� �������, ����� ������ ����������.
inline void CallMe()
{
	
}

class StaticVar
{
public:
	inline static int StaticInt; // ���� inline, �� ��� ��������� ���� � �� �� ��������� �� ���� �������� ����������. ���� (), �� ��� ������ ���� �������, ����������� ����������� ��� ��. ��� ���������� ����� ������������� ����������������.
	//static int MyStaticVariableOld; LNK
	static constexpr int MyStaticConstConstexpr = 44; // �������� ����������.
};

//inline int StaticVar::MyStaticVariableOld = 0; // inline ���� ������.