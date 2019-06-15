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

inline int Mas1[2]; // Нужен inline. Будет инициализирован.
static int Mas2[2]; // Будет инициализирован.

inline void MasInitDemo()
{
	MassiveInit mi; // Все, кроме i, не будут инициализированы вне зависимости от уровня доступа.
	MassiveInit mp{}; // Результат тот же, что и вверху.
	MassiveInit mc = MassiveInit(); // Результат тот же, что и вверху.
	//MassiveInit ms(); // Пустой.

	MassiveInit1 ms; // i = 90; Остальные неинициализированы.
	MassiveInit1 md{}; // ВСЕ инициализированы.
	MassiveInit1 mw = MassiveInit1(); // ВСЕ инициализированы.

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