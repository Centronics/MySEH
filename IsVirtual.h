class A
{
public:
	virtual char foo(int)
	{
		return 0;
	}
	virtual int foe(wchar_t)
	{
		return 1;
	}
	virtual void foi()
	{
		return;
	}
};

class B : public A
{
public:
	char foo(int)
	{
		return 0;
	}
	char foe(char)
	{
		return 1;
	}
	char foi(int)
	{
		return 1;
	}
};

void IsVirtualStart()
{
	B b;
	A* pa = &b;
	pa->foo(1);
	pa->foe(1);
	pa->foi();
	b.foi(1);
}