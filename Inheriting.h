#pragma once

struct C // Forward declaration �� �����������.
{
	int aa; // public � ������ D. �� ��������� public-������������.
};

struct D : C
{
	int bb;
};

inline void InheritingDemo()
{
	D d{};
	d.aa = 1;
}