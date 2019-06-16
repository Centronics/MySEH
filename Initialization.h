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

class Massive
{
	void vd() {}
	int u;
public:
	int at;

	Massive()
	{

	}
};

class MasHolder
{
public:
	Massive mas;
	int tt;
};

class BN
{
public:
	BN(int, float) {}
	int op;
};

class Book
{
public:
	BN mas;
	int yu;
};

class BCInh : public BN
{
public:
	BCInh() : BN(10, 90.9f)
	{

	}

	int t;
};

inline int Mas1[2]; // ����� inline. ����� ���������������.
static int Mas2[2]; // ����� ���������������.

inline void MasInitDemo()
{
	MasHolder masHolder = { Massive{}, 89 }; // � Massive ��������� ����������� ��� ����������.
	Book book = { BN(23, 68.0f), 56 };
	BN bn = { 45, 67.0f }; // ����������� ����������� � ����������� ������������ ������������� � ������ ����������.
	BCInh bci{};

	MassiveInit mi; // ���, ����� i, �� ����� ���������������� ��� ����������� �� ������ �������.
	MassiveInit mp{}; // ��������� ��� ��, ��� � ������.
	MassiveInit mc = MassiveInit(); // ��������� ��� ��, ��� � ������.
	//MassiveInit ms(); // ������.

	MassiveInit1 ms; // i = 90; ��������� ������������������.
	MassiveInit1 md{}; // ��� ����������������.
	MassiveInit1 mw = MassiveInit1(); // ��� ����������������.

	auto* mi1 = new MassiveInit;   // ���, ����� i, �� ����� ���������������� ��� ����������� �� ������ �������.
	auto* mp1 = new MassiveInit{}; // ��������� ��� ��, ��� � ������.
	auto* mc1 = new MassiveInit(); // ��������� ��� ��, ��� � ������.

	auto* ms1 = new MassiveInit1;   // i = 90; ��������� ������������������.
	auto* md1 = new MassiveInit1{}; // ��� ����������������.
	auto* mw1 = new MassiveInit1(); // ��� ����������������.

	delete mi1;
	delete mp1;
	delete mc1;
	delete ms1;
	delete md1;
	delete mw1;

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