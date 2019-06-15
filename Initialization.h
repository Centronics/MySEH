#pragma once

class MassiveInit
{
	double ui;
	int mas[2];

public:
	int i;
	float flt;

	MassiveInit() : i()
	{

	}
};

class MassiveInit1
{
	double ui;
	float flt;

public:
	int i = 90;
	float rt;
	int mas[2];
};

inline int Mas1[2]; // ����� inline. ����� ���������������.
static int Mas2[2]; // ����� ���������������.

inline void MasInitDemo()
{
	MassiveInit mi; // ���, ����� i, �� ����� ���������������� ��� ����������� �� ������ �������.
	MassiveInit mp{}; // ��������� ��� ��, ��� � ������.
	MassiveInit mc = MassiveInit(); // ��������� ��� ��, ��� � ������.
	//MassiveInit ms(); // ������.

	MassiveInit1 ms; // i = 90; ��������� ������������������.
	MassiveInit1 md{}; // ��� ����������������.
	MassiveInit1 mw = MassiveInit1(); // ��� ����������������.

	int mas[2]; // �� ����� ���������������.

	int t1 = Mas1[0];
	int t2 = Mas1[1];
	int t3 = Mas2[0];
	int t4 = Mas2[1];

	int *k = Mas1, *m = Mas2;
	auto km = m - k; // int
	int p = k[-2]; // ����� ������� - ��� �� ������ (int).
	const auto t = static_cast<size_t>(-2);
	int s = Mas1[t]; // ��� �� ����� �� ������ (int).
	const unsigned long long g = 12;
	int o = Mas1[g]; // ������������ � ����������� (g). ����� �������, ����� ������ ����������� � ����� ������� ������.
	int ty = 90;
	int f = Mas1[static_cast<unsigned long long>(ty)]; // ��� �� ������ ��� ��� �����, � ����������� �� ���������.
	const unsigned int w = 3;
	int n = Mas1[w]; // ��� �� ������.
	int j = Mas1[-1]; // ��� �� ������.
	int r = Mas2[1]; // ��� �� ������.
}