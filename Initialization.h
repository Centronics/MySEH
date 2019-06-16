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

inline int Mas1[2]; // Нужен inline. Будет инициализирован.
static int Mas2[2]; // Будет инициализирован.

inline void MasInitDemo()
{
	MasHolder masHolder = { Massive{}, 89 }; // У Massive вызовется конструктор без параметров.
	Book book = { BN(23, 68.0f), 56 };
	BN bn = { 45, 67.0f }; // Конструторы копирования и перемещения генерируются автоматически в случае отсутствия.
	BCInh bci{};

	MassiveInit mi; // Все, кроме i, не будут инициализированы вне зависимости от уровня доступа.
	MassiveInit mp{}; // Результат тот же, что и вверху.
	MassiveInit mc = MassiveInit(); // Результат тот же, что и вверху.
	//MassiveInit ms(); // Пустой.

	MassiveInit1 ms; // i = 90; Остальные неинициализированы.
	MassiveInit1 md{}; // ВСЕ инициализированы.
	MassiveInit1 mw = MassiveInit1(); // ВСЕ инициализированы.

	auto* mi1 = new MassiveInit;   // Все, кроме i, не будут инициализированы вне зависимости от уровня доступа.
	auto* mp1 = new MassiveInit{}; // Результат тот же, что и вверху.
	auto* mc1 = new MassiveInit(); // Результат тот же, что и вверху.

	auto* ms1 = new MassiveInit1;   // i = 90; Остальные неинициализированы.
	auto* md1 = new MassiveInit1{}; // ВСЕ инициализированы.
	auto* mw1 = new MassiveInit1(); // ВСЕ инициализированы.

	delete mi1;
	delete mp1;
	delete mc1;
	delete ms1;
	delete md1;
	delete mw1;

	int mas[2]; // Не будет инициализирован.

	int t1 = Mas1[0];
	int t2 = Mas1[1];
	int t3 = Mas2[0];
	int t4 = Mas2[1];

	int *k = Mas1, *m = Mas2;
	auto km = m - k; // int
	int p = k[-2]; // Номер индекса - тип со знаком (int).
	const auto t = static_cast<size_t>(-2);
	int s = Mas1[t]; // Тип всё равно со знаком (int).
	const unsigned long long g = 12;
	int o = Mas1[g]; // Превращается в беззнаковый (g). Таким образом, можно задать беззнаковый и очень большой индекс.
	int ty = 90;
	int f = Mas1[static_cast<unsigned long long>(ty)]; // Тип со знаком или без знака, в зависимости от поданного.
	const unsigned int w = 3;
	int n = Mas1[w]; // Тип со знаком.
	int j = Mas1[-1]; // Тип со знаком.
	int r = Mas2[1]; // Тип со знаком.
}