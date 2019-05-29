#pragma once

class A
{
public:
	virtual ~A() = default;
	virtual void F()
	{
		i++;
	}

	int i = 0;
};

class B : public A
{
public:
	void F() override
	{
		b++;
	}

	int b = 0;
};

/* Если вызвать функцию F из копии, то в первом случае вызовется из класса B, а во втором - из класса A.
 * Второй случай работает с копией класса. Таким образом, во втором i будет равна единице, а в первом b будет равна единице.
 * В третьем случае b = 2, i = 0. Вызовется F из класса B. */

static void ClassCopyDemo()
{
	A* a = new B();
	a->F();      // Первый случай

	A da = *a;
	da.F();      // Второй случай

	A& das = *a;
	das.F();     // Третий случай
}