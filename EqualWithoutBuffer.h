#pragma once
#include <string>
#include <winnt.h>

using namespace std::string_literals;

int Flip(int bit)
{
	return 1 ^ bit;
}

/* ¬озвращаем 1, если число положительное, и 0, если отрицательное*/
int Sign(int a)
{
	return Flip((a >> (sizeof(int) * CHAR_BIT - 1))) & 0x1;
}

inline int GetMax(int a, int b)
{
	int c = a - b;

	int sa = Sign(a); // если a >= 0, то 1, иначе 0
	int sb = Sign(b); // если a >= 1, то 1, иначе 0
	int sc = Sign(c); // зависит от переполнени€ a - b

	/* ÷ель: найти k, которое = 1, если а > b, и 0, если a < b.
	 * если a = b, k не имеет значени€ */

	 // ≈сли у а и b равные знаки, то k = sign(a)
	int use_sign_of_a = sa ^ sb;

	// ≈сли у a и b одинаковый знак, то k = sign(a - b)
	int use_sign_of_c = Flip(sa ^ sb);

	int k = use_sign_of_a * sa + use_sign_of_c * sc;
	int q = Flip(k); // отражение k

	return a * k + b * q;
}

inline void EqualWithoutBufferDemo()
{
	int t = GetMax(9, 10);
	int n = 0;
	n = n & (n - 1);
	bool b = n == 0;
	int* i = new int[0]; // указывает неизвестно, куда
	*i = 10;
	UNREFERENCED_PARAMETER(i);
}