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

/* ���� ������� ������� F �� �����, �� � ������ ������ ��������� �� ������ B, � �� ������ - �� ������ A.
 * ������ ������ �������� � ������ ������. ����� �������, �� ������ i ����� ����� �������, � � ������ b ����� ����� �������.
 * � ������� ������ b = 2, i = 0. ��������� F �� ������ B. */

static void ClassCopyDemo()
{
	A* a = new B();
	a->F();      // ������ ������

	A da = *a;
	da.F();      // ������ ������

	A& das = *a;
	das.F();     // ������ ������
}