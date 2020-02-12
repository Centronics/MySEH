#pragma once
#include <string>
#include <winnt.h>

using namespace std::string_literals;

int Flip(int bit)
{
	return 1 ^ bit;
}

/* ���������� 1, ���� ����� �������������, � 0, ���� �������������*/
int Sign(int a)
{
	return Flip((a >> (sizeof(int) * CHAR_BIT - 1))) & 0x1;
}

inline int GetMax(int a, int b)
{
	int c = a - b;

	int sa = Sign(a); // ���� a >= 0, �� 1, ����� 0
	int sb = Sign(b); // ���� a >= 1, �� 1, ����� 0
	int sc = Sign(c); // ������� �� ������������ a - b

	/* ����: ����� k, ������� = 1, ���� � > b, � 0, ���� a < b.
	 * ���� a = b, k �� ����� �������� */

	 // ���� � � � b ������ �����, �� k = sign(a)
	int use_sign_of_a = sa ^ sb;

	// ���� � a � b ���������� ����, �� k = sign(a - b)
	int use_sign_of_c = Flip(sa ^ sb);

	int k = use_sign_of_a * sa + use_sign_of_c * sc;
	int q = Flip(k); // ��������� k

	return a * k + b * q;
}

inline void EqualWithoutBufferDemo()
{
	int t = GetMax(9, 10);
	int n = 0;
	n = n & (n - 1);
	bool b = n == 0;
	int* i = new int[0]; // ��������� ����������, ����
	*i = 10;
	UNREFERENCED_PARAMETER(i);
}