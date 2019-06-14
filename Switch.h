#pragma once

class ClsSw
{
public:
	operator int() const // Если добавить explicit, то будет требоваться явное преобразование.
	{
		return 1;
	}
};

inline void SwitchDemo()
{
	ClsSw c;
	switch(c) // Будет работать.
	{
	case 1:
		int y = 9;
		break;
	}
}