#pragma once
#include <algorithm>

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
	BN mas; // (10, 1) - ���������������� ������.
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

inline void FuncTry() noexcept try // ����� ������ ���.
{

}
catch (...) {}

inline int Mas1[2]; // ����� inline. ����� ���������������.
static int Mas2[2]; // ����� ���������������.

class DF
{
	int i = 9;
public:
	void Void()
	{
		if (this == nullptr) // this �� ����������� �� nullptr.
			return;
		i = 90;
	}
};

class DG
{
public:
	int t;
public:
	//DG(float) : t(0){}
};

class DS
{
	int t, u, t1;
public:
	DS(float f, int u) : t(f), u(u) {}
	// DS() = default;
};

class IniSeq
{
	Massive mas; DS ds;
	MassiveInit ms;
	BCInh bci;
	int i;
	double d;

public:
	IniSeq() : d(10.1), i(5), ds(11.4, 56)
	{
		// ������������� ����� ��������� � ������� ��������� ��������� � ������: mas, ds, ms, bci, i, d.
	}
};

class DoubleInit
{
	int i = 19;

public:
	DoubleInit() :i(20)
	{

	}

	DoubleInit(float) : i(30)
	{

	}
};

inline void MasInitDemo()
{
	FuncTry();

	MasHolder masHolder = { Massive{}, 89 }; // � Massive ��������� ����������� ��� ����������. tt = 89.
	MasHolder mash; // � Massive ��������� ����������� ��� ����������. ���������� �� ����������������.
	Book book = { BN(23, 68.0f), 56 };
	BN bn = { 45, 67.0f }; // ����������� ����������� � ����������� ������������ ������������� � ������ ����������.
	BCInh bci{};
	BN* pbn = new BN[2]{ BN(1,2.0f), BN(5,6.7f) }; // ���� ���������� ���������� �� ����� ��������������� ��� ����� �������� "()" � �����, �� ����� ������, ��� ��� ������������ �� ���������.

	MassiveInit mi; // ���, ����� i, �� ����� ���������������� ��� ����������� �� ������ �������.
	MassiveInit mp{}; // ��������� ��� ��, ��� � ������.
	MassiveInit mc = MassiveInit(); // ��������� ��� ��, ��� � ������.
	//MassiveInit ms(); // ������.

	MassiveInit1 ms; // i = 90; ��������� ������������������. � ���� ������ �������� ���������������� ������ ������.
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

	DF* lk = nullptr;
	lk->Void();
	DF* pdf = new DF();
	pdf->Void();
	int* pi = reinterpret_cast<int*>(pdf); // 90.
	int* gi = new int{ 12 }; // ���� ��� ������, �� ��� �������������, � ���� () ��� {}, �� ��� ����. ���� � {} ��������� �����, �� �� ����� ���������������� ����������, �� ��� ���� ������ ����������� �� ����� �������.
	int* gi1 = new int(9); // ���������� ����� 9.
	double* pd = new double[10](); // ���� � ����� "()", �� ����� ������������� ������. "()" ������ ��������, ���� ��� ������������ �� ���������.

	DG dg[3] = { {12} }; // ������ ����� 12, ��������� ����.
	DG dh[3]{ {13} }; // ������ ����� 13, ��������� ����.
	DG dp[3]{ 14 }; // ������ ����� 14, ��������� ����, �� ��� ����� �� ������.
	DG d�[3] = { 15 }; // ������ ����� 15, ��������� ����, �� ��� ����� �� ������.
	DG dk{ 10 }; // ���������.

	DG* pdg = new DG{ 14 }; // ����� �� ����� �����������.
	DS* pds = new DS{ 12.2f, 13 };
	DS* pdp = new DS(12.2f, 13); // ���������������.
	DG* plg = new DG(); // ���������������.
	DG* gpl = new DG; // �� ���������������.
	DG* gph = new DG{}; // ���������������.

	size_t count = 2;
	// DG dgx[count]; // count ����� ���� ������ ����������.
	DG* pph = new DG[count]; // �� ���������������.
	DG* kkp = new DG[count](); // ���������������.
	DG* kkm = new DG[count]{}; // ���������������.
	DG* kvp = new DG[count]{ 112, 113 }; // ������ �� �����, �� ������������� ����. ������ ��� ������. ���� "=" ����� "{" ������� ������. �������: ���� � ���, ��� ���������� "count" �����������, �.�. ������ ��������� � �������� new, �� ����� ������������� ������������.
	DG* kvk = new DG[count]{ DG(), {113} }; // ������ �� �����, �� ������������� ����. ������ ��� ������. ���� "=" ����� "{" ������� ������. �������: ���� � ���, ��� ���������� "count" �����������, �.�. ������ ��������� � �������� new, �� ����� ������������� ������������.
	DG* kvq = new DG[count]{ {112}, {113} }; // ������ �� �����, �� ������������� ����. ������ ��� ������. ���� "=" ����� "{" ������� ������. �������: ���� � ���, ��� ���������� "count" �����������, �.�. ������ ��������� � �������� new, �� ����� ������������� ������������.
	//DS* pd2 = new DS[2]{ {12.2f, 13}, {13.3f, 14} }; // ����� ������. "t1" �� ����������������. count ���������� ������. ����� ������ ���������.

	DG* kph = new DG[10]; // �� ���������������.
	DG* vkp = new DG[10](); // ���������������.
	DG* vkm = new DG[10]{}; // ���������������.
	DG* vvp = new DG[10]{ 112, 113 }; // ������ �� �����, �� ������������� ����. ������ ��� ������.
	DG* vvm = new DG[10]{ {112}, {113} }; // ������ �� �����, �� ������������� ����. ������ ��� ������. ���� "=" ����� "{" ������� ������.
	DG* vvk = new DG[10]{ DG(), {113} }; // ������ �� �����, �� ������������� ����. ������ ��� ������.
	DG* vvq = new DG[2]{ {112}, {113} }; // ������ �� �����, �� ������������� ����. ������ ��� ������. ���� "=" ����� "{" ������� ������.
	DS* kd2 = new DS[2]{ {12.2f, 13}, {13.3f, 14} }; // ����� ������. "t1" �� ����������������.

	// DS* zph = new DS; // ��� ������������ �� ���������.
	// DS* mph = new DS[10]; // ��� ������������ �� ���������.

	DS pdn{ 12.4,34 }; // ���������.
	DS pdz(12.4, 34); // ���������.
	// DG dgf(); // ������.
	// DS* zpm = new DS(); // ������.
	DG dfg{ 10 }; // ���������.
	DG mdg; // �� ����� ����������������.
	DG sdg{}; // ������������� �� ���������.

	DS dc[3] = { {16,6}, {17,7}, {18,8} }; // ���� �������� ������, ��� ������� � ��������������, ����� ������ ��-�� ���������� ������������ �� ���������.

	double x{ 2.7 };
	// int y1 {x};   // ������.
	// int y1 = {x}; // ������.
	int iii(2.7); // �����.
	int iij(x); // �����.

	int y3 = x; // ��� ����� �� ������.
	int y4 = static_cast<int>(x); // ��� ���� ������.
	double tre[5]{ 1.1, 2.2 }; // ����� ���������������� ������ ��� ��������� ����������, ��������� ������.
	double trr[5] = { 3.3, 4.4 }; // ����� ���������������� ������ ��� ��������� ����������, ��������� ������.

	int df = 12.2;
	double d1 = 12.5;
	int i = d1;
	char* a = "1";

	IniSeq seq;

	DoubleInit di; // i = 20
	DoubleInit da(3.14f); // i = 30. () ������ ������. ���������� ���, ��� i ������� �� ����� ����� 19.
	DoubleInit dx{}; // i = 20
	DoubleInit dn = {}; // i = 20
	DoubleInit ds = da; // i = 30
	DoubleInit dj(da); // i = 30
	DoubleInit de = da; // i = 30
	DoubleInit dm(std::move(da)); // i = 30
}