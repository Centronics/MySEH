#pragma once

class ClsSw
{
public:
	operator int() const // ���� �������� explicit, �� ����� ����������� ����� ��������������.
	{
		return 1;
	}
};

inline void SwitchDemo()
{
	ClsSw c;
	switch(c) // ����� ��������.
	{
	case 1:
		int y = 9;
		break;
	}
}