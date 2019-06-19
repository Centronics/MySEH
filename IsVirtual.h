#pragma once

class A
{
protected:
	int tt;

public:
	virtual char foo(int)
	{
		tt = 90;
		return 0;
	}
	virtual int foo(wchar_t) noexcept // Если функция const, то перекрытие должно быть тоже const. noexcept может быть, а может и не быть.
	{
		return 1;
	}
	virtual void foo()
	{
		return;
	}
};

class B : public A
{
	int td;

public:
	char foo(int) noexcept override
	{
		tt = 100;
		return 0;
	}
	int foo(wchar_t) noexcept override
	{
		return 1;
	}
	void foo() override
	{
		return;
	}
};

inline void IsVirtualStart()
{
	B b;
	A* pa = &b;
	pa->foo(1);
	pa->foo(L'1');
	pa->foo();
	b.foo(1);

	A a = b;
	// b = static_cast<B>(a); // Нельзя.

	a.foo(1);
	a.foo(L'1');
	a.foo();
}